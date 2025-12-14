QT       += core gui widgets charts
CONFIG  += c++17
TEMPLATE = app
TARGET = MiniBankSystem

INCLUDEPATH += headers

HEADERS += \
    gui/DepositWithdrawDialog.h \
    gui/InssuranceDialog.h \
    gui/LoansDialog.h \
    gui/MainMenuDialog.h \
    gui/StockMarketDialog.h \
    headers/Account.h \
    headers/CheckingAccount.h \
    headers/SavingsAccount.h \
    headers/Bank.h \
    headers/FileStorage.h \
    headers/AuthManager.h \
    headers/StockMarket.h \
    gui/LogInDialog.h \
    gui/TransferDialog.h \


SOURCES += \
    gui/DepositWithdrawDialog.cpp \
    gui/InssuranceDialog.cpp \
    gui/LoansDialog.cpp \
    gui/MainMenuDialog.cpp \
    gui/StockMarketDialog.cpp \
    src/Account.cpp \
    src/CheckingAccount.cpp \
    src/SavingsAccount.cpp \
    src/Bank.cpp \
    src/FileStorage.cpp \
    src/AuthManager.cpp \
    src/StockMarket.cpp \
    gui/main.cpp \
    gui/LogInDialog.cpp \
    gui/TransferDialog.cpp

FORMS += \
    gui/DepositWithdrawDialog.ui \
    gui/InssuranceDialog.ui \
    gui/LoansDialog.ui \
    gui/MainMenuDialog.ui \
    gui/StockMarketDialog.ui \
    gui/LogInDialog.ui \
    gui/TransferDialog.ui

# Make sure to link charts if using Qt Charts
QT += charts
