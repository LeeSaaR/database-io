#include "datafield.h"

DataField::DataField(const QString& name, const bool& isString) :
    m_name(name),
    m_isString(isString)
{
}

DataField::DataField(const QString& name, const QString& newValue, const bool& isString) :
    m_name(name),
    m_value(newValue),
    m_isString(isString)
{
}

DataField::~DataField()
{
}

// GETTER & SETTER
QString DataField::name() const
{
    return m_name;
}

QString DataField::get() const
{
    return m_value;
}

QString DataField::getQuoted() const
{
    return "\""+ m_value + "\"";
}

void DataField::set(const QString &newValue)
{
    m_value = newValue;
}

bool DataField::isString() const
{
    return m_isString;
}
