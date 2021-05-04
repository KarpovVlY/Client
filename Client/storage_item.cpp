#include "storage_item.h"
#include "ui_storage_item.h"

StorageItem::StorageItem(QWidget *parent,
                         int id,
                         int uniqueId,
                         QString name,
                         QString description,
                         QString login,
                         QString password,
                         QString info,
                         QString content):
                         QWidget(parent),
                         ui(new Ui::StorageItem)
{
    ui->setupUi(this);

    ui->nameLabel->setText(name);
    ui->descriptionLabel->setText(description);

    this->id = id;
    this->uniqueId = uniqueId;

    this->name = name;
    this->description = description;
    this->login = login;
    this->password = password;
    this->info = info;
    this->content = content;

}

void StorageItem::setMaster(QObject *parent)
{
    MasterListItemMouseHandler *handler = new MasterListItemMouseHandler(parent);
    handler->setId(id);
    handler->setType(1);

    this->installEventFilter(handler);
}

StorageItem::~StorageItem()
{
    delete ui;
}
