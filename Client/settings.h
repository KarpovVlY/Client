#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

namespace Ui { class Settings; }

class Settings : public QWidget
{
    Q_OBJECT

public:


private:
    Ui::Settings *ui;

    QStackedWidget *mainStackedWidget;
    QWidget *masterWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;

public:
    Settings(QWidget *parent,
             QStackedWidget *mainStackedWidget);

    ~Settings();


    void startAnimation();
    void endAnimation();


private slots:
    void on_cancelButon_clicked();
    void on_exitButton_clicked();

private:


};

#endif
