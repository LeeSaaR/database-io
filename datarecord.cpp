#include "datarecord.h"

DataRecord::DataRecord()
{

}

DataRecord::~DataRecord()
{
    while (!m_fields.isEmpty()) {
        DataField* _field = m_fields.last();
        m_fields.removeLast();
        delete _field;
    }
}

//void DataRecord::printData()
//{
//    for (DataField *field : m_fields)
//        qDebug() << field->name() + " = " + field->get();
//}

void DataRecord::setField(const QString &name, const QString &value)
{
    for (DataField *field : m_fields) {
        if (field->name() == name) {
            field->set(value);
            return;
        }
    }
}

void DataRecord::setFields(DataFieldHolder *holder)
{
    m_fields.clear();
    m_fields = holder->fields();
}

// GETTER & SETTER
QString DataRecord::table() const
{
    return m_table;
}

QList<DataField *> DataRecord::fields() const
{
    return m_fields;
}

void DataRecord::setTable(const QString &newTable)
{
    m_table = newTable;
}

bool DataRecord::isStringId() const
{
    return m_isStringId;
}

void DataRecord::setIsStringId(bool newIsStringId)
{
    m_isStringId = newIsStringId;
}

QString DataRecord::idFormat() const
{
    return m_idFormat;
}

void DataRecord::setIdFormat(const QString &newIdFormat)
{
    m_idFormat = newIdFormat;
}


