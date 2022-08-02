
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    socket = new QUdpSocket(this);
        bool result =  socket->bind(QHostAddress::AnyIPv4, 45454);
        qDebug() << result;
        if(result)
        {
            qDebug() << "PASS";
        }
        else
        {
            qDebug() << "FAIL";
        }
        while(true)
        processPendingDatagrams();
        connect(socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()),Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
}

void MainWindow::TextPacketSave(const QString &fileName)
{
    QFile file(fileName);
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ioError(file, tr("Cannot open file %1 for writing"));

      }

      QTextStream out(&file);
      out.setEncoding(QTextStream::UnicodeUTF8);

      list<Drawing>::const_iterator it = drawings.begin();
      while (it != drawings.end()) {
        out << *it;
        ++it;
      }
      if (file.status() != IO_Ok) {
        ioError(file, tr("Error writing to file %1"));

      }
}

void MainWindow::processPendingDatagrams()
 {

    QHostAddress sender;
    u_int16_t port;
    while (socket->hasPendingDatagrams())
    {
         qDebug() << "in !";
         QByteArray datagram;
         datagram.resize(socket->pendingDatagramSize());
         socket->readDatagram(datagram.data(),datagram.size(),&sender,&port);
        qDebug() <<"Message From :: " << sender.toString();
        qDebug() <<"Port From :: "<< port;
        qDebug() <<"Message :: " << datagram;

    }
}
