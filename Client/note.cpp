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


    this->currentItem = item;



    ui->nameLineEdit->setText(item->name);
    ui->descriptionLineEdit->setText(item->description);
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


void Note::on_editButton_clicked()
{

    NewNote *newNotePage = new NewNote(this,
                                       mainStackedWidget,
                                       currentItem->name,
                                       currentItem->description,
                                       currentItem->content);

    mainStackedWidget->addWidget(newNotePage);

    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                mainStackedWidget->setCurrentWidget(newNotePage);

                newNotePage->endAnimation();

                fadeEffect->setOpacity(1);
            });
}



void Note::on_deleteButon_clicked()
{
    QSqlQuery query;
    query.exec("DELETE FROM notes WHERE id = " + QString::number(currentItem->uniqueId));


    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                this->mainStackedWidget->setCurrentWidget(masterWidget);
                Master *master = qobject_cast<Master *>(masterWidget);
                master->endAnimation();
                master->deleteNoteItem(currentItem->id);

                fadeEffect->setOpacity(1);
            });
}


void Note::noteChanged(QString name,
                       QString description,
                       QString content)
{
    currentItem->name = name;
    currentItem->description = description;
    currentItem->content = content;

    ui->nameLineEdit->setText(name);
    ui->descriptionLineEdit->setText(description);
    ui->contentPlainTextEdit->setPlainText(content);

    QSqlQuery query;
    query.exec("UPDATE notes SET name = '" + name +
               "', description = '" + description +
               "', content = '" + content +
               "' WHERE id = " + QString::number(currentItem->uniqueId));



    Master *master = qobject_cast<Master *>(masterWidget);
    master->updateNoteList();
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

    delete fadeEffect;
    delete animation;

    delete currentItem;
}

