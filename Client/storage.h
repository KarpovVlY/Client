#ifndef STORAGE_H
#define STORAGE_H

#include <QWidget>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>

#include "cryptopp.h"


#include "client.h"
#include "storage_item.h"

namespace Ui { class Storage; }

class Storage : public QWidget
{
    Q_OBJECT


public:

private:
    Ui::Storage *ui;

    QStackedWidget *mainStackedWidget;
    QWidget *masterWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;

    StorageItem *currentItem;
    Client *client;
    cryptopp *crypt;


public:
    Storage(QWidget *parent,
         QStackedWidget *mainStackedWidget,
         StorageItem *item,
         Client *client,
         cryptopp *crypt);

    ~Storage();

    void storageChanged(QString name,
                        QString description,
                        QString login,
                        QString password,
                        QString info,
                        QString content);


    void startAnimation();
    void endAnimation();


private:

    void cancel();
    void deleteItem();


private slots:
    void on_cancelButon_clicked();

    void on_editButton_clicked();
    void on_deleteButon_clicked();
};

#endif
