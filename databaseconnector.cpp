#include "databaseconnector.h"

#include <QDebug>
#include "databasemodel.h"

DatabaseConnector *DatabaseConnector::m_instance = nullptr;

DatabaseConnector::DatabaseConnector()
{

}

DatabaseConnector *DatabaseConnector::GetInstance()
{
    if (m_instance == nullptr)
        m_instance = new DatabaseConnector();
    return m_instance;
}

DatabaseConnector::~DatabaseConnector()
{

}

bool DatabaseConnector::createDatabase(const QString &filename, const QString &connection, DatabaseModel *model)
{
    qDebug() << "Creating..." << filename;
    qDebug() << "database filename  :" << filename;
    qDebug() << "database connection:" << connection;

    // create database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName(filename);

    if (!db.open()) {
        qDebug() << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);

    // create tables
    for (const QString &statement : model->createStatements())
        query.exec(statement);

    query.finish();

    return true;
}

bool DatabaseConnector::connectDatabase(const QString &filename, const QString &connection)
{
    qDebug() << "Connecting..." << filename;
    qDebug() << "database filename  :" << filename;
    qDebug() << "database connection:" << connection;
    if (!QFile::exists(filename)) {
        qDebug() << "ERROR: no such file:" << filename;
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName(filename);
    if (!db.open()) {
        qDebug() << db.lastError().text();
        return false;
    }
    return true;
}

