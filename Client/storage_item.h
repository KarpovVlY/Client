#ifndef STORAGE_ITEM_H
#define STORAGE_ITEM_H

#include <QWidget>
#include "master_list_item_mouse_handler.h"

namespace Ui { class StorageItem; }

class StorageItem : public QWidget
{
    Q_OBJECT

public:
    QString name;
    QString description;
    QString login;
    QString password;
    QString info;
    QString content;

private:
    Ui::StorageItem *ui;

    int id;

public:
    StorageItem(QWidget *parent,
                int id,
                QString name,
                QString description,
                QString login,
                QString password,
                QString info,
                QString content);

    ~StorageItem();


    void setMaster(QObject *parent);

private:


};

#endif
