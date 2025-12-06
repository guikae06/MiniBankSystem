QT       += core gui widgets

CONFIG += c++17

TARGET = MiniBankSystem
TEMPLATE = app

INCLUDEPATH += headers

SOURCES += \
    src/Account.cpp \
    src/CheckingAccount.cpp \
    src/SavingsAccount.cpp \
    src/Bank.cpp \
    src/FileStorage.cpp \
    src/Authmanager.cpp \
    src/StockMarket.cpp \
    gui/main.cpp \
    gui/mainwindow.cpp \
    gui/LogInDialog.cpp \
    gui/TransferDialog.cpp

HEADERS += \
    headers/Account.h \
    headers/CheckingAccount.h \
    headers/SavingsAccount.h \
    headers/Bank.h \
    headers/FileStorage.h \
    headers/Authmanager.h \
    headers/StockMarket.h \
    gui/mainwindow.h \
    gui/LogInDialog.h \
    gui/TransferDialog.h

FORMS += \
    gui/LogInDialog.ui \
    gui/TransferDialog.ui \
    gui/mainwindow.ui

# Default rules for deployment.
unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
