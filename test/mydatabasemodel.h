#ifndef MYDATABASEMODEL_H
#define MYDATABASEMODEL_H

#include <QString>
#include <QList>

#include "databasemodel.h"

class MyDatabaseModel : public DatabaseModel
{
private:
    MyDatabaseModel();

protected:
    static MyDatabaseModel *m_instance;

public:
    MyDatabaseModel(MyDatabaseModel &other) = delete;
    void operator=(const MyDatabaseModel &) = delete;
    static MyDatabaseModel *GetInstance();
    ~MyDatabaseModel();
    virtual const QList<QString> createStatements() const override;
};

#endif // MYDATABASEMODEL_H
