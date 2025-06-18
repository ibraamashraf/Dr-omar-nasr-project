#include "playmodewindow.h"
#include "ui_playmodewindow.h"
#include "gamewindow.h"
#include "difficultywindow.h"

PlayModeWindow::PlayModeWindow(UserManager* manager, const QString& username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayModeWindow),
    userManager(manager),
    currentUsername(username)
{
    ui->setupUi(this);
}

PlayModeWindow::~PlayModeWindow()
{
    delete ui;
}

void PlayModeWindow::on_pushButton_player_clicked()
{
    this->hide();

    GameWindow *game = new GameWindow(PvP, 0, userManager, currentUsername);
    connect(game, &QDialog::finished, this, &QDialog::show);
    game->setAttribute(Qt::WA_DeleteOnClose);
    game->exec();
}

void PlayModeWindow::on_pushButton_ai_clicked()
{
    this->hide();

    DifficultyWindow *difficulty = new DifficultyWindow("PvAI", userManager, currentUsername);
    connect(difficulty, &QDialog::finished, this, &QDialog::show);
    difficulty->setAttribute(Qt::WA_DeleteOnClose);
    difficulty->exec();
}
