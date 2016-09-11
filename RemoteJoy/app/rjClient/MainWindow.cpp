#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QList>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _deviceID(0),
    _udpSocket(new QUdpSocket(this)),
    _timeInterval(67)
{
    ui->setupUi(this);
    _xWrapper = new IWindows_XInput_Wrapper;
    _xWrapper->Setup();

    connect(_xWrapper, SIGNAL(ButtonPressed(short,  QList<XboxOneButtons>)), this, SLOT(GetButtons(short,  QList<XboxOneButtons>)));
    connect(_xWrapper, SIGNAL(LeftThumbStick(short, double, double)), this, SLOT(GetLeftThumbstick(short, double, double)));
    connect(_xWrapper, SIGNAL(RightThumbStick(short, double, double)), this, SLOT(GetRightThumbstick(short, double, double)));
    connect(_xWrapper, SIGNAL(LeftTrigger(short, byte)), this, SLOT(GetLeftTrigger(short, byte)));
    connect(_xWrapper, SIGNAL(RightTrigger(short, byte)), this, SLOT(GetRightTrigger(short, byte)));

    connect(_xWrapper, SIGNAL(StateRecieve(short, XINPUT_STATE)), this, SLOT(GetXState(short, XINPUT_STATE)));

    connect(&_timer, SIGNAL(timeout()), this, SLOT(sendMsg()));
    connect(_udpSocket,SIGNAL(readyRead()),this,SLOT(Recv()));
    _xWrapper->Start();
}

MainWindow::~MainWindow()
{
    _xWrapper->Stop();
    delete _udpSocket;
    delete _xWrapper;
    delete ui;
}

void MainWindow::GetButtons(short uID, QList<XboxOneButtons> PressedButtons)
{
    if (uID != _deviceID) {
        return;
    }

    if (PressedButtons.contains(X1_up)) {
        ui->dupBtn->setChecked(true);
    }
    else {
        ui->dupBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_down)) {
        ui->ddwBtn->setChecked(true);
    }
    else {
        ui->ddwBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_left)) {
        ui->dltBtn->setChecked(true);
    }
    else {
        ui->dltBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_right)) {
        ui->drtBtn->setChecked(true);
    }
    else {
        ui->drtBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_start)) {
        ui->startBtn->setChecked(true);
    }
    else {
        ui->dupBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_back)) {
        ui->selectBtn->setChecked(true);
    }
    else {
        ui->selectBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_ltdown)) {
        ui->lsBtn->setChecked(true);
    }
    else {
        ui->lsBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_rtdown)) {
        ui->rsBtn->setChecked(true);
    }
    else {
        ui->rsBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_lbump)) {
        ui->lbBtn->setChecked(true);
    }
    else {
        ui->lbBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_rbump)) {
        ui->rbBtn->setChecked(true);
    }
    else {
        ui->rbBtn->setChecked(false);
    }

    //    if(PressedButtons.contains(X1_guide)) ui->dupBtn->setChecked(true) else ui->dupBtn->setChecked(false);
    if (PressedButtons.contains(X1_a)) {
        ui->aBtn->setChecked(true);
    }
    else {
        ui->aBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_b)) {
        ui->bBtn->setChecked(true);
    }
    else {
        ui->bBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_x)) {
        ui->xBtn->setChecked(true);
    }
    else {
        ui->xBtn->setChecked(false);
    }

    if (PressedButtons.contains(X1_y)) {
        ui->yBtn->setChecked(true);
    }
    else {
        ui->yBtn->setChecked(false);
    }
}

void MainWindow::GetLeftTrigger(short uID, byte Value)
{
    if (uID != _deviceID) {
        return;
    }

    ui->ltLineEdit->setText(QString::number(Value));
}

void MainWindow::GetRightTrigger(short uID, byte Value)
{
    if (uID != _deviceID) {
        return;
    }

    ui->rtLineEdit->setText(QString::number(Value));
}

void MainWindow::GetLeftThumbstick(short uID, double x, double y)
{
    if (uID != _deviceID) {
        return;
    }

    ui->lThumbLineEdit->setText(tr("%1,%2").arg(x).arg(y));
}

void MainWindow::GetRightThumbstick(short uID, double x, double y)
{
    if (uID != _deviceID) {
        return;
    }

    ui->rThumbLineEdit->setText(tr("%1,%2").arg(x).arg(y));
}

void MainWindow::GetXState(short uID, XINPUT_STATE state)
{
    if (uID != _deviceID) {
        return;
    }

    _xstate = state;
}

void MainWindow::Recv()
{
    while (_udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpSocket->pendingDatagramSize());
        _udpSocket->readDatagram(datagram.data(), datagram.size());

        for (int i = 0; i < datagram.size(); ++i)
        {
            printf("%x", datagram.at(i));
        }

        printf("\n");
    }
}

void MainWindow::on_deviceRadioBtn_1_clicked()
{
    _deviceID = 0;
}

void MainWindow::on_deviceRadioBtn_2_clicked()
{
    _deviceID = 1;
}

void MainWindow::on_deviceRadioBtn_3_clicked()
{
    _deviceID = 2;
}

void MainWindow::on_deviceRadioBtn_4_clicked()
{
    _deviceID = 3;
}

void MainWindow::on_connectBtn_clicked()
{
    _timer.start(_timeInterval);
    _udpSocket->bind(QHostAddress::Any, ui->clientPortLineEdit->text().toInt());
    _hostAddr = QHostAddress(ui->hostAddrComboBox->currentText());
    _hostPort = ui->portLineEdit->text().toInt();
    //    _udpSocket->connectToHost(ui->hostAddrComboBox->currentText(), ui->portLineEdit->text().toInt());
}

void MainWindow::sendMsg()
{
    _udpSocket->writeDatagram((char*)&_xstate, sizeof(XINPUT_STATE), _hostAddr, _hostPort);
}


void MainWindow::on_disconnectBtn_clicked()
{
    _timer.stop();
    _udpSocket->close();
}

void MainWindow::on_freqComboBox_activated(const QString &arg1)
{
    int freq = arg1.mid(0, arg1.length() - 2).toInt();
    _timeInterval = 1000 / freq;

    if (_timeInterval < 0 || _timeInterval > 1000)
    {
        _timeInterval = 66;
    }

    _timer.setInterval(_timeInterval);
}
