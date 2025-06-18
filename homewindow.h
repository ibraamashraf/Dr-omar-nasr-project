#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QDialog>
#include "usermanager.h"

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = nullptr, UserManager* manager = nullptr);
    ~HomeWindow();

private slots:
    void on_pushButton_history_clicked(); // ✅ History button slot
    void on_pushButton_play_clicked();    // ✅ Play button slot
    void on_pushButton_exit_clicked();    // ✅ Exit button slot

private:
    Ui::HomeWindow *ui;
    UserManager* userManager;
};

#endif // HOMEWINDOW_H
