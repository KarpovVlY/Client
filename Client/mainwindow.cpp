#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
                       QMainWindow(parent),
                       ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //signUpPage = new SignUp();
    masterPage = new Master(this, ui->mainStackedWidget);

    //newContactPage = new NewContact(this, ui->mainStackedWidget);
    //newNotePage = new NewNote(this, ui->mainStackedWidget);


    ui->mainStackedWidget->addWidget(masterPage);
    //ui->mainStackedWidget->addWidget(signUpPage);
   // ui->mainStackedWidget->addWidget(newContactPage);
    //ui->mainStackedWidget->addWidget(newNotePage);

    ui->mainStackedWidget->setCurrentWidget(masterPage);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete signUpPage;
    delete masterPage;

}


void MainWindow::on_exitButton_clicked()
{
    //this->setVisible(false);
    QCoreApplication::quit();
}
