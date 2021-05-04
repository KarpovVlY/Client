#include "storage.h"
#include "ui_storage.h"

#include "master.h"

NewStorage *newStoragePage;

Storage::Storage(QWidget *parent,
           QStackedWidget *mainStackedWidget,
           StorageItem *item) :
           QWidget(parent),
           ui(new Ui::Storage)
{
    ui->setupUi(this);

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;


    this->currentItem = item;


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


    QSqlQuery query;
    query.exec("UPDATE storages SET name = '" + name +
               "', description = '" + description +
               "', login = '" + login +
               "', password = '" + password +
               "', info = '" + info +
               "', content = '" + content +
               "' WHERE id = " + QString::number(currentItem->uniqueId));



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



