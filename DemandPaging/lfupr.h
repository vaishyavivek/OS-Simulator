#ifndef LFUPR_H
#define LFUPR_H

#include <QThread>
#include "page.h"

class CountClass{
public:
    CountClass(int Id, int Count)
        :id(Id), count(Count){}
    int Id() const{return id;}
    int Count() const{ return count;}
    void incrementCount(){ count++; }
    void decrementCount(){ if(count != 0) count--;}
private:
    int id, count;
};

class LfuThread: public QObject{
    Q_OBJECT

public:
    LfuThread(QList<QObject*> PageList, int FrameSize, QObject *parent = nullptr)
        :QObject (parent){
        pageList.append(PageList);
        frameSize = FrameSize;
    }

    void calculate(){
        int faults = 0, hits = 0;
        for(int i = 0; i < frameSize; i++)
            frameList.append(new Page(-1));

        foreach (QObject *obj, pageList){
            auto id = qobject_cast<Page*>(obj)->Id();
            int i;
            for(i = 0; i < repeated.length() && repeated[i].Id() != id; i++);

            if(i == repeated.length())
                repeated.append(CountClass(id, 0));
        }

        int count = 0;
        while(count < frameSize){
            auto firstPage = qobject_cast<Page*>(pageList.takeFirst());
            incrementCount(firstPage->Id());
            frameList.replace(count, firstPage);
            emit updatePageList(count);
            QThread::msleep(500);
            faults++;
            emit updateFrameList(count++, firstPage->Id());
        }

        while(!pageList.isEmpty()){
            auto firstPage = qobject_cast<Page*>(pageList.takeFirst());

            int position = contains(firstPage);
            if(position > -1){
                incrementCount(firstPage->Id());
                emit updatePageList(position);
                QThread::msleep(500);
                hits++;
                emit updateFrameList(-1, firstPage->Id());
            }
            else{
                int l = leastCount();
                int con = contains(new Page(l));
                frameList.replace(con, firstPage);
                incrementCount(firstPage->Id());

                emit updatePageList(con);
                QThread::msleep(500);

                emit updateFrameList(con, firstPage->Id());
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

    void incrementCount(int Id){
        for(int i = 0; i < repeated.length(); i++)
            if(repeated[i].Id() == Id){
                repeated[i].incrementCount();
                repeated.move(i, frameSize - 1);
                break;
            }

    }

    int leastCount(){
        int least = 0;

        for(int i = 1; i < frameSize - 1; i++)
            if(repeated[i].Count() < repeated[least].Count())
                least = i;

        repeated[least].decrementCount();
        repeated.move(least, frameSize);
        return repeated[frameSize].Id();
    }

signals:
    void updatePageList(int changedFrameNo);
    void updateFrameList(int changedFrameNo, int changedValue);
    void updateResult(int faults, int hits);

private:
    int frameSize;
    QList<QObject*> frameList;
    QList<QObject*> pageList;
    QList<CountClass> repeated;
};

#endif // LFUPR_H
