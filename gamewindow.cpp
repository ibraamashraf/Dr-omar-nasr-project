#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <QDateTime>

GameWindow::GameWindow(GameMode mode, int difficulty, UserManager* manager, const QString& username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow),
    currentMode(mode),
    aiDifficulty(difficulty),
    userManager(manager),
    currentUsername(username),
    player1Turn(true),
    movesCount(0)
{
    ui->setupUi(this);

    buttons = {
        ui->button_00, ui->button_01, ui->button_02,
        ui->button_10, ui->button_11, ui->button_12,
        ui->button_20, ui->button_21, ui->button_22
    };

    setupBoard();

    for (auto btn : buttons) {
        connect(btn, &QPushButton::clicked, this, &GameWindow::handleButtonClicked);
    }

    connect(ui->button_restart, &QPushButton::clicked, this, &GameWindow::restartGame);
    connect(ui->button_back, &QPushButton::clicked, this, &GameWindow::close);

    srand(time(nullptr));
    ui->label_turn->setText("Player 1's turn (X)");
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::setupBoard()
{
    for (auto btn : buttons) {
        btn->setText("");
        btn->setEnabled(true);
    }
    player1Turn = true;
    movesCount = 0;
    ui->label_turn->setText("Player 1's turn (X)");
}

void GameWindow::handleButtonClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    int index = buttons.indexOf(clickedButton);
    if (index == -1) return;

    if (currentMode == PvP) {
        playerVsPlayerLogic(index);
    } else {
        if (player1Turn && buttons[index]->text() == "") {
            buttons[index]->setText("X");
            buttons[index]->setEnabled(false);
            movesCount++;

            if (checkWin() == 1) {
                endGame(1);
                return;
            } else if (movesCount == 9) {
                endGame(3);
                return;
            }

            player1Turn = false;
            ui->label_turn->setText("AI's turn (O)");
            makeAIMove();
        }
    }
}

void GameWindow::playerVsPlayerLogic(int index)
{
    if (buttons[index]->text() != "") return;

    buttons[index]->setText(player1Turn ? "X" : "O");
    buttons[index]->setEnabled(false);
    movesCount++;

    int result = checkWin();
    if (result == 1) {
        endGame(1);
        return;
    } else if (result == 2) {
        endGame(2);
        return;
    } else if (movesCount == 9) {
        endGame(3);
        return;
    }

    player1Turn = !player1Turn;
    ui->label_turn->setText(player1Turn ? "Player 1's turn (X)" : "Player 2's turn (O)");
}

void GameWindow::makeAIMove()
{
    int moveIndex = -1;

    if (aiDifficulty == 1) {
        moveIndex = getRandomMove();
    } else if (aiDifficulty == 2) {
        if (rand() % 2 == 0)
            moveIndex = getRandomMove();
        else
            moveIndex = getBestMove();
    } else if (aiDifficulty == 3) {
        moveIndex = getBestMove();
    }

    if (moveIndex != -1) {
        buttons[moveIndex]->setText("O");
        buttons[moveIndex]->setEnabled(false);
        movesCount++;
    }

    int result = checkWin();
    if (result == 2) {
        endGame(2);
        return;
    } else if (movesCount == 9) {
        endGame(3);
        return;
    }

    player1Turn = true;
    ui->label_turn->setText("Player 1's turn (X)");
}

int GameWindow::getRandomMove()
{
    QVector<int> emptyCells;
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i]->text() == "") {
            emptyCells.append(i);
        }
    }
    if (emptyCells.isEmpty()) return -1;

    return emptyCells[rand() % emptyCells.size()];
}

