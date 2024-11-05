#include "databaseiotest.h"

#include "core_databaseio.h"
#include "mydatarecord.h"
#include "mydatabasemodel.h"

DataBaseIOTest::DataBaseIOTest()
{

}

void DataBaseIOTest::run()
{
    /**
     * Choose a database absolute file path and connection name!
     * Here the default path is . so the database file is
     * saved where the application is running.
     * You can choose any path you like.
    */

    const QString filename = "app.db";

    /**
     * The connection name can be random. It is good if your application
     * keeps track of the connection names, espacially when your connecting
     * to multiple databases.
    */

    const QString connection = "conn_app_db";

    /**
     * How to create a database.
    */

    MyDatabaseModel *model = MyDatabaseModel::GetInstance();
    DataBaseIOTest::createDatabase(filename, connection, model);

    /**
     * How to open / connect to an existing database.
    */

//    DataBaseIOTest::connectDatabase(filename, connection);

    /**
     * How to make Operations
    */

//    DataBaseIOTest::deleteAll();
//    DataBaseIOTest::insertSingleRecord(connection);
//    DataBaseIOTest::insertMultipleRecords();
//    DataBaseIOTest::selectSingle();
//    DataBaseIOTest::selectSingleByField();
//    DataBaseIOTest::selectAllRecords();
//    DataBaseIOTest::selectRecordsWithTargetField();
//    DataBaseIOTest::updateRecord();
//    DataBaseIOTest::updateRecordByTargetField();
//    DataBaseIOTest::deleteRecord();
}

void DataBaseIOTest::createDatabase(const QString &db_filename, const QString &db_connection_name, DatabaseModel *model)
{
    /*
     * DatabaseConnector is a Singleton, so you have global access to it.
     * It can create a database and it can connect to an existing database.
    */

    DatabaseConnector *db_connector = DatabaseConnector::GetInstance();

    // Use your DatabaseModel to create a database
    if (!db_connector->createDatabase(db_filename, db_connection_name, model))
    {
        // DatabaseConnector returns true on successful creation
        qDebug() << "ERROR: createDatabase() failed";
        exit(0);
    }

    /*
     *  After you created a database or after you connected to an existing database,
     *  you must tell DatabaseIO the connection name.
    */

    initDatabaseIO(db_connection_name);
}

void DataBaseIOTest::connectDatabase(const QString &db_filename, const QString &db_connection_name)
{
    /*
     * DatabaseConnector is a Singleton, so you have global access to it.
     * It can create a database and it can connect to an existing database.
    */

    DatabaseConnector *db_connector = DatabaseConnector::GetInstance();

    if (!db_connector->connectDatabase(db_filename, db_connection_name))
    {
        // database connector returns true on successful connection
        qDebug() << "ERROR: connectDatabase() failed";
        exit(0);
    }

    /*
     *  After you created a database or after you connected to an existing database,
     *  you must tell DatabaseIO the connection name.
    */

    initDatabaseIO(db_connection_name);
}

void DataBaseIOTest::initDatabaseIO(const QString &connection)
{
    /*
     * DatabaseIO is a Singleton, so you have global access.
     * You must set the connection with DatabaseIO::setConnection()
     * to tell DatabaseIO what connection it should use, even
     * if you created a database with DatabaseConnector::createDatabase()
     * or DatabaseConnector::connectDatabase(). DatabaseConnector only
     * creates a and/or establishes a connection to a database. DatabaseIO
     * needs to know what connection DatabaseConnector established.
     */

    DatabaseIO *db = DatabaseIO::GetInstance();

    /*
     * If you have multiple databases running
     * you can use DatabaseIO::setConnection(db_connection_name)
     * to switch to the database with "db_connection_name".
     * Do this call before you do operations on the DatabaseIO.
    */

    db->setConnection(connection);
}

void DataBaseIOTest::insertSingleRecord(const QString &connection)
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    /*
     * If needed change the connection to the desired database
    */

    db->setConnection(connection);

    MyDataRecord user = MyDataRecord();
    user.name->set("Toni");
    user.email->set("iron@man.com");
    db->insert(&user);

    user.printData();
}

