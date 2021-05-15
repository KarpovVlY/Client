#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "login.h"
#include "master.h"

#include "client.h"
#include "cryptopp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    Master *masterPage;
    Login *loginPage;

    Client *client;
    cryptopp *crypto;

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


    void changePageToMaster();
    void changePageToLogin();



private slots:
    void on_exitButton_clicked();
};
#endif
