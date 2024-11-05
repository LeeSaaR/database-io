#ifndef DATAFIELDHOLDER_H
#define DATAFIELDHOLDER_H

#include "datafield.h"

#include <QList>

class DataFieldHolder
{
private:
    QList<DataField*> m_fields;

public:
    DataFieldHolder();
    ~DataFieldHolder();
    void add(DataField* field);

    QList<DataField*> fields();
};

#endif // DATAFIELDHOLDER_H
