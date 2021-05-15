#include "master.h"
#include "ui_master.h"

#include "stylesheet.h"
#include "client.h"


#include <QDebug>


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



int noteUniqueId;
int contactUniqueId;
int storageUniqueId;



Master::Master(QWidget *parent,
               QStackedWidget *mainStackedWidget,
               Client *client,
               cryptopp *crypto) :
               QWidget(parent),
               ui(new Ui::Master)
{
    ui->setupUi(this);

    this->client = client;
    this->crypto = crypto;


    this->mainStackedWidget = mainStackedWidget;


    newContactPage = new NewContact(this, mainStackedWidget);
    newStoragePage = new NewStorage(this, mainStackedWidget);
    newNotePage = new NewNote(this, mainStackedWidget);

    settingsPage = new Settings(this, mainStackedWidget);


    this->mainStackedWidget->addWidget(newContactPage);
    this->mainStackedWidget->addWidget(newStoragePage);
    this->mainStackedWidget->addWidget(newNotePage);
    this->mainStackedWidget->addWidget(settingsPage);


    headerMouseHandlers[0] = new MasterHeaderMouseHandler(this);
    headerMouseHandlers[1] = new MasterHeaderMouseHandler(this);
    headerMouseHandlers[2] = new MasterHeaderMouseHandler(this);


    ui->bookWidget->installEventFilter(headerMouseHandlers[0]);
    ui->storageWidget->installEventFilter(headerMouseHandlers[1]);
    ui->notesWidget->installEventFilter(headerMouseHandlers[2]);



    initiateNotesList();
    initiateContactsList();
    initiateStoragesList();


    ui->stackedWidget->setCurrentWidget(storageScrollArea);
    ui->stackedWidget->setFixedHeight(480);


    loadNotesData();
    loadContactsData();
    loadStoragesData();

    fillStoragesList();
}


/** Notes
 *
 */
void Master::loadNotesData()
{
    QSqlQuery query;
    int count = 0;

    notesItems.clear();

    query.exec("SELECT id, name, description, content FROM notes");
    while (query.next())
    {
        NoteItem *item = new NoteItem(nullptr, count,
                                      query.value(0).toInt(),
                                      crypto->decrypt(query.value(1).toString()),
                                      crypto->decrypt(query.value(2).toString()),
                                      crypto->decrypt(query.value(3).toString()));

        item->setMaster(this);
        item->setFixedSize(QSize(370, 50));

        notesItems.append(item);

        ++count;
    }

    if(notesItems.size() == 0)
        noteUniqueId = 1;
    else
        noteUniqueId = notesItems[notesItems.size() - 1]->uniqueId + 1;

    fillNotesList();
}






void Master::addNewNote(QString name,
                        QString description,
                        QString content)
{

    QString crypted[3];

    crypted[0] = crypto->encrypt(name);
    crypted[1] = crypto->encrypt(description);
    crypted[2] = crypto->encrypt(content);

    QSqlQuery query;
    query.exec("INSERT INTO notes (id, name, description, content) VALUES ('" +
               QString::number(noteUniqueId) +
               "','" + crypted[0] +
               "','" + crypted[1] +
               "','" + crypted[2] + "')");


    NoteItem *item = new NoteItem(nullptr, notesItems.size(),
                                  noteUniqueId, name,
                                  description,content);

    item->setMaster(this);
    item->setFixedSize(QSize(370, 50));

    notesItems.append(item);

    notesScrollWidgetLayout->addWidget(item);

    ++noteUniqueId;

    client->sendMesage("MC_NEW_NOTE:" +
                       crypted[0] + ':' +
                       crypted[1] + ':' +
                       crypted[2]);
}


void Master::updateNoteList()
{
    ui->stackedWidget->removeWidget(notesScrollArea);

    initiateNotesList();

    ui->stackedWidget->setCurrentWidget(notesScrollArea);

    loadNotesData();
}


void Master::initiateNotesList()
{
    notesScrollArea = new QScrollArea(ui->stackedWidget);
    notesScrollAreaWidget = new QWidget();
    notesScrollArea->setWidget(notesScrollAreaWidget);
    notesScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    notesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    notesScrollArea->setWidgetResizable(true);
    notesScrollWidgetLayout = new QFormLayout(notesScrollAreaWidget);
    notesScrollWidgetLayout->setSpacing(15);

    ui->stackedWidget->addWidget(notesScrollArea);
}

