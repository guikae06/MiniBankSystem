QT += core gui widgets

CONFIG += c++17

TARGET = MiniBankSystem
TEMPLATE = app

INCLUDEPATH += headers libs

SOURCES += \
    src/FileDB.cpp \
    src/AuthManager.cpp \
    src/Bank.cpp \
    src/Account.cpp \
    src/CheckingAccount.cpp \
    src/SavingsAccount.cpp \
    src/StockMarket.cpp \
    gui/main.cpp \
    gui/mainwindow.cpp \
    gui/LogInDialog.cpp \
    gui/TransferDialog.cpp

HEADERS += \
    headers/FileDB.h \
    headers/AuthManager.h \
    headers/Bank.h \
    headers/Account.h \
    headers/CheckingAccount.h \
    headers/SavingsAccount.h \
    headers/StockMarket.h \
    gui/mainwindow.h \
    gui/LogInDialog.h \
    gui/TransferDialog.h

FORMS += \
    gui/mainwindow.ui \
    gui/LogInDialog.ui \
    gui/TransferDialog.ui

