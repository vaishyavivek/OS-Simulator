#ifndef ADVFIFOPR_H
#define ADVFIFOPR_H

#include <QThread>
#include "page.h"

class AdvFifoThread: public QObject{
    Q_OBJECT

public:
    AdvFifoThread(QList<QObject*> PageList, int FrameSize, QObject *parent = nullptr)
        :QObject (parent){
        pageList.append(PageList);
        frameSize = FrameSize;
    }

    void calculate(){
        int faults = 0, hits = 0;
        for(int i = 0; i < frameSize; i++){
            frameList.append(new Page(-1));
            countList.append(-1);
        }

        int pointer = 0;
        while(!pageList.isEmpty()){
            auto firstPage = qobject_cast<Page*>(pageList.takeFirst());

            int con = contains(firstPage);
            if(con > -1){
                //if it already has that page then mark its count bit as 1
                countList[con] = 1;

                hits++;
                emit updatePageList(con);
                QThread::msleep(500);

                emit updateFrameList(-1, firstPage->Id());
            }
            else{
                //go in a forever loop until we find a frame suitable for replacement
                while(true){
                    if(countList[pointer]){
                        //give it a second chance, mark its count bit as 0
                        countList[pointer] = 0;
                        pointer = (pointer + 1)%frameSize;
                    }
                    else{
                        //got the frame for replecement
                        frameList.replace(pointer, firstPage);
                        faults++;
                        emit updatePageList(pointer);
                        QThread::msleep(500);

                        emit updateFrameList(pointer, firstPage->Id());

                        pointer = (pointer + 1)%frameSize;
                        break;
                    }
                }
            }

            emit updateResult(faults, hits);
            QThread::msleep(250);
        }
    }

    int contains(Page *page){
        for(int i = 0 ; i < frameList.length(); i++){
            auto frame = qobject_cast<Page*>(frameList[i]);
            if(frame->Id() == page->Id()){
                countList[i]++;
                return i;
            }
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
    QList<int> countList;
};

#endif // ADVFIFOPR_H
