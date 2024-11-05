#ifndef DATARECORD_H
#define DATARECORD_H

#include <QString>
#include <QMap>

#include "datafield.h"
#include "datafieldholder.h"

class DataRecord
{
    /*
     * This class is used to pass data from the app to the DatabaseIO class.
     * DatabaseIO doesn't know how to handle a specific DataRecord, but it knows
     * how to handle the base DataRecord.
     *
     * For each table in the database you create a specific DataRecord class that
     * derives from DataRecord e.g.:
     *
     * Assuming we have a table:
     *
     * CREATE TABLE users (
     * id TEXT PRIMARY KEY UNIQUE,
     * name TEXT )
     *
     * Then we would create a class:
     *
     * class DataRecordUsers : public DataRecord
     * {
     *   private:
     *     DataField *id;
     *     DataField *name;
     *   public:
     *     DataRecordUsers();
     *     virtual DataField* ID() override {return id;}
     * }
     *
     * We define the data of DataRecordUsers in its constructor:
     * DataRecordUsers::DataRecordUsers()
     * {
     *   setTable("users");
     *   setIsStringId(true);
     *   setIdFormat("CCNNNCC");
     *
     *   DataField *id = new DataField("id");
     *   DataField *name = new DataField("name");
     *
     *   m_fields.append(id);
     *   m_fields.append(name);
     * }
     *
     * Now DataRecord's m_fields are pointing DataRecordUser's DataFields.
     * DatabaseIO doesn't know about DataRecordUser's id and name, but it
     * can get the DataFields via DataRecord's m_fields and handles them
     * to insert, update, select and delete data from the database.
     *
     */

private:
    /*
     * The name of the table.
     */
    QString m_table;
    /*
     * Primary Key is a String
     */
    bool m_isStringId;

    /*
     * ID Format of the table's primary key.
     * C gets one of the characters defined in IDGenerator's m_id_characters
     * N gets one of the numbers defined in IDGenerator's m_id_characters
     * Other characters are not replaced
     * example formats:
     * "CCNN" could generate -> iB90 or Ta73 etc.
     * "CN-CN" could generate -> h5-e3 or Z1-g8 etc.
     * the primary key id is generated automaticly in DatabaseIO
     * before inserting to database.
    */
    QString m_idFormat;

protected:
    /*
     * All DataFields of the specific DataRecord as a list
    */
    QList<DataField*> m_fields;

public:
    DataRecord();
    virtual ~DataRecord();

public:
    /*
     * ID() is a pointer to the primary key DataField:
     * When you derive from DataRecord e.g. DataRecordUsers
     * and the primary key is:
     * DataField *id = new DataField("ID");
     *
     * be sure to override this like:
     *
     * DataField* ID() override { return id; }
    */
    virtual DataField* ID() {return nullptr;}

    /*
     * Method for development purposes
     * prints the DataFields' Names and Values
    */
    void printData();

    /*
     * This is used when we need to transfer data from
     * existing DataField to specific DataRecords' DataField.
     */
    void setField(const QString &name, const QString &value);
    void setFields(DataFieldHolder *holder);

public:
    // GETTER & SETTER
    QString table() const;
    void setTable(const QString &newTable);
    bool isStringId() const;
    void setIsStringId(bool newIsStringId);
    QList<DataField *> fields() const;
    QString idFormat() const;
    void setIdFormat(const QString &newIdFormat);
};

#endif // DATARECORD_H
