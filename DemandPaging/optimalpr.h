#ifndef OPTIMALPR_H
#define OPTIMALPR_H

#include <QThread>
#include "page.h"

class OptimalThread: public QObject{
    Q_OBJECT

public:
    OptimalThread(QList<QObject*> PageList, int FrameSize, QObject *parent = nullptr)
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

            int lIndex = contains(firstPage);
            if(lIndex > -1){
                hits++;
                emit updatePageList(lIndex);
                QThread::msleep(500);
                emit updateFrameList(-1, firstPage->Id());
            }
            else{
                lIndex = (counter < frameSize) ? counter++ : forLookFuture();
                frameList.replace(lIndex, firstPage);
                faults++;
                emit updatePageList(lIndex);
                QThread::msleep(500);
                emit updateFrameList(lIndex, firstPage->Id());
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

    int forLookFuture(){
        //signed int nearOccurence = -1;
        int index = 0;
        for(int j = 0, nearOccurence = 0; j < frameSize; j++){
            auto frame = qobject_cast<Page*>(frameList[j]);
            if(frame->Id() != -1){
                int i;
                for(i = 0; i < pageList.length(); i++){
                    auto page = qobject_cast<Page*>(pageList[i]);
                    if(page->Id() == frame->Id()){
                        if(nearOccurence < i){
                            nearOccurence = i;
                            index = j;
                        }
                        break;
                    }
                }
                if(i == pageList.length()){
                    nearOccurence = i;
                    index = j;
                }
            }
        }
        return index;
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

#endif // OPTIMALPR_H
