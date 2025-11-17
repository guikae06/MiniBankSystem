QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniBankSystem
TEMPLATE = app

INCLUDEPATH += headers

SOURCES += \
    src/Account.cpp \
    src/CheckingAccount.cpp \
    src/SavingsAccount.cpp \
    src/Bank.cpp \
    gui/main.cpp \
    gui/mainwindow.cpp

HEADERS += \
    headers/Account.h \
    headers/CheckingAccount.h \
    headers/SavingsAccount.h \
    headers/Bank.h \
    gui/mainwindow.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

