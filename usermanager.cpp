#include "usermanager.h"
#include "security.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

UserManager::UserManager(const QString &filename) : filePath(filename) {
    loadUsers();
}

void UserManager::loadUsers() {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        usersArray = doc.object().value("users").toArray();
    }
}

void UserManager::saveUsers() {
    QJsonObject root;
    root["users"] = usersArray;

    QJsonDocument doc(root);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

int UserManager::findUserIndex(const QString &username) {
    for (int i = 0; i < usersArray.size(); ++i) {
        if (usersArray[i].toObject()["username"].toString() == username) {
            return i;
        }
    }
    return -1;
}

bool UserManager::registerUser(const QString &username, const QString &password) {
    if (findUserIndex(username) != -1) return false; // already exists

    QJsonObject newUser;
    newUser["username"] = username;
    newUser["password"] = Security::hashPassword(password);
    newUser["games"] = QJsonArray();   // For saving detailed game data
    newUser["history"] = QJsonArray(); // For saving win/loss/draw history

    usersArray.append(newUser);
    saveUsers();
    return true;
}

// ✅ This is the function your code uses
bool UserManager::loginUser(const QString &username, const QString &password) {
    return authenticateUser(username, password);
}

bool UserManager::authenticateUser(const QString &username, const QString &password) {
    int index = findUserIndex(username);
    if (index == -1) return false;

    QJsonObject user = usersArray[index].toObject();
    QString hashed = Security::hashPassword(password);

    if (user["password"].toString() == hashed) {
        currentUser = username;
        return true;
    }

    return false;
}

QString UserManager::getCurrentUser() const {
    return currentUser;
}

void UserManager::logout() {
    currentUser = "";
}

bool UserManager::saveGame(const QJsonObject &gameData) {
    int index = findUserIndex(currentUser);
    if (index == -1) return false;

    QJsonObject user = usersArray[index].toObject();
    QJsonArray games = user["games"].toArray();
    games.append(gameData);
    user["games"] = games;
    usersArray[index] = user;

    saveUsers();
    return true;
}

bool UserManager::recordGameResult(const QString &result) {
    if (currentUser.isEmpty()) return false;

    int index = findUserIndex(currentUser);
    if (index == -1) return false;

    QJsonObject user = usersArray[index].toObject();
    QJsonArray history = user["history"].toArray(); // 👈 history key
    history.append(result);
    user["history"] = history;

    usersArray[index] = user;
    saveUsers();
    return true;
}

QList<QString> UserManager::getGameHistory(const QString &username) {
    QList<QString> results;

    int index = findUserIndex(username);
    if (index == -1) return results;

    QJsonObject user = usersArray[index].toObject();
    QJsonArray history = user["history"].toArray();

    for (const QJsonValue &val : history) {
        results.append(val.toString());
    }

    return results;
}
