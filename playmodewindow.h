#ifndef PLAYMODEWINDOW_H
#define PLAYMODEWINDOW_H

#include <QDialog>
#include "usermanager.h"

namespace Ui {
class PlayModeWindow;
}

class PlayModeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlayModeWindow(UserManager* manager, const QString& username, QWidget *parent = nullptr);
    ~PlayModeWindow();

private slots:
    void on_pushButton_player_clicked();
    void on_pushButton_ai_clicked();

private:
    Ui::PlayModeWindow *ui;
    UserManager* userManager;
    QString currentUsername;
};

#endif // PLAYMODEWINDOW_H
