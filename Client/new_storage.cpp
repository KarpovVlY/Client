#include "new_storage.h"
#include "ui_new_storage.h"

#include "master.h"
#include "storage.h"


NewStorage::NewStorage(QWidget *parent,
                       QStackedWidget *mainStackedWidget) :
                       QWidget(parent),
                       ui(new Ui::NewStorage)
{
    ui->setupUi(this);


    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

    ui->infoTextEdit->setPlainText("");
    ui->contentTextEdit->setPlainText("");

    isNewStorageFromMaster = true;
}


NewStorage::NewStorage(QWidget *parent,
                       QStackedWidget *mainStackedWidget,
                       QString name,
                       QString description,
                       QString login,
                       QString password,
                       QString info,
                       QString content) :
                       QWidget(parent),
                       ui(new Ui::NewStorage)
{
    ui->setupUi(this);


    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

    ui->nameLineEdit->setText(name);
    ui->commentLineEdit->setText(description);
    ui->contentTextEdit->setPlainText(content);

    ui->newStorageLabel->setText("Изменить запись");


    isNewStorageFromMaster = false;
}



void NewStorage::on_cancelButon_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                if(isNewStorageFromMaster)
                {
                    this->mainStackedWidget->setCurrentWidget(masterWidget);
                    Master *master = qobject_cast<Master *>(masterWidget);
                    master->endAnimation();
                }
                else
                {
                    this->mainStackedWidget->setCurrentWidget(masterWidget);
                    Storage *storage = qobject_cast<Storage *>(masterWidget);
                    storage->endAnimation();
                }


                fadeEffect->setOpacity(1);
            });
}


void NewStorage::on_confirmButton_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                if(isNewStorageFromMaster)
                {
                    this->mainStackedWidget->setCurrentWidget(masterWidget);
                    Master *master = qobject_cast<Master *>(masterWidget);

                    master->addNewStorage(ui->nameLineEdit->text(),
                                          ui->commentLineEdit->text(),
                                          ui->loginLineEdit->text(),
                                          ui->passwordLineEdit->text(),
                                          ui->infoTextEdit->toPlainText(),
                                          ui->contentTextEdit->toPlainText());
                    master->endAnimation();

                    ui->nameLineEdit->setText("");
                    ui->commentLineEdit->setText("");
                    ui->loginLineEdit->setText("");
                    ui->passwordLineEdit->setText("");
                    ui->infoTextEdit->setPlainText("");
                    ui->contentTextEdit->setPlainText("");
                }
                else
                {
                    this->mainStackedWidget->setCurrentWidget(masterWidget);
                    Storage *storage = qobject_cast<Storage *>(masterWidget);

                    storage->storageChanged(ui->nameLineEdit->text(),
                                            ui->commentLineEdit->text(),
                                            ui->loginLineEdit->text(),
                                            ui->passwordLineEdit->text(),
                                            ui->infoTextEdit->toPlainText(),
                                            ui->contentTextEdit->toPlainText());
                    storage->endAnimation();
                }


                fadeEffect->setOpacity(1);
            });
}


void NewStorage::startAnimation()
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


void NewStorage::endAnimation()
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


NewStorage::~NewStorage()
{
    delete ui;
}
