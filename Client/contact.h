#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>

#include "contact_item.h"

namespace Ui { class Contact; }

class Contact : public QWidget
{
    Q_OBJECT

public:


private:
    Ui::Contact *ui;

    QStackedWidget *mainStackedWidget;
    QWidget *masterWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;


    ContactItem *currentItem;


public:
    Contact(QWidget *parent,
         QStackedWidget *mainStackedWidget,
         ContactItem *item);

    ~Contact();

    void contactChanged(QString name,
                        QString description,
                        QString phone,
                        QString email,
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
