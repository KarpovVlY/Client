#include "new_note.h"
#include "ui_new_note.h"

#include "master.h"

NewNote::NewNote(QWidget *parent,
                 QStackedWidget *mainStackedWidget) :
                 QWidget(parent),
                 ui(new Ui::NewNote)
{
    ui->setupUi(this);


    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;


}


void NewNote::on_cancelButon_clicked()
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


void NewNote::on_confirmButton_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                this->mainStackedWidget->setCurrentWidget(masterWidget);
                Master *master = qobject_cast<Master *>(masterWidget);

                master->addNewNote(ui->nameLineEdit->text(),
                                   ui->commentLineEdit->text(),
                                   ui->contentTextEdit->toPlainText());
                master->endAnimation();
                fadeEffect->setOpacity(1);
            });
}



void NewNote::startAnimation()
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


void NewNote::endAnimation()
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


NewNote::~NewNote()
{
    delete ui;
}