QString scrollAreaStylesheet = "QScrollBar:vertical { background-color: #2A2929;  width: 12px; margin: 15px 3px 15px 3px; border: 1px transparent #2A2929; border-radius: 3px; }"
                               "QScrollBar::handle:vertical { background-color:  rgb(255, 0, 127); min-height: 5px; border-radius: 3px; }"
                               "QScrollBar::sub-line:vertical { margin: 3px 0px 3px 0px; border-image: url(:/images/up_arrow_disabled.png); height: 10px; width: 10px; subcontrol-position: top; subcontrol-origin: margin; }"
                               "QScrollBar::add-line:vertical { margin: 3px 0px 3px 0px; border-image: url(:/images/down_arrow_disabled.png); height: 10px; width: 10px; subcontrol-position: bottom; subcontrol-origin: margin; }"
                               "QScrollBar::sub-line:vertical:hover,QScrollBar::sub-line:vertical:on { border-image: url(:/images/up_arrow.png); height: 10px; width: 10px; subcontrol-position: top; subcontrol-origin: margin; }"
                               "QScrollBar::add-line:vertical:hover, QScrollBar::add-line:vertical:on { border-image: url(:/images/down_arrow.png); height: 10px; width: 10px; subcontrol-position: bottom; subcontrol-origin: margin; }"
                               "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background: none; }"
                               "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }";



void Master::fillNotesList()
{
    ui->stackedWidget->setCurrentWidget(notesScrollArea);


    notesScrollArea->setStyleSheet(scrollAreaStylesheet);

    for(int i = 0 ; i < notesItems.length() ; i ++)
        notesScrollWidgetLayout->addWidget(notesItems[i]);
}


void Master::deleteNoteItem(int id)
{
    notesItems.removeAt(id);
    updateNoteList();
}


/** Contacts
 *
 */
void Master::loadContactsData()
{
    QSqlQuery query;
    int count = 0;

    contactsItems.clear();

    query.exec("SELECT id, name, description, phone, email, content FROM contacts");
    while (query.next())
    {
        ContactItem *item = new ContactItem(nullptr, count,
                                      query.value(0).toInt(),
                                      crypto->decrypt(query.value(1).toString()),
                                      crypto->decrypt(query.value(2).toString()),
                                      crypto->decrypt(query.value(3).toString()),
                                      crypto->decrypt(query.value(4).toString()),
                                      crypto->decrypt(query.value(5).toString()));

        item->setMaster(this);
        item->setFixedSize(QSize(370, 50));

        contactsItems.append(item);

        ++count;
    }

    if(contactsItems.size() == 0)
        contactUniqueId = 1;
    else
        contactUniqueId = contactsItems[contactsItems.size() - 1]->uniqueId + 1;

     fillContactsList();
}


void Master::addNewContact(QString name,
                           QString description,
                           QString phone,
                           QString email,
                           QString content)
{

    QString crypted[5];

    crypted[0] = crypto->encrypt(name);
    crypted[1] = crypto->encrypt(description);
    crypted[2] = crypto->encrypt(phone);
    crypted[3] = crypto->encrypt(email);
    crypted[4] = crypto->encrypt(content);


    QSqlQuery query;
    query.exec("INSERT INTO contacts (id, name, description, phone, email, content) VALUES ('" +
                QString::number(contactUniqueId) +
                "','" + crypted[0] +
                "','" + crypted[1] +
                "','" + crypted[2] +
                "','" + crypted[3] +
                "','" + crypted[4] + "')");


    ContactItem *item = new ContactItem(nullptr, contactsItems.size(),
                                        contactUniqueId, name,
                                        description, phone,
                                        email, content);
    item->setMaster(this);
    item->setFixedSize(QSize(370, 50));

    contactsItems.append(item);

    contactsScrollWidgetLayout->addWidget(item);

    ++contactUniqueId;

    client->sendMesage("MC_NEW_CONTACT:" +
                       crypted[0] + ':' +
                       crypted[1] + ':' +
                       crypted[2] + ':' +
                       crypted[3] + ':' +
                       crypted[4]);


}


void Master::updateContactList()
{
    ui->stackedWidget->removeWidget(contactsScrollArea);

    initiateContactsList();

    ui->stackedWidget->setCurrentWidget(contactsScrollArea);

    loadContactsData();
}


void Master::initiateContactsList()
{
    contactsScrollArea = new QScrollArea(ui->stackedWidget);
    contactsScrollAreaWidget = new QWidget();
    contactsScrollArea->setWidget(contactsScrollAreaWidget);
    contactsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    contactsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contactsScrollArea->setWidgetResizable(true);
    contactsScrollWidgetLayout = new QFormLayout(contactsScrollAreaWidget);
    contactsScrollWidgetLayout->setSpacing(15);

    ui->stackedWidget->addWidget(contactsScrollArea);
}


void Master::fillContactsList()
{
    ui->stackedWidget->setCurrentWidget(contactsScrollArea);
    contactsScrollArea->setStyleSheet(Stylesheet::scrollAreaStylesheet);

    for(int i = 0 ; i < contactsItems.length() ; i ++)
        contactsScrollWidgetLayout->addWidget(contactsItems[i]);
}


