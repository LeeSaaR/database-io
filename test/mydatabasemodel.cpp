#include "mydatabasemodel.h"

MyDatabaseModel* MyDatabaseModel::m_instance= nullptr;



MyDatabaseModel::MyDatabaseModel()
{

}

MyDatabaseModel *MyDatabaseModel::GetInstance()
{
    if (m_instance == nullptr)
        m_instance = new MyDatabaseModel();

    return m_instance;
}

MyDatabaseModel::~MyDatabaseModel()
{

}

const QList<QString> MyDatabaseModel::createStatements() const
{
    return {
        "CREATE TABLE users ( "
        "id TEXT PRIMARY KEY UNIQUE, "
        "name TEXT, "
        "email TEXT )",
    };
}