int GameWindow::getBestMove()
{
    QVector<QString> board(9);
    for (int i = 0; i < 9; i++)
        board[i] = buttons[i]->text();

    int bestScore = std::numeric_limits<int>::min();
    int move = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == "") {
            board[i] = "O";
            int score = minimax(board, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            board[i] = "";
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

int GameWindow::minimax(QVector<QString> &board, int depth, bool isMax, int alpha, int beta)
{
    int result = checkWinSim(board);
    if (result == 1) return -10 + depth;
    if (result == 2) return 10 - depth;
    if (!board.contains("")) return 0;

    if (isMax) {
        int best = std::numeric_limits<int>::min();
        for (int i = 0; i < 9; i++) {
            if (board[i] == "") {
                board[i] = "O";
                int score = minimax(board, depth + 1, false, alpha, beta);
                board[i] = "";
                best = std::max(best, score);
                alpha = std::max(alpha, best);
                if (beta <= alpha)
                    break;
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::max();
        for (int i = 0; i < 9; i++) {
            if (board[i] == "") {
                board[i] = "X";
                int score = minimax(board, depth + 1, true, alpha, beta);
                board[i] = "";
                best = std::min(best, score);
                beta = std::min(beta, best);
                if (beta <= alpha)
                    break;
            }
        }
        return best;
    }
}

int GameWindow::checkWinSim(QVector<QString> &b)
{
    for (int i = 0; i <= 6; i += 3)
        if (!b[i].isEmpty() && b[i] == b[i+1] && b[i] == b[i+2])
            return (b[i] == "X") ? 1 : 2;

    for (int i = 0; i < 3; i++)
        if (!b[i].isEmpty() && b[i] == b[i+3] && b[i] == b[i+6])
            return (b[i] == "X") ? 1 : 2;

    if (!b[0].isEmpty() && b[0] == b[4] && b[0] == b[8])
        return (b[0] == "X") ? 1 : 2;

    if (!b[2].isEmpty() && b[2] == b[4] && b[2] == b[6])
        return (b[2] == "X") ? 1 : 2;

    return 0;
}

int GameWindow::checkWin()
{
    QString b[9];
    for (int i = 0; i < 9; i++) {
        b[i] = buttons[i]->text();
    }

    for (int i = 0; i <= 6; i += 3)
        if (!b[i].isEmpty() && b[i] == b[i+1] && b[i] == b[i+2])
            return (b[i] == "X") ? 1 : 2;

    for (int i = 0; i < 3; i++)
        if (!b[i].isEmpty() && b[i] == b[i+3] && b[i] == b[i+6])
            return (b[i] == "X") ? 1 : 2;

    if (!b[0].isEmpty() && b[0] == b[4] && b[0] == b[8])
        return (b[0] == "X") ? 1 : 2;

    if (!b[2].isEmpty() && b[2] == b[4] && b[2] == b[6])
        return (b[2] == "X") ? 1 : 2;

    return 0;
}

void GameWindow::endGame(int result)
{
    QString message;
    QString resultStr;

    if (result == 1) {
        message = "Player 1 (X) wins!";
        resultStr = "Player 1 (X) wins";
    } else if (result == 2) {
        message = (currentMode == PvP) ? "Player 2 (O) wins!" : "AI (O) wins!";
        resultStr = (currentMode == PvP) ? "Player 2 (O) wins" : "AI (O) wins";
    } else {
        message = "It's a draw!";
        resultStr = "Draw";
    }

    QMessageBox::information(this, "Game Over", message);

    // Save full game details
    if (userManager && !currentUsername.isEmpty()) {
        QJsonObject gameData;
        gameData["mode"] = (currentMode == PvP) ? "PvP" : "PvAI";
        gameData["result"] = resultStr;
        gameData["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        gameData["difficulty"] = aiDifficulty;

        userManager->saveGame(gameData);
    }

    // Save correct summary result
    if (userManager && !currentUsername.isEmpty()) {
        QString simpleResult;

        if (currentMode == PvP) {
            // In PvP, assume current user is Player 1 (X)
            simpleResult = (result == 1) ? "win" :
                               (result == 2) ? "loss" : "draw";
        } else {
            // In PvAI, user is always Player 1 (X), AI is O
            simpleResult = (result == 1) ? "win" :
                               (result == 2) ? "loss" : "draw";
        }

        userManager->recordGameResult(simpleResult);
    }

    if (result != 3)
        resetBoard();
    else
        this->close();
}


void GameWindow::resetBoard()
{
    for (auto btn : buttons) {
        btn->setText("");
        btn->setEnabled(true);
    }
    player1Turn = true;
    movesCount = 0;
    ui->label_turn->setText("Player 1's turn (X)");
}

void GameWindow::restartGame()
{
    resetBoard();
}
