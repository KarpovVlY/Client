QT       += core gui sql network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    contact.cpp \
    contact_item.cpp \
    main.cpp \
    mainwindow.cpp \
    master.cpp \
    master_header_mouse_handler.cpp \
    master_list_item_mouse_handler.cpp \
    new_contact.cpp \
    new_note.cpp \
    new_storage.cpp \
    note.cpp \
    note_item.cpp \
    settings.cpp \
    signup.cpp \
    storage.cpp \
    storage_item.cpp \
    stylesheet.cpp

HEADERS += \
    client.h \
    contact.h \
    contact_item.h \
    mainwindow.h \
    master.h \
    master_header_mouse_handler.h \
    master_list_item_mouse_handler.h \
    new_contact.h \
    new_note.h \
    new_storage.h \
    note.h \
    note_item.h \
    settings.h \
    signup.h \
    storage.h \
    storage_item.h \
    stylesheet.h

FORMS += \
    contact.ui \
    contact_item.ui \
    mainwindow.ui \
    master.ui \
    new_contact.ui \
    new_note.ui \
    new_storage.ui \
    note.ui \
    note_item.ui \
    settings.ui \
    signup.ui \
    storage.ui \
    storage_item.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
