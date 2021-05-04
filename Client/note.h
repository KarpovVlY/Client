#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>

#include "note_item.h"



namespace Ui { class Note; }

class Note : public QWidget
{
    Q_OBJECT

public:


private:
    Ui::Note *ui;

    QStackedWidget *mainStackedWidget;
    QWidget *masterWidget;

    QGraphicsOpacityEffect *fadeEffect;
    QPropertyAnimation *animation;


    NoteItem *currentItem;


public:
    Note(QWidget *parent,
         QStackedWidget *mainStackedWidget,
         NoteItem *item);

    ~Note();

    void noteChanged(QString name,
                     QString description,
                     QString content);

    void startAnimation();
    void endAnimation();

private:

    void cancel();
    void deleteItem();


private slots:
    void on_cancelButon_clicked();

    void on_editButton_clicked();
    void on_deleteButon_clicked();
};

#endif
