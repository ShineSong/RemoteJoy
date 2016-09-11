#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <Windows.h>
#include <QUdpSocket>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _udpSocket(new QUdpSocket),
    _firstPackage(true)
{
    ui->setupUi(this);

    _slot = 0;

    while (!isControllerExists(_slot))
    {
        _slot++;

        if (_slot == 4) {
            break;
        }
    }

    PlugIn(_slot);
    connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(Recv()));
}

MainWindow::~MainWindow()
{
    UnPlug(_slot);
    delete _udpSocket;
    delete ui;
}

void MainWindow::on_listenBtn_clicked()
{
    _udpSocket->bind(QHostAddress::Any, 8845, QUdpSocket::ShareAddress);
    _firstPackage = true;
}

void MainWindow::on_stopBtn_clicked()
{
    _udpSocket->close();
}

void MainWindow::Recv()
{
    while (_udpSocket->hasPendingDatagrams() &&
            _udpSocket->pendingDatagramSize() >= sizeof(XINPUT_STATE))
    {
        XINPUT_STATE xstate;

        if (_firstPackage)
        {
            _udpSocket->readDatagram((char *)&xstate, sizeof(XINPUT_STATE), &_clientAddr, &_clientPort);
            _firstPackage = false;

            ui->clientInfoLineEdit->setText(tr("%1 %2").arg(_clientAddr.toString()).arg(_clientPort));
        } else
        {
            _udpSocket->readDatagram((char *)&xstate, sizeof(XINPUT_STATE));
        }



        WORD bID = xstate.Gamepad.wButtons;
        SetDpadOff(_slot);

        if ((X1_up & bID) != 0) {
            SetDpadUp(_slot);
        }

        if ((X1_down & bID) != 0) {
            SetDpadDown(_slot);
        }

        if ((X1_left & bID) != 0) {
            SetDpadLeft(_slot);
        }

        if ((X1_right & bID) != 0) {
            SetDpadRight(_slot);
        }

        SetBtnStart(_slot, (X1_start & bID) != 0);
        SetBtnBack(_slot, (X1_back & bID) != 0);
        SetBtnLT(_slot, (X1_ltdown & bID) != 0);
        SetBtnRT(_slot, (X1_rtdown & bID) != 0);
        SetBtnLB(_slot, (X1_lbump & bID) != 0);
        SetBtnRB(_slot, (X1_rbump & bID) != 0);
        SetBtnA(_slot, (X1_a & bID) != 0);
        SetBtnB(_slot, (X1_b & bID) != 0);
        SetBtnX(_slot, (X1_x & bID) != 0);
        SetBtnY(_slot, (X1_y & bID) != 0);
        SetTriggerL(_slot, xstate.Gamepad.bLeftTrigger);
        SetTriggerR(_slot, xstate.Gamepad.bRightTrigger);

        SetAxisX(_slot, xstate.Gamepad.sThumbLX);
        SetAxisY(_slot, xstate.Gamepad.sThumbLY);
        SetAxisRx(_slot, xstate.Gamepad.sThumbRX);
        SetAxisRy(_slot, xstate.Gamepad.sThumbRY);
    }
}
