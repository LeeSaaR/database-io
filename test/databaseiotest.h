#ifndef DATABASEIOTEST_H
#define DATABASEIOTEST_H

#include <QString>
#include "databasemodelmain.h"

class DataBaseIOTest
{
public:
    DataBaseIOTest();

    void run();

    void createDatabase(const QString &db_filename, const QString &db_connection_name, DatabaseModel *model);
    void connectDatabase(const QString &db_filename, const QString &db_connection_name);
    void initDatabaseIO(const QString &db_connection_name);
    void insertSingleRecord(const QString &connection);
    void insertMultipleRecords();
    void selectSingle();
    void selectSingleByField();
    void selectAllRecords();
    void selectRecordsWithTargetField();
    void updateRecord();
    void updateRecordByTargetField();
    void deleteRecord();
    void deleteAll();
};

#endif // DATABASEIOTEST_H
