#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QStackedWidget>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include "client.h"
#include "cryptopp.h"

#include "confirmation.h"

namespace Ui { class SignUp; }

class SignUp : public QWidget
{
    Q_OBJECT


private:
    Ui::SignUp *ui;

    QStackedWidget *mainStackedWidget;
    QWidget *masterWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;


private:
     Client *client;
     cryptopp *crypto;

     Confirmation *confirmationPage;


public:
    SignUp(QWidget *parent,
           QStackedWidget *mainStackedWidget,
           Client *client,
           cryptopp *crypto);

    ~SignUp();


    void startAnimation();
    void endAnimation();

    void changePageToLogin();

private:


private slots:
    void on_cancelButon_clicked();
    void on_confirmButton_clicked();


};

#endif
