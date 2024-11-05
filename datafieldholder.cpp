#include "datafieldholder.h"

DataFieldHolder::DataFieldHolder()
{

}

DataFieldHolder::~DataFieldHolder()
{
    while (!m_fields.isEmpty()) {
        DataField* _field = m_fields.last();
        m_fields.removeLast();
        delete _field;
    }
}

void DataFieldHolder::add(DataField *field)
{
    m_fields.append(field);
}

QList<DataField *> DataFieldHolder::fields()
{
    return m_fields;
}
