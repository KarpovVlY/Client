#include "new_storage.h"
#include "ui_new_storage.h"

#include "master.h"

NewStorage::NewStorage(QWidget *parent,
                       QStackedWidget *mainStackedWidget) :
                       QWidget(parent),
                       ui(new Ui::NewStorage)
{
    ui->setupUi(this);


    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;
}



void NewStorage::on_cancelButon_clicked()
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


void NewStorage::on_confirmButton_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
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
