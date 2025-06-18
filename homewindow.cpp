#include "homewindow.h"
#include "ui_homewindow.h"
#include "historywindow.h"
#include "playmodewindow.h"
#include <QMessageBox>

HomeWindow::HomeWindow(QWidget *parent, UserManager* manager) :
    QDialog(parent),
    ui(new Ui::HomeWindow),
    userManager(manager)
{
    ui->setupUi(this);
    // ⛔️ Removed manual connects — already wired via UI if designed in Qt Designer
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::on_pushButton_history_clicked()
{
    QString currentUser = userManager->getCurrentUser();

    if (currentUser.isEmpty()) {
        QMessageBox::warning(this, "Error", "No user is logged in.");
        return;
    }

    // ✅ Open as modal dialog, will only show once
    HistoryWindow historyWin(userManager, currentUser, this);
    historyWin.exec();
}

void HomeWindow::on_pushButton_play_clicked()
{
    QString currentUser = userManager->getCurrentUser();

    if (currentUser.isEmpty()) {
        QMessageBox::warning(this, "Error", "No user is logged in.");
        return;
    }

    PlayModeWindow playMode(userManager, currentUser, this);
    playMode.exec();
}

void HomeWindow::on_pushButton_exit_clicked()
{
    QApplication::quit();
}
