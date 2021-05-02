#include "storage.h"
#include "ui_storage.h"

#include "master.h"

Storage::Storage(QWidget *parent,
           QStackedWidget *mainStackedWidget,
           StorageItem *item) :
           QWidget(parent),
           ui(new Ui::Storage)
{
    ui->setupUi(this);

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

    ui->nameLabel->setText(item->name);
    ui->descriptionLabel->setText(item->description);
    ui->loginLabel->setText(item->login);
    ui->passwordLabel->setText(item->password);
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

