#include "contact.h"
#include "ui_contact.h"

#include "master.h"

Contact::Contact(QWidget *parent,
                 QStackedWidget *mainStackedWidget,
                 ContactItem *item,
                 Client *client,
                 cryptopp *crypt) :
                 QWidget(parent),
                 ui(new Ui::Contact)
{
    ui->setupUi(this);

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;


    this->currentItem = item;
    this->client = client;
    this->crypt = crypt;


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

    QString a[5];
    query.exec("SELECT name, description, phone, email, content FROM contacts WHERE id = " + QString::number(currentItem->uniqueId));
    while (query.next())
    {
        a[0] = query.value(0).toString(),
        a[1] = query.value(1).toString(),
        a[2] = query.value(2).toString();
        a[3] = query.value(3).toString();
        a[4] = query.value(4).toString();
    }

    client->sendMesage("MC_DROP_CONTACT:" +
                       a[0] + ':' +
                       a[1] + ':' +
                       a[2] + ':' +
                       a[3] + ':' +
                       a[4]);


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
    QString previous[5];

    previous[0] = crypt->encrypt(currentItem->name);
    previous[1] = crypt->encrypt(currentItem->description);
    previous[2] = crypt->encrypt(currentItem->phone);
    previous[3] = crypt->encrypt(currentItem->email);
    previous[4] = crypt->encrypt(currentItem->content);


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


    QString crypted[5];

    crypted[0] = crypt->encrypt(name);
    crypted[1] = crypt->encrypt(description);
    crypted[2] = crypt->encrypt(phone);
    crypted[3] = crypt->encrypt(email);
    crypted[4] = crypt->encrypt(content);


    QSqlQuery query;
    query.exec("UPDATE contacts SET name = '" + crypted[0] +
               "', description = '" + crypted[1] +
               "', phone = '" + crypted[2] +
               "', email = '" + crypted[3] +
               "', content = '" + crypted[4] +
               "' WHERE id = " + QString::number(currentItem->uniqueId));


    client->sendMesage("MC_EDIT_CONTACT:" +
                       previous[0] + ':' +
                       previous[1] + ':' +
                       previous[2] + ':' +
                       previous[3] + ':' +
                       previous[4] + ':' +
                       crypted[0] + ':' +
                       crypted[1] + ':' +
                       crypted[2] + ':' +
                       crypted[3] + ':' +
                       crypted[4]);


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




