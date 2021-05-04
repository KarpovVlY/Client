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

    ui->contentTextEdit->setPlainText("");

    isNewContactFromMaster = true;
}


NewContact::NewContact(QWidget *parent,
                       QStackedWidget *mainStackedWidget,
                       QString name,
                       QString description,
                       QString phone,
                       QString email,
                       QString content):
                       QWidget(parent),
                       ui(new Ui::NewContact)
{
    ui->setupUi(this);


    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

    ui->nameLineEdit->setText(name);
    ui->commentLineEdit->setText(description);
    ui->phoneLineEdit->setText(phone);
    ui->emailLineEdit->setText(email);
    ui->contentTextEdit->setPlainText(content);


    ui->newContactLabel->setText("Изменить контакт");

    isNewContactFromMaster = false;
}



void NewContact::on_cancelButon_clicked()
{
   startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {

                if(isNewContactFromMaster)
                {
                    this->mainStackedWidget->setCurrentWidget(masterWidget);
                    Master *master = qobject_cast<Master *>(masterWidget);
                    master->endAnimation();
                }
                else
                {
                    this->mainStackedWidget->setCurrentWidget(masterWidget);
                    Contact *contact = qobject_cast<Contact *>(masterWidget);
                    contact->endAnimation();
                }


                fadeEffect->setOpacity(1);
            });
}


void NewContact::on_confirmButton_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {

                if(isNewContactFromMaster)
                {
                    this->mainStackedWidget->setCurrentWidget(masterWidget);
                    Master *master = qobject_cast<Master *>(masterWidget);

                    master->addNewContact(ui->nameLineEdit->text(),
                                          ui->commentLineEdit->text(),
                                          ui->phoneLineEdit->text(),
                                          ui->emailLineEdit->text(),
                                          ui->contentTextEdit->toPlainText());
                    master->endAnimation();

                    ui->nameLineEdit->setText("");
                    ui->commentLineEdit->setText("");
                    ui->phoneLineEdit->setText("");
                    ui->emailLineEdit->setText("");
                    ui->contentTextEdit->setPlainText("");
                }
                else
                {
                    this->mainStackedWidget->setCurrentWidget(masterWidget);
                    Contact *contact = qobject_cast<Contact *>(masterWidget);

                    contact->contactChanged(ui->nameLineEdit->text(),
                                            ui->commentLineEdit->text(),
                                            ui->phoneLineEdit->text(),
                                            ui->emailLineEdit->text(),
                                            ui->contentTextEdit->toPlainText());

                    contact->endAnimation();
                }



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
}

