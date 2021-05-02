#ifndef MASTERHEADERMOUSEHANDLER_H
#define MASTERHEADERMOUSEHANDLER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

class MasterHeaderMouseHandler : public QObject
{
    Q_OBJECT

public:

private:
    QWidget *parent;
    QLabel *label;
    QWidget *line;




public:
    MasterHeaderMouseHandler(QObject *parent);
    ~MasterHeaderMouseHandler();


    void refresh();

private:



protected:
    bool eventFilter(QObject *obj, QEvent *event) override;



};

#endif
