 #include "note_item.h"
#include "ui_note_item.h"

NoteItem::NoteItem(QWidget *parent,
                   int id,
                   QString name,
                   QString description,
                   QString content):
                   QWidget(parent),
                   ui(new Ui::NoteItem)
{
    ui->setupUi(this);

    ui->nameLabel->setText(name);
    ui->descriptionLabel->setText(description);


    this->id = id;
    this->name = name;
    this->description = description;
    this->content = content;


}

void NoteItem::setMaster(QObject *parent)
{
    MasterListItemMouseHandler *handler = new MasterListItemMouseHandler(parent);
    handler->setId(id);
    handler->setType(2);

    this->installEventFilter(handler);
}

NoteItem::~NoteItem()
{
    delete ui;
}
