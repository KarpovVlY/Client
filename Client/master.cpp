#include "master.h"
#include "ui_master.h"

#include <QDebug>


QString scrollAreaStylesheet = "QScrollBar:vertical { background-color: #2A2929;  width: 12px; margin: 15px 3px 15px 3px; border: 1px transparent #2A2929; border-radius: 3px; }"
                               "QScrollBar::handle:vertical { background-color:  rgb(255, 0, 127); min-height: 5px; border-radius: 3px; }"
                               "QScrollBar::sub-line:vertical { margin: 3px 0px 3px 0px; border-image: url(:/images/up_arrow_disabled.png); height: 10px; width: 10px; subcontrol-position: top; subcontrol-origin: margin; }"
                               "QScrollBar::add-line:vertical { margin: 3px 0px 3px 0px; border-image: url(:/images/down_arrow_disabled.png); height: 10px; width: 10px; subcontrol-position: bottom; subcontrol-origin: margin; }"
                               "QScrollBar::sub-line:vertical:hover,QScrollBar::sub-line:vertical:on { border-image: url(:/images/up_arrow.png); height: 10px; width: 10px; subcontrol-position: top; subcontrol-origin: margin; }"
                               "QScrollBar::add-line:vertical:hover, QScrollBar::add-line:vertical:on { border-image: url(:/images/down_arrow.png); height: 10px; width: 10px; subcontrol-position: bottom; subcontrol-origin: margin; }"
                               "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background: none; }"
                               "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }";



MasterHeaderMouseHandler *headerMouseHandlers[3];


QScrollArea *contactsScrollArea;
QScrollArea *storageScrollArea;
QScrollArea *notesScrollArea;


QWidget *contactsScrollAreaWidget;
QWidget *storageScrollAreaWidget;
QWidget *notesScrollAreaWidget;


QFormLayout *contactsScrollWidgetLayout;
QFormLayout *storageScrollWidgetLayout;
QFormLayout *notesScrollWidgetLayout;



Master::Master(QWidget *parent,
               QStackedWidget *mainStackedWidget) :
               QWidget(parent),
               ui(new Ui::Master)
{
    ui->setupUi(this);





    this->mainStackedWidget = mainStackedWidget;


    newContactPage = new NewContact(this, mainStackedWidget);
    newStoragePage = new NewStorage(this, mainStackedWidget);
    newNotePage = new NewNote(this, mainStackedWidget);


    this->mainStackedWidget->addWidget(newContactPage);
    this->mainStackedWidget->addWidget(newStoragePage);
    this->mainStackedWidget->addWidget(newNotePage);




    headerMouseHandlers[0] = new MasterHeaderMouseHandler(this);
    headerMouseHandlers[1] = new MasterHeaderMouseHandler(this);
    headerMouseHandlers[2] = new MasterHeaderMouseHandler(this);


    ui->bookWidget->installEventFilter(headerMouseHandlers[0]);
    ui->storageWidget->installEventFilter(headerMouseHandlers[1]);
    ui->notesWidget->installEventFilter(headerMouseHandlers[2]);




    storageScrollArea = new QScrollArea(ui->stackedWidget);
    contactsScrollArea = new QScrollArea(ui->stackedWidget);
    notesScrollArea = new QScrollArea(ui->stackedWidget);


    storageScrollAreaWidget = new QWidget();
    contactsScrollAreaWidget = new QWidget();
    notesScrollAreaWidget = new QWidget();


    storageScrollArea->setWidget(storageScrollAreaWidget);
    storageScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    storageScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    storageScrollArea->setWidgetResizable(true);

    contactsScrollArea->setWidget(contactsScrollAreaWidget);
    contactsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    contactsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contactsScrollArea->setWidgetResizable(true);

    notesScrollArea->setWidget(notesScrollAreaWidget);
    notesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    notesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    notesScrollArea->setWidgetResizable(true);


    storageScrollWidgetLayout = new QFormLayout(storageScrollAreaWidget);
    contactsScrollWidgetLayout = new QFormLayout(contactsScrollAreaWidget);
    notesScrollWidgetLayout = new QFormLayout(notesScrollAreaWidget);

    storageScrollWidgetLayout->setSpacing(15);
    contactsScrollWidgetLayout->setSpacing(15);
    notesScrollWidgetLayout->setSpacing(15);



    ui->stackedWidget->addWidget(storageScrollArea);
    ui->stackedWidget->addWidget(contactsScrollArea);
    ui->stackedWidget->addWidget(notesScrollArea);



    ui->stackedWidget->setCurrentWidget(storageScrollArea);



ui->stackedWidget->setFixedHeight(480);


    loadData();
    fillStorageList();
    //fillListItems(storageItems, 1);
}





