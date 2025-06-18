#ifndef SECURITY_H
#define SECURITY_H

#include <QString>

class Security {
public:
    static QString hashPassword(const QString &password);
};

#endif // SECURITY_H
