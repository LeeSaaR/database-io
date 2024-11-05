#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QtSql>
#include "databasemodel.h"

class DatabaseConnector
{

private:
    DatabaseConnector();

protected:
    static DatabaseConnector *m_instance;

public:
    DatabaseConnector(DatabaseConnector &other) = delete;
    void operator=(const DatabaseConnector &other) = delete;
    static DatabaseConnector *GetInstance();
    ~DatabaseConnector();

public:
    bool createDatabase(const QString & filename, const QString &connection, DatabaseModel *model);
    bool connectDatabase(const QString & filename, const QString &connection);
};

#endif // DATABASECONNECTOR_H
