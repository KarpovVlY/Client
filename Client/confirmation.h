#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include <QWidget>
#include <QStackedWidget>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>


#include "client.h"
#include "cryptopp.h"


namespace Ui { class Confirmation; }

class Confirmation : public QWidget
{
    Q_OBJECT


private:
    Ui::Confirmation *ui;

    QWidget *masterWidget;
    QWidget *masterMasterWidget;


    QStackedWidget *mainStackedWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;


private:
    Client *client;
    cryptopp *crypto;


public:
    Confirmation(QWidget *parent,
                 QStackedWidget *mainStackedWidget,
                 QWidget *masterWidget,
                 Client *client,
                 cryptopp *crypto,
                 bool type);

    ~Confirmation();

    void startAnimation();
    void endAnimation();


private slots:
    void on_cancelButon_clicked();
    void on_confirmButton_clicked();
};

#endif
