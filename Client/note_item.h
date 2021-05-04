#ifndef NOTE_ITEM_H
#define NOTE_ITEM_H

#include <QWidget>
#include "master_list_item_mouse_handler.h"

namespace Ui { class NoteItem; }

class NoteItem : public QWidget
{
    Q_OBJECT


public:
    QString name;
    QString description;
    QString content;

    int uniqueId;

    int id;
private:
    Ui::NoteItem *ui;



public:
    NoteItem(QWidget *parent,
             int id,
             int uniqueId,
             QString name,
             QString description,
             QString content);

    ~NoteItem();

    void setMaster(QObject *parent);

private:


};

#endif
