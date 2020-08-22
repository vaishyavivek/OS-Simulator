#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DemandPaging/demandpaging.h"
#include "DiskSchedular/diskschedular.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setApplicationName("OS-Simulator");
    QCoreApplication::setOrganizationDomain("geetasoftwarecompany.com");
    QCoreApplication::setOrganizationName("Geeta Software Company");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("demandPagingCPP", new DemandPaging());

    ctxt->setContextProperty("diskScheduling", new DiskSchedular());

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
