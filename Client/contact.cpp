#include "contact.h"
#include "ui_contact.h"

#include "master.h"

Contact::Contact(QWidget *parent,
                 QStackedWidget *mainStackedWidget,
                 ContactItem *item) :
                 QWidget(parent),
                 ui(new Ui::Contact)
{
    ui->setupUi(this);

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;


    this->currentItem = item;


    ui->nameLineEdit->setText(item->name);
    ui->companyLineEdit->setText(item->description);
    ui->phoneLineEdit->setText(item->phone);
    ui->emailLineEdit->setText(item->email);
    ui->contentPlainTextEdit->setPlainText(item->content);
}


void Contact::on_cancelButon_clicked()
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


void Contact::on_editButton_clicked()
{
    NewContact *newContactPage = new NewContact(this,
                                       mainStackedWidget,
                                       currentItem->name,
                                       currentItem->description,
                                       currentItem->phone,
                                       currentItem->email,
                                       currentItem->content);

    mainStackedWidget->addWidget(newContactPage);

    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                mainStackedWidget->setCurrentWidget(newContactPage);

                newContactPage->endAnimation();

                fadeEffect->setOpacity(1);
            });


}


void Contact::on_deleteButon_clicked()
{
    QSqlQuery query;
    query.exec("DELETE FROM contacts WHERE id = " + QString::number(currentItem->uniqueId));


    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                this->mainStackedWidget->setCurrentWidget(masterWidget);
                Master *master = qobject_cast<Master *>(masterWidget);
                master->endAnimation();
                master->deleteContactItem(currentItem->id);

                fadeEffect->setOpacity(1);
            });
}



void Contact::contactChanged(QString name,
                             QString description,
                             QString phone,
                             QString email,
                             QString content)
{

    currentItem->name = name;
    currentItem->description = description;
    currentItem->phone = phone;
    currentItem->email = email;
    currentItem->content = content;

    ui->nameLineEdit->setText(name);
    ui->companyLineEdit->setText(description);
    ui->phoneLineEdit->setText(phone);
    ui->emailLineEdit->setText(email);
    ui->contentPlainTextEdit->setPlainText(content);

    QSqlQuery query;
    query.exec("UPDATE contacts SET name = '" + name +
               "', description = '" + description +
               "', phone = '" + phone +
               "', email = '" + email +
               "', content = '" + content +
               "' WHERE id = " + QString::number(currentItem->uniqueId));



    Master *master = qobject_cast<Master *>(masterWidget);
    master->updateContactList();
}



void Contact::startAnimation()
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


void Contact::endAnimation()
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



Contact::~Contact()
{
    delete ui;

    delete fadeEffect;
    delete animation;

    delete currentItem;
}




