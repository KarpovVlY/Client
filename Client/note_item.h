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

private:
    Ui::NoteItem *ui;

    int id;

public:
    NoteItem(QWidget *parent,
             int id,
             QString name,
             QString description,
             QString content);

    ~NoteItem();

    void setMaster(QObject *parent);

private:


};

#endif
