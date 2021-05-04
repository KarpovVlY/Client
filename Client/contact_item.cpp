#include "contact_item.h"
#include "ui_contact_item.h"

ContactItem::ContactItem(QWidget *parent,
                         int id,
                         int uniqueId,
                         QString name,
                         QString description,
                         QString phone,
                         QString email,
                         QString content):
                         QWidget(parent),
                         ui(new Ui::ContactItem)
{
    ui->setupUi(this);


    ui->nameLabel->setText(name);
    ui->descriptionLabel->setText(description);


    this->id = id;
    this->uniqueId = uniqueId;

    this->name = name;
    this->description = description;
    this->phone = phone;
    this->email = email;
    this->content = content;
}

void ContactItem::setMaster(QObject *parent)
{
    MasterListItemMouseHandler *handler = new MasterListItemMouseHandler(parent);
    handler->setId(id);
    handler->setType(0);

    this->installEventFilter(handler);
}

ContactItem::~ContactItem()
{
    delete ui;
}
