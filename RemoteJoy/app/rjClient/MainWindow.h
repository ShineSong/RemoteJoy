#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTimer>
#include <QHostAddress>
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

protected slots:
    void GetButtons(short uID, QList<XboxOneButtons> PressedButtons);
    void GetLeftTrigger(short uID, byte Value);
    void GetRightTrigger(short uID, byte Value);
    void GetLeftThumbstick(short uID, double x, double y);
    void GetRightThumbstick(short uID, double x, double y);
    void GetXState(short uID,XINPUT_STATE state);
    void Recv();
private slots:
    void on_deviceRadioBtn_1_clicked();

    void on_deviceRadioBtn_2_clicked();

    void on_deviceRadioBtn_3_clicked();

    void on_deviceRadioBtn_4_clicked();

    void on_connectBtn_clicked();


    void sendMsg();
    void on_disconnectBtn_clicked();

    void on_freqComboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    IWindows_XInput_Wrapper *_xWrapper;
    XINPUT_STATE _xstate;
    int _deviceID;
    QUdpSocket *_udpSocket;
    QTimer _timer;
    int _timeInterval;
    QHostAddress _hostAddr;
    int _hostPort;
};

#endif // MAINWINDOW_H
