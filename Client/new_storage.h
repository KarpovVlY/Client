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

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;

public:
    NewStorage(QWidget *parent,
               QStackedWidget *mainStackedWidget);
    ~NewStorage();

    void startAnimation();
    void endAnimation();


private:



private slots:
    void on_cancelButon_clicked();
    void on_confirmButton_clicked();


};

#endif
