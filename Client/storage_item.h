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

    int uniqueId;

    int id;
private:
    Ui::StorageItem *ui;



public:
    StorageItem(QWidget *parent,
                int id,
                int uniqueId,
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
