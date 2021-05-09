#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "stylesheet.h"

MainWindow::MainWindow(QWidget *parent):
                       QMainWindow(parent),
                       ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->client = new Client();

    masterPage = new Master(this, ui->mainStackedWidget, client);




    ui->mainStackedWidget->addWidget(masterPage);
    ui->mainStackedWidget->setCurrentWidget(masterPage);
}




MainWindow::~MainWindow()
{
    delete ui;

    delete masterPage;

}


void MainWindow::on_exitButton_clicked()
{

    client->stop();

    QCoreApplication::quit();
}
