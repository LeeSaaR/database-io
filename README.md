# DatabaseIO - Database Input Ouput System

> DatabaseIO is deprecated. See:  
> [DBIO - Database Input Output](https://www.github.com/leesaar/dbio)  
> [DBIOG - Database Input Output Generator](https://www.github.com/leesaar/dbiog)

DatabaseIO is a wrapper around the QtSql Module and it is a small input-output system for SQLite3 databases in Qt applications. 
Its goals is to make the database operations easy and the project's database easy to scale and maintain.

## What can DatabaseIO do?
DatabaseIO provides query methods like insert, select, update and delete to do database operations. But you don't have to write the query manually. You first create a class ```DatabaseModel``` for the database and a class ```DataRecord``` for each table by inhereting from ```DatabaseModel``` and ```DataRecord```. You use ```DataRecord``` Objects and ```DataField``` Objects, that acts like table rows and fields. You can pass them to or receive them from DatabaseIO.

> Info
>
> Documentation of DatabaseIO is in progess.

## Setup DatabaseIO

1. Enable SQL in your Qt project.
2. Copy the database-io/ directory into your project source directory.
3. Add all files in your projects CMakeLists.txt.
4. ```#include "core_databaseio.h"```
5. Make a child class of ```DatabaseModel``` like shown
    <br /> in the example in ```database_io/test/``` directory.
6. Make a child class of ```DataRecord``` like shown in
    <br /> in the example in ```database_io/test/``` directory.
7. Use it like shown in the example ```database_io/test/```