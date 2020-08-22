#ifndef LRUPR_H
#define LRUPR_H

#include <QThread>
#include "page.h"

class LruThread: public QObject{
    Q_OBJECT

public:
    LruThread(QList<QObject*> PageList, int FrameSize, QObject *parent = nullptr)
        :QObject (parent){
        pageList.append(PageList);
        frameSize = FrameSize;
    }

    void calculate(){
        int faults = 0, hits = 0;
        for(int i = 0; i < frameSize; i++)
            frameList.append(new Page(-1));

        int lIndex = 0;
        while(!pageList.isEmpty()){
            auto firstPage = qobject_cast<Page*>(pageList.takeFirst());

            int oindex = indexOf(firstPage);
            if(oindex > -1){
                displace(firstPage);
                emit updatePageList(oindex);
                QThread::msleep(500);
                hits++;
                emit updateFrameList(-1, firstPage->Id());
            }
            else{
                if(!tempFrameList.isEmpty() && tempFrameList.length() >= frameList.length())
                    lIndex = indexOf(qobject_cast<Page*>(tempFrameList.takeFirst()));

                frameList.replace(lIndex, firstPage);
                tempFrameList.append(firstPage);

                emit updatePageList(lIndex);
                QThread::msleep(500);

                emit updateFrameList(lIndex, firstPage->Id());
                lIndex++;
                faults++;
            }


            emit updateResult(faults, hits);
            QThread::msleep(250);
        }
    }

    void displace(Page *page){
        for(int i = 0; i < tempFrameList.length(); i++){
            if(page->Id() == (qobject_cast<Page*>(tempFrameList[i]))->Id()){
                tempFrameList.removeAt(i);
                break;
            }
        }
        tempFrameList.append(page);
    }

    int indexOf(Page *page){
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
    QList<QObject*> tempFrameList;
    QList<QObject*> pageList;
};

#endif // LRUPR_H
