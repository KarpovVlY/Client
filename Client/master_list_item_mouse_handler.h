#ifndef MASTERLISTITEMMOUSEHANDLER_H
#define MASTERLISTITEMMOUSEHANDLER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QPropertyAnimation>



class MasterListItemMouseHandler : public QObject
{
    Q_OBJECT

public:

private:

    QWidget *parent;
    QLabel *nameLabel;
    QLabel *descriptionLabel;

    int id;
    short type;

public:
    MasterListItemMouseHandler(QObject *parent);
    ~MasterListItemMouseHandler();

    void setId(int id);
    void setType(short type);
    void setMaster(QObject *master);

private:


protected:
    bool eventFilter(QObject *obj, QEvent *event) override;


};

#endif
