#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include "usermanager.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    // ✅ Modified constructor to receive UserManager pointer
    explicit RegisterWindow(QWidget *parent = nullptr, UserManager* manager = nullptr);
    ~RegisterWindow();

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_register_clicked();

private:
    Ui::RegisterWindow *ui;

    // ✅ Add this line to store the passed UserManager pointer
    UserManager* userManager;
};

#endif // REGISTERWINDOW_H