void DataBaseIOTest::insertMultipleRecords()
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    QList<DataRecord*> users;

    // record 1
    MyDataRecord user_1 = MyDataRecord();
    user_1.name->set("Romanov");
    user_1.email->set("black@widow.com");
    users.append((DataRecord*)&user_1);

    // record 2
    MyDataRecord user_2 = MyDataRecord();
    user_2.name->set("Logan");
    user_2.email->set("logan@x.com");
    users.append((DataRecord*)&user_2);

    users.append(new MyDataRecord());
    ((MyDataRecord*)users.last())->name->set("C-Style-Cast");
    ((MyDataRecord*)users.last())->email->set("cs@cast.h");

    db->insert(users);

    for (DataRecord* user : users) {
        user->printData();
    }
}

void DataBaseIOTest::selectSingle()
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    // insert record
    MyDataRecord user = MyDataRecord();
    user.name->set("Toni");
    user.email->set("iron@man.com");
    db->insert(&user);

    user.printData();

    const QString pretendWeSearchForSomeID = user.id->get();

    // select record
    MyDataRecord some_user = MyDataRecord();
    some_user.id->set(pretendWeSearchForSomeID);
    db->select(&some_user);

    some_user.printData();
}

void DataBaseIOTest::selectSingleByField()
{
    qDebug() << __FUNCTION__;
    DatabaseIO *db = DatabaseIO::GetInstance();

    // insert record
    MyDataRecord user = MyDataRecord();
    user.name->set("SonGuko");
    user.email->set("goku@z.com");
    db->insert(&user);

    qDebug() << "user:";
    user.printData();

    // select record
    MyDataRecord some_user = MyDataRecord();
    DataField targetField = DataField(QString("email"), QString("goku@z.com"));
    db->select(&some_user, &targetField);

    qDebug() << "some_user:";
    some_user.printData();
}

void DataBaseIOTest::selectAllRecords()
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    insertMultipleRecords();

    DataRecordRawList list = DataRecordRawList();
    db->select("users", &list);
    QList<MyDataRecord*> users = DataRecordConverter::getType<MyDataRecord>(&list);

    for (MyDataRecord* user : users){
        user->printData();
    }
}

void DataBaseIOTest::selectRecordsWithTargetField()
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    insertMultipleRecords();

    DataRecordRawList list = DataRecordRawList();
    DataField targetField = DataField(QString("name"), QString("Logan"));
    db->select("users", &list, &targetField);
    QList<MyDataRecord*> users = DataRecordConverter::getType<MyDataRecord>(&list);

    for (MyDataRecord* user : users){
        user->printData();
    }
}

void DataBaseIOTest::updateRecord()
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    // create a user
    MyDataRecord user = MyDataRecord();
    user.name->set("Some Name");
    user.email->set("some@email.de");
    db->insert(&user);
    // now user has id

    user.printData();

    // update user
    user.name->set("Mary");
    user.email->set("poppins@wool.pl");
    db->update(&user);

    user.printData();
}

void DataBaseIOTest::updateRecordByTargetField()
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    // create a user
    MyDataRecord user = MyDataRecord();
    user.name->set("Some Name");
    user.email->set("some@email.de");
    db->insert(&user);
    // now user has id

    user.printData();
    const QString pretendWeFoundTheEmail = "some@email.de";

    // update user
    MyDataRecord some_user = MyDataRecord();
    some_user.name->set("Mary");
    some_user.email->set("poppins@wool.pl");

    DataField targetField(QString("email"), pretendWeFoundTheEmail);
    db->update(&some_user, &targetField);

    // Woops! ID is gone. So be carful with this update.
    some_user.printData();
}

void DataBaseIOTest::deleteRecord()
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    // create a user
    MyDataRecord user = MyDataRecord();
    user.name->set("Apple");
    user.email->set("apple@fruity.dev");
    db->insert(&user);

    user.printData();

    MyDataRecord other_user = MyDataRecord();
    other_user.name->set("Banana");
    other_user.email->set("banana@fruity.dev");
    db->insert(&other_user);

    // only delete user
    db->del(&user);
}

void DataBaseIOTest::deleteAll()
{
    DatabaseIO *db = DatabaseIO::GetInstance();

    // get all users
    DataRecordRawList list = DataRecordRawList();
    db->select("users", &list);
    QList<DataRecord*> raw_records = DataRecordConverter::getRawDirect<MyDataRecord>(&list);

    db->del(raw_records);
    while (!raw_records.isEmpty()) {
        DataRecord* r = raw_records.last();
        raw_records.removeLast();
        delete r;
    }
}
