#include "note.h"
#include "ui_note.h"

#include "master.h"

Note::Note(QWidget *parent,
           QStackedWidget *mainStackedWidget,
           NoteItem *item) :
           QWidget(parent),
           ui(new Ui::Note)
{
    ui->setupUi(this);

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;

    ui->nameLabel->setText(item->name);
    ui->descriptionLabel->setText(item->description);
    ui->contentPlainTextEdit->setPlainText(item->content);


}


void Note::on_cancelButon_clicked()
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



void Note::startAnimation()
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


void Note::endAnimation()
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


Note::~Note()
{
    delete ui;
}
