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


public:
    Note(QWidget *parent,
         QStackedWidget *mainStackedWidget,
         NoteItem *item);

    ~Note();

    void startAnimation();
    void endAnimation();


private:


private slots:
    void on_cancelButon_clicked();


};

#endif
