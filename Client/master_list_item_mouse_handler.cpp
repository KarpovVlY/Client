#include "master_list_item_mouse_handler.h"


#include <QDebug>
#include "master.h"
#include "stylesheet.h"


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
        nameLabel->setStyleSheet(Stylesheet::masterItemsLabelStylesheetOn);
        descriptionLabel->setStyleSheet(Stylesheet::masterItemsLabelStylesheetOn);

        return true;
    }
    else if(event->type() == QEvent::Leave)
    {
        nameLabel->setStyleSheet(Stylesheet::masterItemsLabelStylesheetOff);
        descriptionLabel->setStyleSheet(Stylesheet::masterItemsLabelStylesheetOff);

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
