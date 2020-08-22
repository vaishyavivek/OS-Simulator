#ifndef PAGELIST_H
#define PAGELIST_H

#include <QObject>

class PageHistoryList: public QObject{
    Q_OBJECT
    Q_PROPERTY(int Header READ Header NOTIFY HeaderChanged)
    Q_PROPERTY(QList<QObject*> Pages READ Pages NOTIFY PagesChanged)
    Q_PROPERTY(QString Status READ Status NOTIFY StatusChanged)

public:
    PageHistoryList(QList<QObject*> PageList, int Header, QString Status, QObject *parent = nullptr)
        :QObject(parent), header(Header), status(Status){
        pageList.append(PageList);
    }

    int Header() const{ return header;}
    QList<QObject*> Pages() const{ return pageList;}
    QString Status() const{ return status;}

signals:
    void HeaderChanged();
    void PagesChanged();
    void StatusChanged();

private:
    int header;
    QList<QObject*> pageList;
    QString status;
};

#endif // PAGELIST_H
