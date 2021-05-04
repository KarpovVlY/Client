#include "settings.h"
#include "ui_settings.h"

#include "master.h"

Settings::Settings(QWidget *parent,
                   QStackedWidget *mainStackedWidget) :
                   QWidget(parent),
                   ui(new Ui::Settings)
{
    ui->setupUi(this);

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

}

void Settings::on_cancelButon_clicked()
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


void Settings::on_whiteRadioButton_clicked()
{



}


void Settings::on_blackRadioButton_clicked()
{



}


void Settings::startAnimation()
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

void Settings::endAnimation()
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


Settings::~Settings()
{
    delete ui;
}
