#ifndef DATARECORDRAWLIST_H
#define DATARECORDRAWLIST_H

#include "datafieldholder.h"

class DataRecordRawList
{
private:
    QList<DataFieldHolder *> m_holder;

public:
    DataRecordRawList();
    ~DataRecordRawList();

    void add(DataFieldHolder * holder);
    QList<DataFieldHolder *> holder();

    void printSize();
};

#endif // DATARECORDRAWLIST_H
