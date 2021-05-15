#include "storage.h"
#include "ui_storage.h"

#include "master.h"

NewStorage *newStoragePage;

Storage::Storage(QWidget *parent,
           QStackedWidget *mainStackedWidget,
           StorageItem *item,
           Client *client,
           cryptopp *crypt) :
           QWidget(parent),
           ui(new Ui::Storage)
{
    ui->setupUi(this);

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;


    this->currentItem = item;
    this->client = client;
    this->crypt = crypt;


    ui->nameLineEdit->setText(item->name);
    ui->descriptionLineEdit->setText(item->description);
    ui->loginLineEdit->setText(item->login);
    ui->passwordLineEdit->setText(item->password);
    ui->infoPlainTextEdit->setPlainText(item->info);
    ui->contentPlainTextEdit->setPlainText(item->content);


}

void Storage::on_cancelButon_clicked()
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


void Storage::on_editButton_clicked()
{
    newStoragePage = new NewStorage(this,
                                    mainStackedWidget,
                                    currentItem->name,
                                    currentItem->description,
                                    currentItem->login,
                                    currentItem->password,
                                    currentItem->info,
                                    currentItem->content);

    mainStackedWidget->addWidget(newStoragePage);

    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                mainStackedWidget->setCurrentWidget(newStoragePage);

                newStoragePage->endAnimation();

                fadeEffect->setOpacity(1);
            });

}


void Storage::on_deleteButon_clicked()
{

    QSqlQuery query;


    QString a[6];
    query.exec("SELECT name, description, login, password, info, content FROM storages WHERE id = " + QString::number(currentItem->uniqueId));
    while (query.next())
    {
        a[0] = query.value(0).toString(),
        a[1] = query.value(1).toString(),
        a[2] = query.value(2).toString();
        a[3] = query.value(3).toString();
        a[4] = query.value(4).toString();
        a[5] = query.value(5).toString();
    }

    client->sendMesage("MC_DROP_STORAGE:" +
                       a[0] + ':' +
                       a[1] + ':' +
                       a[2] + ':' +
                       a[3] + ':' +
                       a[4] + ':' +
                       a[5]);


    query.exec("DELETE FROM storages WHERE id = " + QString::number(currentItem->uniqueId));



    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                this->mainStackedWidget->setCurrentWidget(masterWidget);
                Master *master = qobject_cast<Master *>(masterWidget);
                master->endAnimation();
                master->deleteStorageItem(currentItem->id);

                fadeEffect->setOpacity(1);
            });

}


void Storage::storageChanged(QString name,
                             QString description,
                             QString login,
                             QString password,
                             QString info,
                             QString content)
{
    mainStackedWidget->removeWidget(newStoragePage);

    QString previous[6];

    previous[0] = crypt->encrypt(currentItem->name);
    previous[1] = crypt->encrypt(currentItem->description);
    previous[2] = crypt->encrypt(currentItem->login);
    previous[3] = crypt->encrypt(currentItem->password);
    previous[4] = crypt->encrypt(currentItem->info);
    previous[5] = crypt->encrypt(currentItem->content);


    currentItem->name = name;
    currentItem->description = description;
    currentItem->login = login;
    currentItem->password = password;
    currentItem->info = info;
    currentItem->content = content;

    ui->nameLineEdit->setText(name);
    ui->descriptionLineEdit->setText(description);
    ui->loginLineEdit->setText(login);
    ui->passwordLineEdit->setText(password);
    ui->infoPlainTextEdit->setPlaceholderText(info);
    ui->contentPlainTextEdit->setPlainText(content);


    QString crypted[6];

    crypted[0] = crypt->encrypt(name);
    crypted[1] = crypt->encrypt(description);
    crypted[2] = crypt->encrypt(login);
    crypted[3] = crypt->encrypt(password);
    crypted[4] = crypt->encrypt(info);
    crypted[5] = crypt->encrypt(content);


    QSqlQuery query;
    query.exec("UPDATE storages SET name = '" + crypted[0] +
               "', description = '" + crypted[1] +
               "', login = '" + crypted[2] +
               "', password = '" + crypted[3] +
               "', info = '" + crypted[4] +
               "', content = '" + crypted[5] +
               "' WHERE id = " + QString::number(currentItem->uniqueId));


    client->sendMesage("MC_EDIT_STORAGE:" +
                       previous[0] + ':' +
                       previous[1] + ':' +
                       previous[2] + ':' +
                       previous[3] + ':' +
                       previous[4] + ':' +
                       previous[5] + ':' +
                       crypted[0] + ':' +
                       crypted[1] + ':' +
                       crypted[2] + ':' +
                       crypted[3] + ':' +
                       crypted[4] + ':' +
                       crypted[5]);


    Master *master = qobject_cast<Master *>(masterWidget);
    master->updateStorageList();
}



void Storage::startAnimation()
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


void Storage::endAnimation()
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

Storage::~Storage()
{
    delete ui;
}



