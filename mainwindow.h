#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void processPendingDatagrams();

private slots:
    void TextPacketSave(const QString &fileName);

private:
    QUdpSocket *socket = nullptr;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
