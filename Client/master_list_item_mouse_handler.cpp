#include "master_list_item_mouse_handler.h"


#include <QDebug>
#include "master.h"


QString labelStylesheetOn = "background-color: rgb(30, 33, 36);  max-width:180px; max-height:20px; min-width:180px; min-height:20px;";
QString labelStylesheetOff = "background-color: rgb(35, 38, 41);  max-width:180px; max-height:20px; min-width:180px; min-height:20px;";

QString parentStyleSheetOn = "QWidget{ border-style: solid; background-color:rgb(35, 38, 41); border-radius:12px; max-width:370px; max-height:50px; min-width:370px; min-height:50px; }";

Master *masterListItem;



MasterListItemMouseHandler::MasterListItemMouseHandler(QObject *parent) :
                                                       QObject(parent)
{
    masterListItem = qobject_cast<Master*>(parent);
}




bool MasterListItemMouseHandler::eventFilter(QObject *obj, QEvent *event)
{
    parent = qobject_cast<QWidget*>(obj);
    parent = qobject_cast<QWidget*>(parent->children().at(0));
    descriptionLabel = qobject_cast<QLabel*>(parent->children().at(0));
    nameLabel = qobject_cast<QLabel*>(parent->children().at(1));

    if (event->type() == QEvent::MouseButtonPress)
    {
        masterListItem->itemSelected(id, type);

        return true;
    }
    else if(event->type() == QEvent::Enter)
    {
        //parent->setStyleSheet(parentStyleSheetOn);
        nameLabel->setStyleSheet(labelStylesheetOn);
        descriptionLabel->setStyleSheet(labelStylesheetOn);

        return true;
    }
    else if(event->type() == QEvent::Leave)
    {
        nameLabel->setStyleSheet(labelStylesheetOff);
        descriptionLabel->setStyleSheet(labelStylesheetOff);

        return true;
    }
    else
        return QObject::eventFilter(obj, event);

}


void MasterListItemMouseHandler::setId(int id){ this->id = id; }
void MasterListItemMouseHandler::setType(short type){ this->type = type; }

void MasterListItemMouseHandler::setMaster(QObject *master) { masterListItem = qobject_cast<Master*>(master); }


MasterListItemMouseHandler::~MasterListItemMouseHandler()
{
    delete masterListItem;
}
