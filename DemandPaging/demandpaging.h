#ifndef DEMANDPAGING_H
#define DEMANDPAGING_H

#include <QObject>
#include <QThread>

class DemandPaging : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int FrameSize READ FrameSize WRITE setFrameSize NOTIFY FrameSizeChanged)
    Q_PROPERTY(QList<QObject*> FrameList READ FrameList NOTIFY FrameListChanged)
    Q_PROPERTY(QList<QObject*> PageList READ PageList NOTIFY PageListChanged)
    Q_PROPERTY(QList<QObject*> FrameHistory READ FrameHistory NOTIFY FrameHistoryChanged)
    Q_PROPERTY(QObject* FirstPage READ FirstPage NOTIFY FirstPageChanged)
    Q_PROPERTY(int PageFaults READ PageFaults NOTIFY PageFaultsChanged)
    Q_PROPERTY(int PageHits READ PageHits NOTIFY PageHitsChanged)
    Q_PROPERTY(int TotalPages READ TotalPages NOTIFY TotalPagesChanged)
    Q_PROPERTY(QString ExtraTip READ ExtraTip NOTIFY ExtraTipChanged)

public:
    explicit DemandPaging(QObject *parent = nullptr);

    int FrameSize() const{ return frameSize;}
    void setFrameSize(const int FrameSize);

    QList<QObject*> FrameList() const{ return frameList;}

    QList<QObject*> PageList() const{ return pageList;}
    QObject* FirstPage() const{ return pageList.first();}

    QList<QObject*> FrameHistory() const{ return frameHistory;}

    int PageFaults() const{ return pageFaults;}
    int PageHits() const{ return pageHits;}
    int TotalPages() const{ return totalPages;}
    QString ExtraTip() const{ return extraTip;}

signals:
    void FrameSizeChanged();
    void FrameListChanged();
    void PageListChanged();
    void FirstPageChanged();
    void FrameHistoryChanged();

    void startThreadCalc();
    void moveNextPage(int frameIndex);

    void PageFaultsChanged();
    void PageHitsChanged();
    void TotalPagesChanged();
    void ExtraTipChanged();

public slots:
    void addPage(int page);
    void startCalculation(int typeOfAlgorithm);
    void reset();

    void updatePageList(int changedFrameNo);
    void updateFrameList(int changedFrameNo, int changedValue);
    void updateResult(int faults, int hits);

private:
    int frameSize;
    QList<QObject*> frameList;
    QList<QObject*> pageList;
    QList<QObject*> frameHistory;
    QThread calcThread;
    int pageFaults;
    int pageHits;
    int totalPages;
    QString extraTip;
};

#endif // DEMANDPAGING_H
