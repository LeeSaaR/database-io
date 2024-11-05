#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include <QString>
#include <QList>

class DatabaseModel
{
protected:
    DatabaseModel();

public:
    ~DatabaseModel();
    virtual const QList<QString> createStatements() const{ return QList<QString> {};};
};

#endif // DATABASEMODEL_H
