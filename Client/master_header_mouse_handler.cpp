#include "master_header_mouse_handler.h"

#include <QDebug>
#include "master.h"
#include "stylesheet.h"

//QString parentStylesheetOn = "QWidget{ border-radius:10px; background-color: rgb(30, 33, 36);} ";
//QString parentStylesheetOff = "QWidget{ border-radius:10px; background-color: rgb(40, 46, 51);} ";

QString currentTab;

Master *masterHeader;




MasterHeaderMouseHandler::MasterHeaderMouseHandler(QObject *parent) :
                                                   QObject(parent)
{
    masterHeader = qobject_cast<Master*>(parent);
}

void MasterHeaderMouseHandler::refresh()
{
    parent->setStyleSheet(Stylesheet::masterHeaderParentStylesheetOff);
    label->setStyleSheet(Stylesheet::masterHeaderLabelStylesheetOff);
    line->setStyleSheet(Stylesheet::masterHeaderLineStylesheetOff);
}



bool MasterHeaderMouseHandler::eventFilter(QObject *obj, QEvent *event)
{
    parent = qobject_cast<QWidget*>(obj);
    label = qobject_cast<QLabel*>(parent->children().at(0));
    line = qobject_cast<QWidget*>(parent->children().at(1));

    if (event->type() == QEvent::MouseButtonPress)
    {
        if(label->text() == "Контакты")
        {
            currentTab = "Контакты";
            masterHeader->tabChanged(0);

        }
        else if(label->text() == "Хранилище")
        {
            currentTab = "Хранилище";
            masterHeader->tabChanged(1);
        }
        else if(label->text() == "Заметки")
        {
            currentTab = "Заметки";
            masterHeader->tabChanged(2);
        }


        parent->setStyleSheet(Stylesheet::masterHeaderParentStylesheetOn);
        line->setStyleSheet(Stylesheet::masterHeaderLineStylesheetOn);
        return true;
    }
    else if(event->type() == QEvent::Enter)
    {
       parent->setStyleSheet(Stylesheet::masterHeaderParentStylesheetOn);
       label->setStyleSheet(Stylesheet::masterHeaderLabelStylesheetOn);
       return true;
    }
    else if(event->type() == QEvent::Leave)
    {
        if(label->text() != currentTab)
        {
            parent->setStyleSheet(Stylesheet::masterHeaderParentStylesheetOff);
            label->setStyleSheet(Stylesheet::masterHeaderLabelStylesheetOff);
        }

        return true;
    }
    else
        return QObject::eventFilter(obj, event);

}


MasterHeaderMouseHandler::~MasterHeaderMouseHandler()
{

}

