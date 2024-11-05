#include "mydatarecord.h"

MyDataRecord::MyDataRecord()
{
    // set base class members
    setTable("users");
    setIsStringId(true);
    setIdFormat("CCNNNCC");

    // define data
    id = new DataField("id");
    name = new DataField("name");
    email = new DataField("email");

    // connect specific to generic class
    m_fields.append(id);
    m_fields.append(name);
    m_fields.append(email);
}

MyDataRecord::~MyDataRecord()
{
}

DataField *MyDataRecord::ID()
{
    return id;
}
