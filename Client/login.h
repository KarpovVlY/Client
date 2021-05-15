#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QStackedWidget>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include "client.h"
#include "cryptopp.h"


#include "signup.h"
#include "confirmation.h"



namespace Ui { class Login; }

class Login : public QWidget
{
    Q_OBJECT

private:
    Ui::Login *ui;

    QStackedWidget *mainStackedWidget;
    QWidget *masterWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;



private:
    Client *client;

    cryptopp *crypto;

    SignUp *signUpPage;
    Confirmation *confirmationPage;



public:
    Login(QWidget *parent,
          QStackedWidget *mainStackedWidget,
          Client *client,
          cryptopp *crypto);

    ~Login();

    void startAnimation();
    void endAnimation();


private slots:
    void on_loginButton_clicked();
    void on_signupButton_clicked();

    void on_radioButton_clicked();
};

#endif
