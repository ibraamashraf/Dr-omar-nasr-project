#include "historywindow.h"
#include "ui_historywindow.h"

HistoryWindow::HistoryWindow(UserManager* manager, const QString& username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryWindow),
    userManager(manager),
    currentUsername(username)
{
    ui->setupUi(this);
    loadHistory();
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}

void HistoryWindow::loadHistory()
{
    QList<QString> history = userManager->getGameHistory(currentUsername);

    if (history.isEmpty()) {
        ui->listWidget_history->addItem("No games played yet.");
    } else {
        for (const QString& entry : history) {
            ui->listWidget_history->addItem(entry);
        }
    }
}

void HistoryWindow::on_pushButton_close_clicked()
{
    close();
}
