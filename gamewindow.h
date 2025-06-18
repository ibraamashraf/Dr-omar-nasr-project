#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QVector>
#include "usermanager.h"

namespace Ui {
class GameWindow;
}

enum GameMode {
    PvP,
    PvAI
};

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    // ✅ Updated constructor to match the .cpp file
    explicit GameWindow(GameMode mode, int difficulty, UserManager* manager, const QString& username, QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void restartGame();
    void handleButtonClicked(); // ✅ Moved to slots (optional but better practice)

private:
    Ui::GameWindow *ui;
    QVector<QPushButton*> buttons;
    GameMode currentMode;
    int aiDifficulty;
    bool player1Turn;
    int movesCount;

    void setupBoard();
    void resetBoard();
    void playerVsPlayerLogic(int index);
    void endGame(int result);
    int checkWin();

    int getRandomMove();
    int getBestMove();
    int minimax(QVector<QString> &board, int depth, bool isMax, int alpha, int beta);
    int checkWinSim(QVector<QString> &board);

    void makeAIMove();

    UserManager* userManager;
    QString currentUsername;
};

#endif // GAMEWINDOW_H
