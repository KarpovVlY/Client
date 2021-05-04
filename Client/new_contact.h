#ifndef NEW_CONTACT_H
#define NEW_CONTACT_H

#include <QWidget>
#include <QFormLayout>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>



namespace Ui { class NewContact; }

class NewContact : public QWidget
{
    Q_OBJECT

public:


private:
    Ui::NewContact *ui;

    QFormLayout *newContactScrollLayout;

    QStackedWidget *mainStackedWidget;
    QWidget *masterWidget;
    QWidget *contactWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;

    bool isNewContactFromMaster;


public:
    NewContact(QWidget *parent,
               QStackedWidget *mainStackedWidget);

    NewContact(QWidget *parent,
               QStackedWidget *mainStackedWidget,
               QString name,
               QString description,
               QString phone,
               QString email,
               QString content);

    ~NewContact();

    void startAnimation();
    void endAnimation();


private:

private slots:
    void on_confirmButton_clicked();
    void on_cancelButon_clicked();
};

#endif
