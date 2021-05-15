#include "confirmation.h"
#include "ui_confirmation.h"


#include "signup.h"
#include "login.h"

bool masterType;

Confirmation::Confirmation(QWidget *parent,
                           QStackedWidget *mainStackedWidget,
                           QWidget *masterWidget,
                           Client *client,
                           cryptopp *crypto,
                           bool type) :
                           QWidget(parent),
                           ui(new Ui::Confirmation)
{
    ui->setupUi(this);

    masterType = type;


    this->client = client;
    this->crypto = crypto;

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;
    this->masterMasterWidget = masterWidget;

    ui->errorLabel->setVisible(false);
}


void Confirmation::on_cancelButon_clicked()
{
    startAnimation();


    if(masterType)
    {
        connect(animation, &QPropertyAnimation::finished,
                [=]()
                {
                    mainStackedWidget->setCurrentWidget(masterWidget);
                    Login *master = qobject_cast<Login *>(masterWidget);
                    master->endAnimation();

                    fadeEffect->setOpacity(1);
                });
    }
    else
    {
        connect(animation, &QPropertyAnimation::finished,
                [=]()
                {
                    mainStackedWidget->setCurrentWidget(masterWidget);
                    SignUp *master = qobject_cast<SignUp *>(masterWidget);
                    master->endAnimation();

                    fadeEffect->setOpacity(1);
                });
    }
}



void Confirmation::on_confirmButton_clicked()
{
    if(masterType)
    {
        client->sendMesage("MC_LOGGED_REQUEST:" +
                           ui->requestCodeLineEdit->text());


    }
    else
    {
        client->sendMesage("MC_REGISTRATION_REQUEST:" +
                           ui->requestCodeLineEdit->text());

        if(client->receiveMessage() == "MS_SUCCESS_REGISTERED")
        {
            startAnimation();

            connect(animation, &QPropertyAnimation::finished,
                    [=]()
                    {
                        this->mainStackedWidget->setCurrentWidget(masterMasterWidget);
                        Login *master = qobject_cast<Login *>(masterMasterWidget);
                        master->endAnimation();

                        fadeEffect->setOpacity(1);
                    });
        }
        else
            ui->errorLabel->setVisible(true);
    }
}


void Confirmation::startAnimation()
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


void Confirmation::endAnimation()
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



Confirmation::~Confirmation()
{
    delete ui;
}

