#include <QApplication>
#include "mainwindow.h"
#include "LogInDialog.h"
#include "headers/FileStorage.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString err;
    FileStorage storage("data.json");
    if (!storage.ensureLoaded(err)) {
        QMessageBox::warning(nullptr, "Data load error", err);
        // attempt save initial
        storage.load(err);
    }

    LogInDialog dlg(&storage);
    if (dlg.exec() != QDialog::Accepted) return 0;
    int userId = dlg.authenticatedUserId();

    MainWindow w(userId, &storage); // we'll assume your MainWindow header can accept this
    w.show();
    return a.exec();
}
