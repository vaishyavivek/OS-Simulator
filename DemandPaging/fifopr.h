#ifndef FIFOPR_H
#define FIFOPR_H

#include <QThread>
#include "page.h"

class FifoThread: public QObject{
    Q_OBJECT

public:
    FifoThread(QList<QObject*> PageList, int FrameSize, QObject *parent = nullptr)
        :QObject (parent){
        pageList.append(PageList);
        frameSize = FrameSize;
    }

    void calculate(){
        int faults = 0, hits = 0;
        for(int i = 0; i < frameSize; i++)
            frameList.append(new Page(-1));

        int counter = 0;
        while(!pageList.isEmpty()){
            auto firstPage = qobject_cast<Page*>(pageList.takeFirst());
            emit updatePageList(counter);
            QThread::msleep(500);

            if(contains(firstPage)){
                hits++;
                emit updateFrameList(-1, firstPage->Id());
            }
            else{
                frameList.replace(counter, firstPage);
                emit updateFrameList(counter, firstPage->Id());
                counter = (counter + 1)%frameSize;
                faults++;
            }

            emit updateResult(faults, hits);
            QThread::msleep(250);
        }
    }

    bool contains(Page *page){
        foreach(QObject *obj, frameList){
            auto frame = qobject_cast<Page*>(obj);
            if(frame->Id() == page->Id())
                return true;
        }
        return false;
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

#endif // FIFOPR_H
