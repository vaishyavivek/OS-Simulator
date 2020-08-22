#include "demandpaging.h"
#include "page.h"
#include "pagelist.h"
#include "fifopr.h"
#include "lrupr.h"
#include "lfupr.h"
#include "mfupr.h"
#include "optimalpr.h"
#include "advfifopr.h"

DemandPaging::DemandPaging(QObject *parent)
    : QObject(parent){
    extraTip = "Status";
    reset();
}

void DemandPaging::reset(){
    pageList.clear();
    emit PageListChanged();
    frameList.clear();
    emit FrameListChanged();
    frameSize = 0;
    emit FrameSizeChanged();
    frameHistory.clear();
    emit FrameHistoryChanged();
    extraTip.clear();
    emit ExtraTipChanged();
    pageFaults = 0;
    emit PageFaultsChanged();
    pageHits = 0;
    emit PageHitsChanged();
    totalPages = 0;
    emit TotalPagesChanged();
    if(calcThread.isRunning()){
        calcThread.quit();
        calcThread.wait();
    }
}

void DemandPaging::setFrameSize(const int FrameSize){
    if(frameSize != FrameSize)
        frameSize = FrameSize;

    frameList.clear();
    for(int i = 0; i < frameSize; i++)
        frameList.append(new Page(-1));
    emit FrameListChanged();
}

void DemandPaging::addPage(int page){
    pageList.append(new Page(page));
    emit PageListChanged();
    totalPages = pageList.length();
    emit TotalPagesChanged();
}

void DemandPaging::startCalculation(int typeOfAlgorithm){
    if(typeOfAlgorithm == 0){
        FifoThread *fifo = new FifoThread(pageList, frameSize);
        fifo->moveToThread(&calcThread);
        connect(fifo, &FifoThread::updatePageList, this, &DemandPaging::updatePageList);
        connect(fifo, &FifoThread::updateFrameList, this, &DemandPaging::updateFrameList);
        connect(this, &DemandPaging::startThreadCalc, fifo, &FifoThread::calculate);
        connect(fifo, &FifoThread::updateResult, this, &DemandPaging::updateResult);
        connect(&calcThread, &QThread::finished, fifo, &QObject::deleteLater);
    }
    else if(typeOfAlgorithm == 1){
        LruThread *lru = new LruThread(pageList, frameSize);
        lru->moveToThread(&calcThread);
        connect(lru, &LruThread::updatePageList, this, &DemandPaging::updatePageList);
        connect(lru, &LruThread::updateFrameList, this, &DemandPaging::updateFrameList);
        connect(this, &DemandPaging::startThreadCalc, lru, &LruThread::calculate);
        connect(lru, &LruThread::updateResult, this, &DemandPaging::updateResult);
        connect(&calcThread, &QThread::finished, lru, &QObject::deleteLater);
    }
    else if(typeOfAlgorithm == 2){
        LfuThread *lfu = new LfuThread(pageList, frameSize);
        lfu->moveToThread(&calcThread);
        connect(lfu, &LfuThread::updatePageList, this, &DemandPaging::updatePageList);
        connect(lfu, &LfuThread::updateFrameList, this, &DemandPaging::updateFrameList);
        connect(this, &DemandPaging::startThreadCalc, lfu, &LfuThread::calculate);
        connect(lfu, &LfuThread::updateResult, this, &DemandPaging::updateResult);
        connect(&calcThread, &QThread::finished, lfu, &QObject::deleteLater);
    }
    else if(typeOfAlgorithm == 3){
        MfuThread *mfu = new MfuThread(pageList, frameSize);
        mfu->moveToThread(&calcThread);
        connect(mfu, &MfuThread::updatePageList, this, &DemandPaging::updatePageList);
        connect(mfu, &MfuThread::updateFrameList, this, &DemandPaging::updateFrameList);
        connect(this, &DemandPaging::startThreadCalc, mfu, &MfuThread::calculate);
        connect(mfu, &MfuThread::updateResult, this, &DemandPaging::updateResult);
        connect(&calcThread, &QThread::finished, mfu, &QObject::deleteLater);
    }
    else if(typeOfAlgorithm == 4){
        OptimalThread *optimal = new OptimalThread(pageList, frameSize);
        optimal->moveToThread(&calcThread);
        connect(optimal, &OptimalThread::updatePageList, this, &DemandPaging::updatePageList);
        connect(optimal, &OptimalThread::updateFrameList, this, &DemandPaging::updateFrameList);
        connect(this, &DemandPaging::startThreadCalc, optimal, &OptimalThread::calculate);
        connect(optimal, &OptimalThread::updateResult, this, &DemandPaging::updateResult);
        connect(&calcThread, &QThread::finished, optimal, &QObject::deleteLater);
    }
    else if(typeOfAlgorithm == 5){
        AdvFifoThread *advFifo = new AdvFifoThread(pageList, frameSize);
        advFifo->moveToThread(&calcThread);
        connect(advFifo, &AdvFifoThread::updatePageList, this, &DemandPaging::updatePageList);
        connect(advFifo, &AdvFifoThread::updateFrameList, this, &DemandPaging::updateFrameList);
        connect(this, &DemandPaging::startThreadCalc, advFifo, &AdvFifoThread::calculate);
        connect(advFifo, &AdvFifoThread::updateResult, this, &DemandPaging::updateResult);
        connect(&calcThread, &QThread::finished, advFifo, &QObject::deleteLater);
    }

    calcThread.start();
    emit TotalPagesChanged();
    emit startThreadCalc();
}


void DemandPaging::updatePageList(int changedFrameNo){
    emit FirstPageChanged();
    if(!pageList.isEmpty())
        pageList.removeFirst();
    emit PageListChanged();
    emit moveNextPage(changedFrameNo);
}

void DemandPaging::updateFrameList(int changedFrameNo, int changedValue){
    PageHistoryList *pgList;
    if(changedFrameNo != -1 && changedValue != -1){
        Page *changedPage = new Page(changedValue);
        frameList.replace(changedFrameNo, changedPage);
        emit FrameListChanged();
        pgList = new PageHistoryList(frameList, changedValue, "F");
    }
    else
        pgList = new PageHistoryList(frameList, changedValue, "H");

    frameHistory.append(pgList);
    emit FrameHistoryChanged();
}

void DemandPaging::updateResult(int faults, int hits){
    if(faults != pageFaults){
        pageFaults = faults;
        emit PageFaultsChanged();
        extraTip = "Page Fault";
    }

    if(hits != pageHits){
        pageHits = hits;
        emit PageHitsChanged();
        extraTip = "Page Hit";
    }

    emit ExtraTipChanged();
}
