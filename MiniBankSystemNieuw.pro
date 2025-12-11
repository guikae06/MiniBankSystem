QT       += core gui widgets charts
CONFIG  += c++17
TEMPLATE = app
TARGET = MiniBankSystem

INCLUDEPATH += headers

HEADERS += \
    gui/AssuranceDialog.h \
    gui/LoansDialog.h \
    gui/StockMarketDialog.h \
    headers/Account.h \
    headers/CheckingAccount.h \
    headers/SavingsAccount.h \
    headers/Bank.h \
    headers/FileStorage.h \
    headers/AuthManager.h \
    headers/StockMarket.h \
    gui/mainwindow.h \
    gui/LogInDialog.h \
    gui/TransferDialog.h \


SOURCES += \
    gui/AssuranceDialog.cpp \
    gui/LoansDialog.cpp \
    gui/StockMarketDialog.cpp \
    src/Account.cpp \
    src/CheckingAccount.cpp \
    src/SavingsAccount.cpp \
    src/Bank.cpp \
    src/FileStorage.cpp \
    src/AuthManager.cpp \
    src/StockMarket.cpp \
    gui/main.cpp \
    gui/mainwindow.cpp \
    gui/LogInDialog.cpp \
    gui/TransferDialog.cpp

FORMS += \
    gui/AssuranceDialog.ui \
    gui/LoansDialog.ui \
    gui/StockMarketDialog.ui \
    gui/mainwindow.ui \
    gui/LogInDialog.ui \
    gui/TransferDialog.ui

# Make sure to link charts if using Qt Charts
QT += charts
