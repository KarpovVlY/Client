#ifndef NEW_CONTACT_H
#define NEW_CONTACT_H

#include <QWidget>
#include <QFormLayout>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QLineEdit>
#include <QPushButton>


namespace Ui { class NewContact; }

class NewContact : public QWidget
{
    Q_OBJECT

public:


private:
    Ui::NewContact *ui;
    QFormLayout *newContactScrollLayout;

    QLineEdit *nameLineEdit;
    QLineEdit *companyLineEdit;

    QPushButton *numberPushButton;


    QStackedWidget *mainStackedWidget;
    QWidget *masterWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;

    QList<QLineEdit> editLinesList;


public:
    NewContact(QWidget *parent,
               QStackedWidget *mainStackedWidget);
    ~NewContact();

    void startAnimation();
    void endAnimation();



private:
    void fillList();



private slots:
    void on_confirmButton_clicked();
    void on_cancelButon_clicked();
};

#endif
