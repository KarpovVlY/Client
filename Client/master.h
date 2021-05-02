#ifndef MASTER_H
#define MASTER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>

#include <QScrollArea>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>

#include "master_list_part.h"

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


    QList <StorageItem *> storageItems;
    QList <ContactItem *> contactsItems;
    QList <NoteItem *> notesItems;



public:
    short currentId = 1;

public:
    Master(QWidget *parent,
           QStackedWidget *mainStackedWidget);

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


    //void startListAnimation();
    //void endListAnimation();



private:

    void loadData();
    void addData();

    void fillListItems(QList<MasterListPart*> items,
                       short id);

    void fillNotesList();
    void fillContactsList();
    void fillStorageList();

    void replenishListItems();




public slots:
    void tabChanged(short id);

private slots:
    void on_newButton_clicked();

    void on_settingsButton_clicked();
    void on_accountButton_clicked();


};

#endif
