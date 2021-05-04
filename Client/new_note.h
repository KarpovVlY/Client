#ifndef NEW_NOTE_H
#define NEW_NOTE_H

#include <QWidget>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QList>


namespace Ui { class NewNote; }

class NewNote : public QWidget
{
    Q_OBJECT


public:


private:
    Ui::NewNote *ui;

    QStackedWidget *mainStackedWidget;

    QWidget *masterWidget;
    QWidget *noteWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;

    bool isNewNoteFromMaster;



public:
    NewNote(QWidget *parent,
            QStackedWidget *mainStackedWidget);

    NewNote(QWidget *parent,
            QStackedWidget *mainStackedWidget,
            QString name,
            QString description,
            QString content);

    ~NewNote();



    void startAnimation();
    void endAnimation();


private:

private slots:
    void on_cancelButon_clicked();
    void on_confirmButton_clicked();
};

#endif
