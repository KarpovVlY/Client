#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "stylesheet.h"


MainWindow::MainWindow(QWidget *parent):
                       QMainWindow(parent),
                       ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->client = new Client();
    this->crypto = new cryptopp();


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/vladislav/Work/Projects/VKR/ClientDataBase/ClientDB.db");
    db.open();


     QSqlQuery query;
     query.exec("SELECT checked FROM settings");

     query.next();
     QString checked = query.value(0).toString();


     masterPage = new Master(this, ui->mainStackedWidget, client, crypto);
     ui->mainStackedWidget->addWidget(masterPage);

     if(checked == "false")
     {
         loginPage = new Login(this, ui->mainStackedWidget, client, crypto);

         ui->mainStackedWidget->addWidget(loginPage);

         ui->mainStackedWidget->setCurrentWidget(loginPage);
     }
     else if(checked == "true")
         ui->mainStackedWidget->setCurrentWidget(masterPage);


}



void MainWindow::changePageToMaster()
{
    masterPage->endAnimation();
    ui->mainStackedWidget->setCurrentWidget(masterPage);
}


void MainWindow::changePageToLogin()
{
    loginPage->endAnimation();
    ui->mainStackedWidget->setCurrentWidget(loginPage);
}


void MainWindow::on_exitButton_clicked()
{
    client->stop();

    QCoreApplication::quit();
}



MainWindow::~MainWindow()
{
    delete ui;
    delete masterPage;

}
