#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTranslator translator;
    translator.load(":/XimalayaTextDownload_zh_CN.qm");
    qApp->installTranslator(&translator);
    w.show();
    return a.exec();
}
