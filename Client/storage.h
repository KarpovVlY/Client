#ifndef STORAGE_H
#define STORAGE_H

#include <QWidget>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>

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

public:
    Storage(QWidget *parent,
         QStackedWidget *mainStackedWidget,
         StorageItem *item);

    ~Storage();

    void startAnimation();
    void endAnimation();


private:


private slots:
    void on_cancelButon_clicked();


};

#endif
