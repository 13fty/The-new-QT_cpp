QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

TARGET = DormManager
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/dormitory_manager.cpp \
    src/dormitory_manager_dialog.cpp \
    src/dormitory_form_dialog.cpp \
    src/repair_request_dialog.cpp \
    src/repair_list_dialog.cpp

HEADERS += \
    src/mainwindow.h \
    src/dormitory_manager.h \
    src/dormitory_manager_dialog.h \
    src/dormitory_form_dialog.h \
    src/repair_request_dialog.h \
    src/repair_list_dialog.h

FORMS += \
    src/mainwindow.ui

RESOURCES += \
    resources/icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
