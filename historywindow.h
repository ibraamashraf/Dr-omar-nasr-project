#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QDialog>
#include <QListWidget>
#include "usermanager.h"

namespace Ui {
class HistoryWindow;
}

class HistoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryWindow(UserManager* manager, const QString& username, QWidget *parent = nullptr);
    ~HistoryWindow();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::HistoryWindow *ui;
    UserManager* userManager;
    QString currentUsername;

    void loadHistory();
};

#endif // HISTORYWINDOW_H
