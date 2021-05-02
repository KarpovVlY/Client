#include "new_contact.h"
#include "ui_new_contact.h"

#include "master.h"


QString lineEditStyleheet = "QLineEdit { border: 2px solid rgb(37, 39, 48); color:  #FFF; border-radius: 15px; padding-left: 20px; padding-right: 20px; background-color: rgb(35, 38, 41); selection-background-color: rgb(43,45,56);  max-width:200px; max-height:30px; min-width:200px; min-height:30px;} "
                            "QLineEdit:hover{ border: 2px solid rgb(27, 28, 35);} "
                            "QLineEdit:focus{ border: 2px solid rgb(27, 28, 35); background-color: rgb(30, 33, 36); }";

QString pushButtonStyleheet = "QPushButton{ border-radius:15px;  background-color: rgb(35, 38, 41);  max-width:80px; max-height:30px; min-width:80px; min-height:30px; margin-left:170px;}"
                              "QPushButton:hover{ border: 2px solid rgb(27, 28, 35);}"
                              "QPushButton:focus{ border: 2px solid rgb(27, 28, 35); background-color: rgb(30, 33, 36); }";



NewContact::NewContact(QWidget *parent,
                       QStackedWidget *mainStackedWidget) :
                       QWidget(parent),
                       ui(new Ui::NewContact)
{
    ui->setupUi(this);


    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

}



void NewContact::fillList()
{
    nameLineEdit = new QLineEdit("Имя");
    companyLineEdit = new QLineEdit("Компания");
    numberPushButton = new QPushButton();


    QPixmap pixmap("/home/vladislav/Рабочий стол/ClientRes/add_white.png");
    QIcon icon(pixmap);
    numberPushButton->setIcon(icon);
    numberPushButton->setIconSize(QSize(30, 30));

    nameLineEdit->setStyleSheet(lineEditStyleheet);
    companyLineEdit->setStyleSheet(lineEditStyleheet);
    numberPushButton->setStyleSheet(pushButtonStyleheet);



    newContactScrollLayout->addWidget(nameLineEdit);
    newContactScrollLayout->addWidget(companyLineEdit);


    newContactScrollLayout->addWidget(numberPushButton);
}


void NewContact::on_cancelButon_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                this->mainStackedWidget->setCurrentWidget(masterWidget);
                Master *master = qobject_cast<Master *>(masterWidget);
                master->endAnimation();
                fadeEffect->setOpacity(1);
            });
}


void NewContact::on_confirmButton_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                this->mainStackedWidget->setCurrentWidget(masterWidget);
                Master *master = qobject_cast<Master *>(masterWidget);

                master->addNewContact(ui->nameLineEdit->text(),
                                      ui->commentLineEdit->text(),
                                      ui->phoneLineEdit->text(),
                                      ui->emailLineEdit->text(),
                                      ui->contentTextEdit->toPlainText());
                master->endAnimation();
                fadeEffect->setOpacity(1);
            });
}



void NewContact::startAnimation()
{
    fadeEffect = new QGraphicsOpacityEffect(this);
    animation = new QPropertyAnimation(fadeEffect, "opacity");
    this->setGraphicsEffect(fadeEffect);
    animation = new QPropertyAnimation(fadeEffect, "opacity");
    animation->setDuration(300);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}


void NewContact::endAnimation()
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


NewContact::~NewContact()
{
    delete ui;
    delete newContactScrollLayout;
}

