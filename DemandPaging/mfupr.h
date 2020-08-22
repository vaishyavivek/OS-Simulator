#ifndef MFUPR_H
#define MFUPR_H

#include <QThread>
#include "page.h"

class MfuThread: public QObject{
    Q_OBJECT

public:
    MfuThread(QList<QObject*> PageList, int FrameSize, QObject *parent = nullptr)
        :QObject (parent){
        pageList.append(PageList);
        frameSize = FrameSize;
    }

    void calculate(){
        int faults = 0, hits = 0;
        for(int i = 0; i < frameSize; i++)
            frameList.append(new Page(-1));

        for(int i = 0; i < frameSize; i++){
            auto firstPage = qobject_cast<Page*>(pageList.takeFirst());
            emit updatePageList(i);
            QThread::msleep(500);

            frameList.replace(i, firstPage);
            emit updateFrameList(i, firstPage->Id());

            emit updateResult(++faults, hits);
            QThread::msleep(250);
        }

        int counter = frameSize - 1;
        while(!pageList.isEmpty()){
            auto firstPage = qobject_cast<Page*>(pageList.takeFirst());
            emit updatePageList(counter);
            QThread::msleep(500);

            int con = contains(firstPage);
            if(con > -1){
                hits++;
                emit updateFrameList(-1, firstPage->Id());
                counter = con;
            }
            else{
                frameList.replace(counter, firstPage);
                emit updateFrameList(counter, firstPage->Id());
                faults++;
            }

            emit updateResult(faults, hits);
            QThread::msleep(250);
        }
    }

    int contains(Page *page){
        for(int i = 0 ; i < frameList.length(); i++){
            auto frame = qobject_cast<Page*>(frameList[i]);
            if(frame->Id() == page->Id())
                return i;
        }
        return -1;
    }

signals:
    void updatePageList(int changedFrameNo);
    void updateFrameList(int changedFrameNo, int changedValue);
    void updateResult(int faults, int hits);

private:
    int frameSize;
    QList<QObject*> frameList;
    QList<QObject*> pageList;
};

#endif // MFUPR_H
