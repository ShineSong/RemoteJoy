#include <stdio.h>
#include <Windows.h>
#include "MainWindow.h"
#include <QApplication>
#include <Version.h>
int main(int argc,char ** argv)
{
    QApplication app(argc,argv);
    app.setApplicationVersion(QString("C%1.%2").arg(MAJOR_VERSION).arg(MINOR_VERSION));
    MainWindow w;
    w.show();
    return app.exec();
}
