#include <Windows.h>
#include <QApplication>
#include <MainWindow.h>
#include <vXboxInterface.h>
#include <Version.h>
int main(int argc, char **argv)
{
    if (!isVBusExists())
    {
        printf("[Error] SCPVBus is not exist, please run this command with administrator permission.\n devcon.exe install ScpVBus.inf Root\ScpVBus");
        getchar();
        return -1;
    }

    UCHAR num;
    GetNumEmptyBusSlots(&num);

    if (num == 0)
    {
        printf("[Error] XInput slot is full.");
        getchar();
        return -2;
    }

    QApplication app(argc, argv);
    app.setApplicationVersion(QString("H%1.%2").arg(MAJOR_VERSION).arg(MINOR_VERSION));
    MainWindow w;
    w.show();
    return app.exec();
}