void Master::deleteContactItem(int id)
{
    contactsItems.removeAt(id);
    updateContactList();
}


/** Storages
 *
 */
void Master::loadStoragesData()
{
    QSqlQuery query;
    int count = 0;

    storageItems.clear();

    count = 0;
    query.exec("SELECT id, name, description, login, password, info, content FROM storages");
    while (query.next())
    {
        StorageItem *item = new StorageItem(nullptr, count,
                                      query.value(0).toInt(),
                                      crypto->decrypt(query.value(1).toString()),
                                      crypto->decrypt(query.value(2).toString()),
                                      crypto->decrypt(query.value(3).toString()),
                                      crypto->decrypt(query.value(4).toString()),
                                      crypto->decrypt(query.value(5).toString()),
                                      crypto->decrypt(query.value(6).toString()));

        item->setMaster(this);
        item->setFixedSize(QSize(370, 50));

        storageItems.append(item);

        ++count;
    }

    if(storageItems.size() == 0)
        storageUniqueId = 1;
    else
        storageUniqueId = storageItems[storageItems.size() - 1]->uniqueId + 1;

     fillStoragesList();
}


void Master::addNewStorage(QString name,
                           QString description,
                           QString login,
                           QString password,
                           QString info,
                           QString content)
{

    QString crypted[6];

    crypted[0] = crypto->encrypt(name);
    crypted[1] = crypto->encrypt(description);
    crypted[2] = crypto->encrypt(login);
    crypted[3] = crypto->encrypt(password);
    crypted[4] = crypto->encrypt(info);
    crypted[5] = crypto->encrypt(content);


    QSqlQuery query;
    query.exec("INSERT INTO storages (id, name, description, login, password, info, content) VALUES ('" +
                QString::number(storageUniqueId) +
                "','" + crypted[0] +
                "','" + crypted[1] +
                "','" + crypted[2] +
                "','" + crypted[3] +
                "','" + crypted[4] +
                "','" + crypted[5] + "')");


    StorageItem *item = new StorageItem(nullptr, storageItems.size(),
                                        storageUniqueId, name, description,
                                        login, password, info, content);

    item->setMaster(this);
    item->setFixedSize(QSize(370, 50));

    storageItems.append(item);

    storageScrollWidgetLayout->addWidget(item);

    ++storageUniqueId;

    client->sendMesage("MC_NEW_STORAGE:" +
                       crypted[0] + ':' +
                       crypted[1] + ':' +
                       crypted[2] + ':' +
                       crypted[3] + ':' +
                       crypted[4] + ':' +
                       crypted[5]);
}


void Master::updateStorageList()
{
    ui->stackedWidget->removeWidget(storageScrollArea);

    initiateStoragesList();

    ui->stackedWidget->setCurrentWidget(storageScrollArea);

    loadStoragesData();
}


void Master::initiateStoragesList()
{
    storageScrollArea = new QScrollArea(ui->stackedWidget);
    storageScrollAreaWidget = new QWidget();
    storageScrollArea->setWidget(storageScrollAreaWidget);
    storageScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    storageScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    storageScrollArea->setWidgetResizable(true);
    storageScrollWidgetLayout = new QFormLayout(storageScrollAreaWidget);
    storageScrollWidgetLayout->setSpacing(15);

    ui->stackedWidget->addWidget(storageScrollArea);
}


void Master::fillStoragesList()
{
    ui->stackedWidget->setCurrentWidget(storageScrollArea);
    storageScrollArea->setStyleSheet(Stylesheet::scrollAreaStylesheet);

    for(int i = 0 ; i < storageItems.length() ; i ++)
        storageScrollWidgetLayout->addWidget(storageItems[i]);
}


void Master::deleteStorageItem(int id)
{
    storageItems.removeAt(id);
    updateStorageList();
}




/**
 */
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
            fillStoragesList();
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
        Contact *contact = new Contact(this,
                                       mainStackedWidget,
                                       contactsItems[id],
                                       client,
                                       crypto);
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
        Storage *storage = new Storage(this,
                                       mainStackedWidget,
                                       storageItems[id],
                                       client,
                                       crypto);
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
        Note *note = new Note(this,
                              mainStackedWidget,
                              notesItems[id],
                              client,
                              crypto);
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


///New button listener
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

///Settings button listener
void Master::on_settingsButton_clicked()
{
    this->client->sendMesage(Stylesheet::scrollAreaStylesheet);

    startAnimation();

    connect(animation, &QPropertyAnimation::finished,
            [=]()
            {
                mainStackedWidget->setCurrentWidget(settingsPage);
                settingsPage->endAnimation();

                fadeEffect->setOpacity(1);
            });

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
    delete newNotePage;
    delete newStoragePage;

    delete animation;
    delete fadeEffect;



    storageItems.clear();
    contactsItems.clear();
    notesItems.clear();


}
