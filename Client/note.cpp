#include "note.h"
#include "ui_note.h"

#include "master.h"


Note::Note(QWidget *parent,
           QStackedWidget *mainStackedWidget,
           NoteItem *item,
           Client *client,
           cryptopp *crypt) :
           QWidget(parent),
           ui(new Ui::Note)
{
    ui->setupUi(this);

    this->mainStackedWidget = mainStackedWidget;
    this->masterWidget = parent;


    this->currentItem = item;
    this->client = client;
    this->crypt = crypt;



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

    QString a[3];
    query.exec("SELECT name, description, content FROM notes WHERE id = " + QString::number(currentItem->uniqueId));
    while (query.next())
    {
        a[0] = query.value(0).toString(),
        a[1] = query.value(1).toString(),
        a[2] = query.value(2).toString();
    }

    client->sendMesage("MC_DROP_NOTE:" +
                       a[0] + ':' +
                       a[1] + ':' +
                       a[2]);

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
    QString previous[3];

    previous[0] = crypt->encrypt(currentItem->name);
    previous[1] = crypt->encrypt(currentItem->description);
    previous[2] = crypt->encrypt(currentItem->content);


    currentItem->name = name;
    currentItem->description = description;
    currentItem->content = content;

    ui->nameLineEdit->setText(name);
    ui->descriptionLineEdit->setText(description);
    ui->contentPlainTextEdit->setPlainText(content);


    QString crypted[3];

    crypted[0] = crypt->encrypt(name);
    crypted[1] = crypt->encrypt(description);
    crypted[2] = crypt->encrypt(content);


    QSqlQuery query;
    query.exec("UPDATE notes SET name = '" + crypted[0] +
               "', description = '" + crypted[1] +
               "', content = '" + crypted[2] +
               "' WHERE id = " + QString::number(currentItem->uniqueId));


    client->sendMesage("MC_EDIT_NOTE:" +
                       previous[0] + ':' +
                       previous[1] + ':' +
                       previous[2] + ':' +
                       crypted[0] + ':' +
                       crypted[1] + ':' +
                       crypted[2]);


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

