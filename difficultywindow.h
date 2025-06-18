#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QDialog>
#include "usermanager.h"

namespace Ui {
class DifficultyWindow;
}

class DifficultyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DifficultyWindow(const QString& mode, UserManager* manager, const QString& username, QWidget *parent = nullptr);
    ~DifficultyWindow();

private slots:
    void on_pushButton_easy_clicked();
    void on_pushButton_medium_clicked();
    void on_pushButton_hard_clicked();
    void on_pushButton_back_clicked();

private:
    void launchGameWithDifficulty(int difficulty);  // ✅ Fix: declare this private helper

    Ui::DifficultyWindow *ui;
    QString selectedMode;
    UserManager* userManager;
    QString currentUsername;
};

#endif // DIFFICULTYWINDOW_H
