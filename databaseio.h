#ifndef DATABASEIO_H
#define DATABASEIO_H

#include "datarecordrawlist.h"
#include "datarecord.h"
#include "idgenerator.h"

class DatabaseIO
{
private:
    QString m_connection;

private:
    DatabaseIO();
protected:
    static DatabaseIO *m_instance;
public:
    DatabaseIO(DatabaseIO &other) = delete;
    void operator=(const DatabaseIO &) = delete;
    static DatabaseIO *GetInstance();
    ~DatabaseIO();

private:
    QString makeID(DataRecord *record);
    void getIDs(const QString &table, const QString &primary_key_name, QList<QString> &existing_ids);
    void generateID(IDGenerator* id_gen, const QList<QString> &existing_ids, const QString &id_format, QString &id);
    const QString generateBindValue(const int & i);

public:
    void insert(DataRecord *record);
    void insert(QList<DataRecord*> records);
    void update(DataRecord *record, DataField *targetField = nullptr);
    void update(QList<DataRecord*> records);
    void update(const QString &table, DataField *updateField, DataField *targetField);
    void update(const QString &table, DataField *updateField, const QString &WHERE);
    void select(DataRecord* record, DataField *targetField = nullptr);
    void select(const QString &table, DataRecordRawList *outputList, DataField *targetField = nullptr);
    void del(DataRecord* record);
    void del(QList<DataRecord* > records);
    void del(const QString &table, DataField *targetField);

public: // GETTER & SETTER
    QString connection() const;
    void setConnection(const QString &newConnection);
};

#endif // DATABASEIO_H
