#ifndef DISKSCHEDULAR_H
#define DISKSCHEDULAR_H

#include <QObject>

class DiskSchedular : public QObject
{
    Q_OBJECT
public:
    explicit DiskSchedular(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DISKSCHEDULAR_H