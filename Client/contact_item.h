#ifndef CONTACT_ITEM_H
#define CONTACT_ITEM_H

#include <QWidget>
#include "master_list_item_mouse_handler.h"

namespace Ui { class ContactItem; }

class ContactItem : public QWidget
{
    Q_OBJECT


public:
    QString name;
    QString description;
    QString phone;
    QString email;
    QString content;


private:
    Ui::ContactItem *ui;

    int id;

public:
    ContactItem(QWidget *parent,
                int id,
                QString name,
                QString description,
                QString phone,
                QString email,
                QString content);

    ~ContactItem();

    void setMaster(QObject *parent);


private:


};

#endif
