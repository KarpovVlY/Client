#include "signup.h"
#include "ui_signup.h"

#include "login.h"
#include "mainwindow.h"

SignUp::SignUp(QWidget *parent,
               QStackedWidget *mainStackedWidget,
               Client *client,
               cryptopp *crypto) :
               QWidget(parent),
               ui(new Ui::SignUp)
{
    ui->setupUi(this);


    this->client = client;
    this->crypto = crypto;
    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

    ui->errorLabel->setVisible(false);

}



void SignUp::changePageToLogin()
{
    MainWindow *master = qobject_cast<MainWindow *>(masterWidget);
    master->changePageToLogin();
}


void SignUp::on_cancelButon_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                this->mainStackedWidget->setCurrentWidget(masterWidget);
                Login *master = qobject_cast<Login *>(masterWidget);
                master->endAnimation();

                fadeEffect->setOpacity(1);
            });

}

void SignUp::on_confirmButton_clicked()
{

    client->sendMesage("MC_REGISTER:" +
                       crypto->encrypt(ui->nameLineEdit->text()) + ':' +
                       crypto->encrypt(ui->surnameLineEdit->text()) + ':' +
                       crypto->encrypt(ui->loginLineEdit->text()) + ':' +
                       ui->emailLineEdit->text() + ':' +
                       crypto->encrypt(ui->passwordLineEdit->text()) + ':' +
                       crypto->encrypt(ui->repeatLineEdit->text()));



    if(client->receiveMessage() != "MS_INTERMEDIATE_REGISTERED")
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
                                            false);
        mainStackedWidget->addWidget(confirmationPage);

        startAnimation();

        connect(animation, &QPropertyAnimation::finished,
                [=]()
                {
                    mainStackedWidget->setCurrentWidget(confirmationPage);

                    confirmationPage->endAnimation();

                    fadeEffect->setOpacity(1);
                });
    }
}


void SignUp::startAnimation()
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


void SignUp::endAnimation()
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

SignUp::~SignUp()
{
    delete ui;
}
