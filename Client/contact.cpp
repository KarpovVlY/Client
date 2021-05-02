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

    ui->nameLabel->setText(item->name);
    ui->descriptionLabel->setText(item->description);
    ui->phoneLabel->setText(item->phone);
    ui->emailLabel->setText(item->email);
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
}

