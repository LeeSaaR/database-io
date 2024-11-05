#include "databaseio.h"

#include <QtSql>
#include <QMap>

#include "idgenerator.h"

DatabaseIO * DatabaseIO::m_instance = nullptr;

DatabaseIO::DatabaseIO()
{

}

DatabaseIO *DatabaseIO::GetInstance()
{
    if (m_instance == nullptr)
        m_instance = new DatabaseIO();

    return m_instance;
}

DatabaseIO::~DatabaseIO()
{

}

QString DatabaseIO::makeID(DataRecord *record)
{
    QList<QString> existing_ids;
    getIDs(record->table(), record->ID()->name(), existing_ids);

    IDGenerator *id_gen = IDGenerator::GetInstance();
    QString id;

    generateID(id_gen, existing_ids, record->idFormat(), id);
    return id;
}

void DatabaseIO::getIDs(const QString &table, const QString &primary_key_name, QList<QString> &existing_ids)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    query.exec("SELECT "+primary_key_name+" FROM "+table);

    query.previous();
    if (!query.next()) return;

    // set data
    query.first(); query.previous();
    while (query.next()) {
        existing_ids.append(query.value(primary_key_name).toString());
    }

    query.finish();
}

void DatabaseIO::generateID(IDGenerator* id_gen, const QList<QString> &existing_ids, const QString &id_format, QString &id)
{
    /**
     *  recursive call
     *  if id exists call this method again
    */

    id = id_gen->generate(id_format);
    if (existing_ids.contains(id))
        generateID(id_gen, existing_ids, id_format, id);
}

const QString DatabaseIO::generateBindValue(const int &i)
{
    /**
     * Assuming there are less than 99 columns in the table,
     * we hardcode the value to 10.
    */

    const QString value = (i < 10) ? ":val0"+ QString::number(i) : ":val"+ QString::number(i);
    return value;
}

void DatabaseIO::insert(DataRecord *record)
{
    QSqlQuery query(QSqlDatabase::database(connection()));

    // generate ID
    record->ID()->set(makeID(record));

    QStringList keys;
    QStringList values;

    for (DataField *field : record->fields()) {
        keys.append(field->name());
        if (field->isString())
            values.append(field->getQuoted());
        else
            values.append(field->get());
    }

    const QString query_string = "INSERT INTO "+ record->table() +" ("+ keys.join(", ") +") VALUES ("+ values.join(", ") +")";
    query.exec(query_string);
    query.finish();
}

void DatabaseIO::insert(QList<DataRecord*> records)
{
    for (DataRecord *record : records)
        insert(record);
}

void DatabaseIO::update(DataRecord *record, DataField *targetField)
{
    QSqlQuery query(QSqlDatabase::database(connection()));

    QStringList query_records;
    QMap<QString, QString> bind_values;

    int i = 0;
    for (DataField *field : record->fields()) {
        // generate bind value
        const QString value = generateBindValue(i);

        /**
         * Create a map for bind values that looks like:
        * bind_map[":val00"] = "value0"
        * bind_map[":val01"] = "value1" etc.
        */

        bind_values[value] = field->get();
        /**
         * Create a StringList for SET section like
         * "keyname0" = :val00
         * "keyname1" = :val01
        */

        query_records.append(field->name() +" = "+ value);
        i++;
    }

    // consolidate prepare
    const QString prepare_part_1  = "UPDATE "+ record->table() +" SET ";
    const QString prepare_part_2 = query_records.join(", ");
    QString prepare_part_3;
    if (targetField == nullptr) {
        prepare_part_3 = " WHERE "+ record->ID()->name() +" = ";
        prepare_part_3 += (record->isStringId()) ? record->ID()->getQuoted(): record->ID()->get();
    }
    else {
        prepare_part_3 = " WHERE "+targetField->name()+" = ";
        prepare_part_3 += (targetField->isString()) ? targetField->getQuoted(): targetField->get();
    }


    const QString prepare = prepare_part_1 + prepare_part_2 + prepare_part_3;
    query.prepare(prepare);

    // bind the values
    QMapIterator<QString, QString> bind_map(bind_values);
    while (bind_map.hasNext()) {
        bind_map.next();
        query.bindValue(bind_map.key(), bind_map.value());
    }

    query.exec();
    query.finish();
}

