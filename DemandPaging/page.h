#ifndef PAGE_H
#define PAGE_H

#include <QObject>

class Page: public QObject{
    Q_OBJECT
    Q_PROPERTY(int Id READ Id WRITE setId NOTIFY IdChanged)
public:
    explicit Page(int Id, QObject *parent = nullptr)
        :QObject(parent), id(Id){}

    int Id() const{ return id;}
    void setId(const int Id){ id = Id;}

signals:
    void IdChanged();

private:
    int id;
};

#endif // PAGE_H
