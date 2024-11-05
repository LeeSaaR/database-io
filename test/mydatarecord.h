#ifndef MYDATARECORD_H
#define MYDATARECORD_H

#include "datarecord.h"

class MyDataRecord : public DataRecord
{

public:
    DataField *id;
    DataField *name;
    DataField *email;

public:
    MyDataRecord();
    ~MyDataRecord();

public:
    virtual DataField* ID() override;
};

#endif // MYDATARECORD_H
