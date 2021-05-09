#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signup.h"
#include "master.h"

#include "client.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:

private:
    Ui::MainWindow *ui;
    SignUp *signUpPage;
    Master *masterPage;

    NewNote *newNotePage;
    NewContact *newContactPage;


    Client *client;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:





private slots:
    void on_exitButton_clicked();
};
#endif
