#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Windows.h>
#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <vXboxInterface.h>
#include <IWindows/iwindows_xinput_wrapper.h>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_listenBtn_clicked();

    void on_stopBtn_clicked();
    void Recv();
private:
    Ui::MainWindow *ui;
    QUdpSocket *_udpSocket;
    QHostAddress _clientAddr;
    quint16 _clientPort;
    bool _firstPackage;
    UCHAR _slot;
};

#endif // MAINWINDOW_H
