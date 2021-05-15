#ifndef MASTER_H
#define MASTER_H



#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QStackedWidget>

#include <QGraphicsOpacityEffect>

#include <QSqlDatabase>
#include <QtSql>

#include "settings.h"

#include "new_contact.h"
#include "new_note.h"
#include "new_storage.h"

#include "master_header_mouse_handler.h"

#include "note_item.h"
#include "contact_item.h"
#include "storage_item.h"

#include "note.h"
#include "contact.h"
#include "storage.h"

#include "aes.h"
#include "client.h"

#include "cryptopp.h"

namespace Ui { class Master; }

class Master : public QWidget
{
    Q_OBJECT


private:
    Ui::Master *ui;

    QStackedWidget *mainStackedWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;

private:
    NewContact *newContactPage;
    NewStorage *newStoragePage;
    NewNote *newNotePage;

    Settings *settingsPage;

    QList <StorageItem *> storageItems;
    QList <ContactItem *> contactsItems;
    QList <NoteItem *> notesItems;


    Client *client;
    cryptopp *crypto;


public:
    short currentId = 1;

public:
    Master(QWidget *parent,
           QStackedWidget *mainStackedWidget,
           Client *client,
           cryptopp *crypto);

    ~Master();

    void startAnimation();
    void endAnimation();



    void itemSelected(int id,
                      short type);



    void addNewNote(QString name,
                    QString description,
                    QString content);

    void addNewContact(QString name,
                       QString description,
                       QString phone,
                       QString email,
                       QString content);

    void addNewStorage(QString name,
                       QString description,
                       QString login,
                       QString password,
                       QString info,
                       QString content);


    void deleteNoteItem(int id);
    void deleteContactItem(int id);
    void deleteStorageItem(int id);


    void updateNoteList();
    void updateContactList();
    void updateStorageList();




private:
    void initiateNotesList();
    void initiateContactsList();
    void initiateStoragesList();

    void loadNotesData();
    void loadContactsData();
    void loadStoragesData();

    void fillNotesList();
    void fillContactsList();
    void fillStoragesList();

    void replenishListItems();



public slots:
    void tabChanged(short id);

private slots:
    void on_newButton_clicked();
    void on_settingsButton_clicked();


};

#endif
