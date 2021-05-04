#ifndef NEW_STORAGE_H
#define NEW_STORAGE_H

#include <QWidget>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>


namespace Ui { class NewStorage; }

class NewStorage : public QWidget
{
    Q_OBJECT


private:
    Ui::NewStorage *ui;

    QStackedWidget *mainStackedWidget;

    QWidget *masterWidget;
    QWidget storageWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;

    bool isNewStorageFromMaster;

public:
    NewStorage(QWidget *parent,
               QStackedWidget *mainStackedWidget);

    NewStorage(QWidget *parent,
               QStackedWidget *mainStackedWidget,
               QString name,
               QString description,
               QString login,
               QString password,
               QString info,
               QString content);

    ~NewStorage();

    void startAnimation();
    void endAnimation();


private:



private slots:
    void on_cancelButon_clicked();
    void on_confirmButton_clicked();


};

#endif
