#include "login.h"
#include "ui_login.h"


#include "mainwindow.h"


bool checked;

Login::Login(QWidget *parent,
             QStackedWidget *mainStackedWidget,
             Client *client,
             cryptopp *crypto) :
             QWidget(parent),
             ui(new Ui::Login)
{
    ui->setupUi(this);


    this->client = client;
    this->crypto = crypto;
    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

    ui->errorLabel->setVisible(false);
}



void Login::on_loginButton_clicked()
{
    client->sendMesage("MC_LOGIN:"  +
                       crypto->encrypt(ui->loginLineEdit->text()) + ':' +
                       crypto->encrypt(ui->passwordLineEdit->text()));


    if(client->receiveMessage() != "MS_SUCCESS_LOGGED")
    {
        ui->errorLabel->setVisible(true);
    }
    else
    {
        confirmationPage = new Confirmation(this,
                                            mainStackedWidget,
                                            masterWidget,
                                            client,
                                            crypto,
                                            true);
        mainStackedWidget->addWidget(confirmationPage);

        startAnimation();

        connect(animation, &QPropertyAnimation::finished,
                [=]()
                {
                    mainStackedWidget->setCurrentWidget(confirmationPage);
            /*
                    MainWindow *master = qobject_cast<MainWindow *>(masterWidget);
                    master->changePageToMaster();*/

                    confirmationPage->endAnimation();

                    fadeEffect->setOpacity(1);
                });
    }
}


void Login::on_signupButton_clicked()
{
    signUpPage = new SignUp(this, mainStackedWidget, client, crypto);
    mainStackedWidget->addWidget(signUpPage);

    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                mainStackedWidget->setCurrentWidget(signUpPage);

                signUpPage->endAnimation();

                fadeEffect->setOpacity(1);
            });
}


void Login::on_radioButton_clicked()
{
    checked = ui->checkedRadioButton->isChecked();
}


void Login::startAnimation()
{
    fadeEffect = new QGraphicsOpacityEffect(this);
    animation = new QPropertyAnimation(fadeEffect, "opacity");
    this->setGraphicsEffect(fadeEffect);
    animation->setDuration(300);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}


void Login::endAnimation()
{
    fadeEffect = new QGraphicsOpacityEffect(this);
    animation = new QPropertyAnimation(fadeEffect, "opacity");
    this->setGraphicsEffect(fadeEffect);
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}


Login::~Login()
{
    delete ui;
}

