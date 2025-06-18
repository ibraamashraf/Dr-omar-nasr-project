#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

class UserManager {
public:
    UserManager(const QString &filename);

    bool registerUser(const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);

    // ✅ Add this missing function
    bool authenticateUser(const QString &username, const QString &password);

    QString getCurrentUser() const;
    void logout();

    // ✅ Game-related functions
    bool saveGame(const QJsonObject &gameData);

    // ✅ Save result (win/loss/draw)
    bool recordGameResult(const QString &result); // result: "win", "loss", "draw"

    // ✅ Get game history as list of strings (e.g. ["win", "loss", "draw"])
    QList<QString> getGameHistory(const QString &username);

private:
    QString currentUser;
    QString filePath;
    QJsonArray usersArray;

    void loadUsers();
    void saveUsers();
    int findUserIndex(const QString &username);
};

#endif // USERMANAGER_H
