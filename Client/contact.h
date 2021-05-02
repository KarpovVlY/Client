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


public:
    Contact(QWidget *parent,
         QStackedWidget *mainStackedWidget,
         ContactItem *item);

    ~Contact();

    void startAnimation();
    void endAnimation();


private slots:
    void on_cancelButon_clicked();
};

#endif