void Master::loadData()
{
    for(int i = 0 ; i < 15 ; i ++)
    {
        StorageItem *item = new StorageItem(nullptr, i, "storage", QString::number(i), "", "", "", "");

        item->setMaster(this);
        item->setFixedSize(QSize(370, 50));

        storageItems.append(item);
    }


    for(int i = 0 ; i < 3 ; i ++)
    {
        NoteItem *item = new NoteItem(nullptr, i, "note", QString::number(i), "");

        item->setMaster(this);
        item->setFixedSize(QSize(370, 50));

        notesItems.append(item);
    }

    for(int i = 0 ; i < 5 ; i ++)
    {
        ContactItem *item = new ContactItem(nullptr, i, "contact", QString::number(i), "", "", "");

        item->setMaster(this);
        item->setFixedSize(QSize(370, 50));

        contactsItems.append(item);
    }


}






void Master::addNewNote(QString name,
                        QString description,
                        QString content)
{
    NoteItem *item = new NoteItem(nullptr, notesItems.size(), name, description,
                                  content);

    item->setMaster(this);
    item->setFixedSize(QSize(370, 50));

    notesItems.append(item);

    notesScrollWidgetLayout->addWidget(item);
}

void Master::addNewContact(QString name,
                           QString description,
                           QString phone,
                           QString email,
                           QString content)
{
    ContactItem *item = new ContactItem(nullptr, contactsItems.size(), name, description,
                                        phone, email, content);
    item->setMaster(this);
    item->setFixedSize(QSize(370, 50));

    contactsItems.append(item);

    contactsScrollWidgetLayout->addWidget(item);
}


void Master::addNewStorage(QString name,
                           QString description,
                           QString login,
                           QString password,
                           QString info,
                           QString content)
{
    StorageItem *item = new StorageItem(nullptr, contactsItems.size(), name, description,
                                        login, password, info, content);

    item->setMaster(this);
    item->setFixedSize(QSize(370, 50));

    storageItems.append(item);

    storageScrollWidgetLayout->addWidget(item);
}


void Master::tabChanged(short id)
{
    for(int i = 0 ; i < 3 ; i ++)
        if(i != id)
            headerMouseHandlers[i]->refresh();


    if(id == 0)
    {
        if(currentId != 0)
            fillContactsList();

    }
    else if(id == 1)
    {
        if(currentId != 1)
            fillStorageList();
    }
    else
    {
        if(currentId != 2)
            fillNotesList();

    }

    currentId = id;
}


