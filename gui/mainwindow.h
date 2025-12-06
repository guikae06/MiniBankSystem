#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui { class MainWindow; }
namespace MiniBank { class Bank; class FileStorage; }

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(MiniBank::Bank* bankPtr, MiniBank::FileStorage* storagePtr, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void deposit();
    void withdraw();
    void transfer();
    void addInterest();
    void refresh();

private:
    Ui::MainWindow* ui;
    MiniBank::Bank* bank;
    MiniBank::FileStorage* storage;

    void refreshAccountView();
};

#endif // MAINWINDOW_H