void DatabaseIO::update(QList<DataRecord *> records)
{
    for (DataRecord *record : records) {
        update(record);
    }
}

void DatabaseIO::update(const QString &table, DataField *updateField, DataField *targetField)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    const QString prepare_set = "SET "+updateField->name() +" = :val";

    QString prepare_where = "WHERE "+targetField->name() + " = ";
    prepare_where += (targetField->isString()) ? targetField->getQuoted() : targetField->get();

    const QString prepare = "UPDATE "+ table +" "+ prepare_set +" "+prepare_where;
    query.prepare(prepare);
    query.bindValue(":val", updateField->get());
    query.exec();
    query.finish();
}

void DatabaseIO::update(const QString &table, DataField *updateField, const QString &WHERE)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    const QString prepare_set = "SET "+updateField->name() +" = :val";
    const QString prepare = "UPDATE "+ table +" "+ prepare_set +" WHERE "+WHERE;
    query.prepare(prepare);
    query.bindValue(":val", updateField->get());
    query.exec();
    query.finish();
}

void DatabaseIO::select(DataRecord* record, DataField *targetField)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    QString query_string;
    if (targetField == nullptr) {
        query_string = "SELECT * FROM "+record->table()+" WHERE "+record->ID()->name()+" = ";
        query_string += (record->isStringId()) ? record->ID()->getQuoted() : record->ID()->get();
    }
    else {
        query_string = "SELECT * FROM "+record->table()+" WHERE "+targetField->name()+" = ";
        query_string += (targetField->isString()) ? targetField->getQuoted() : targetField->get();
    }

    query.exec(query_string);
    query.previous();
    if (!query.next()) return;

    // set data
    query.first();
    for (int i = 0; i < query.record().count(); i++)
        record->setField(query.record().fieldName(i),query.value(i).toString());

    query.finish();
}

void DatabaseIO::select(const QString &table, DataRecordRawList *outputList, DataField *targetField)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    QString query_string;
    if (targetField == nullptr) {
        query_string = "SELECT * FROM "+table;
    }
    else {
        query_string = "SELECT * FROM "+table+" WHERE "+ targetField->name() +" = ";
        query_string += (targetField->isString()) ? targetField->getQuoted() : targetField->get();
    }

    query.exec(query_string);

    query.previous();
    if (!query.next()) return;

    query.first(); query.previous();

    // set data
    while (query.next()) {
        DataFieldHolder *holder = new DataFieldHolder();
        for (int i = 0; i < query.record().count(); i++){
            const QString fieldName = query.record().fieldName(i);
            int type = query.record().field(fieldName).typeID();
            const bool isString = type == QMetaType::QString;
            const QString value = query.value(i).toString();
            DataField* field = new DataField(query.record().fieldName(i), isString);
            field->set(value);
            holder->add(field);
        }
        outputList->add(holder);
    }
    query.finish();
}

void DatabaseIO::del(DataRecord *record)
{
    QSqlQuery query(QSqlDatabase::database(connection()));
    QString query_string = "DELETE FROM "+ record->table() +" WHERE "+ record->ID()->name() +" = ";
    query_string += (record->isStringId()) ? record->ID()->getQuoted() : record->ID()->get();

    query.exec(query_string);
    query.finish();
}

void DatabaseIO::del(QList<DataRecord *> records)
{
    for (DataRecord *record : records) {
        del(record);
    }
}

void DatabaseIO::del(const QString &table, DataField *targetField)
{
    QSqlQuery query(QSqlDatabase::database(connection()));

    QString query_string = "DELETE FROM "+ table +" WHERE "+ targetField->name() +" = ";
    query_string += (targetField->isString()) ? targetField->getQuoted() : targetField->get();

    query.exec(query_string);
    query.finish();
}

QString DatabaseIO::connection() const
{
    return m_connection;
}

void DatabaseIO::setConnection(const QString &newConnection)
{
    m_connection = newConnection;
}