void Master::itemSelected(int id,
                          short type)
{

    if(type == 0)
    {
        Contact *contact = new Contact(this, mainStackedWidget, contactsItems[id]);
        this->mainStackedWidget->addWidget(contact);

        startAnimation();

        connect(animation, &QPropertyAnimation::finished,
                [=]()
                {

                    this->mainStackedWidget->setCurrentWidget(contact);

                    contact->endAnimation();

                    fadeEffect->setOpacity(1);
                });
    }
    else if(type == 1)
    {
        Storage *storage = new Storage(this, mainStackedWidget, storageItems[id]);
        this->mainStackedWidget->addWidget(storage);


        startAnimation();

        connect(animation, &QPropertyAnimation::finished,
                [=]()
                {

                    this->mainStackedWidget->setCurrentWidget(storage);

                    storage->endAnimation();

                    fadeEffect->setOpacity(1);
                });
    }
    else
    {
        Note *note = new Note(this, mainStackedWidget, notesItems[id]);
        this->mainStackedWidget->addWidget(note);

        startAnimation();

        connect(animation, &QPropertyAnimation::finished,
                [=]()
                {

                    this->mainStackedWidget->setCurrentWidget(note);

                    note->endAnimation();

                    fadeEffect->setOpacity(1);
                });
    }




}

void Master::fillNotesList()
{
    ui->stackedWidget->setCurrentWidget(notesScrollArea);
    notesScrollArea->setStyleSheet(scrollAreaStylesheet);

    for(int i = 0 ; i < notesItems.length() ; i ++)
        notesScrollWidgetLayout->addWidget(notesItems[i]);
}


void Master::fillContactsList()
{
    ui->stackedWidget->setCurrentWidget(contactsScrollArea);
    contactsScrollArea->setStyleSheet(scrollAreaStylesheet);

    for(int i = 0 ; i < contactsItems.length() ; i ++)
        contactsScrollWidgetLayout->addWidget(contactsItems[i]);

}


void Master::fillStorageList()
{
    ui->stackedWidget->setCurrentWidget(storageScrollArea);
    storageScrollArea->setStyleSheet(scrollAreaStylesheet);

    for(int i = 0 ; i < storageItems.length() ; i ++)
        storageScrollWidgetLayout->addWidget(storageItems[i]);
}

void Master::fillListItems(QList<MasterListPart*> items, short id)
{
    QFormLayout *bufferLayout;
    QScrollArea *bufferScrollArea;

    if(id == 0)
    {
        bufferLayout = contactsScrollWidgetLayout;
        bufferScrollArea = contactsScrollArea;
    }
    else if(id == 1)
    {
        bufferLayout = storageScrollWidgetLayout;
        bufferScrollArea = storageScrollArea;
    }
    else
    {
        bufferLayout = notesScrollWidgetLayout;
        bufferScrollArea = notesScrollArea;
    }

    ui->stackedWidget->setCurrentWidget(bufferScrollArea);
    bufferScrollArea->setStyleSheet(scrollAreaStylesheet);

    for(int i = 0 ; i < items.length() ; i ++)
        bufferLayout->addWidget(items[i]);
}



void Master::on_newButton_clicked()
{
    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                if(currentId == 0)
                {
                    mainStackedWidget->setCurrentWidget(newContactPage);
                    newContactPage->endAnimation();
                }
                else if(currentId == 1)
                {
                    mainStackedWidget->setCurrentWidget(newStoragePage);
                    newStoragePage->endAnimation();
                }
                else if(currentId == 2)
                {
                    mainStackedWidget->setCurrentWidget(newNotePage);
                    newNotePage->endAnimation();
                }


                fadeEffect->setOpacity(1);
            });
}


void Master::on_settingsButton_clicked()
{


}


void Master::on_accountButton_clicked()
{

}


void Master::startAnimation()
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


void Master::endAnimation()
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


Master::~Master()
{
    delete ui;
    delete newContactPage;

    delete animation;
    delete fadeEffect;


    delete mainStackedWidget;

    delete contactsScrollArea;
    delete contactsScrollAreaWidget;
    delete contactsScrollWidgetLayout;

    delete storageScrollArea;
    delete storageScrollAreaWidget;
    delete storageScrollWidgetLayout;

    delete notesScrollArea;
    delete notesScrollAreaWidget;
    delete notesScrollWidgetLayout;


    storageItems.clear();
    contactsItems.clear();
    notesItems.clear();

}
