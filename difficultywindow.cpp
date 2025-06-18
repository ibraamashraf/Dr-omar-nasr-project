#include "difficultywindow.h"
#include "ui_difficultywindow.h"
#include "gamewindow.h"

DifficultyWindow::DifficultyWindow(const QString& mode, UserManager* manager, const QString& username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DifficultyWindow),
    selectedMode(mode),
    userManager(manager),
    currentUsername(username)
{
    ui->setupUi(this);
}

DifficultyWindow::~DifficultyWindow()
{
    delete ui;
}

// Helper to convert string to GameMode
GameMode getModeFromString(const QString& modeStr) {
    if (modeStr == "PvP") return PvP;
    return PvAI;
}

void DifficultyWindow::launchGameWithDifficulty(int difficulty)
{
    GameMode mode = getModeFromString(selectedMode);
    this->hide();

    GameWindow *game = new GameWindow(mode, difficulty, userManager, currentUsername);
    connect(game, &QDialog::finished, this, &QDialog::show);
    game->setAttribute(Qt::WA_DeleteOnClose);
    game->exec();
}

void DifficultyWindow::on_pushButton_easy_clicked()
{
    launchGameWithDifficulty(1);
}

void DifficultyWindow::on_pushButton_medium_clicked()
{
    launchGameWithDifficulty(2);
}

void DifficultyWindow::on_pushButton_hard_clicked()
{
    launchGameWithDifficulty(3);
}

void DifficultyWindow::on_pushButton_back_clicked()
{
    this->close();  // Properly closes and allows parent to reappear
}
