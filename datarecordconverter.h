#ifndef DATARECORDCONVERTER_H
#define DATARECORDCONVERTER_H

#include "datarecord.h"
#include "datarecordrawlist.h"

#include <QString>
#include <QList>
class T;

class DataRecordConverter
{

public:
    DataRecordConverter();

    template<class T>
    static QList<T*> getType(DataRecordRawList *fieldList){
        QList<T*> records;
        for (DataFieldHolder *holder : fieldList->holder()) {
            T* record = new T();
            for (DataField *field : holder->fields())
                record->setField(field->name(), field->get());
            records.append(record);

        }
        return records;
    }

    template<class T>
    static QList<DataRecord*> getRaw(QList<T*> list){
        QList<DataRecord*> records;
        for (DataRecord* record : list) {
            records.append(record);
        }
        return records;
    }

    template<class T>
    static QList<DataRecord*> getRawDirect(DataRecordRawList *fieldList){
        QList<T*> specific_records;
        for (DataFieldHolder *holder : fieldList->holder()) {
            specific_records.append(new T());
            for (DataField *field : holder->fields())
                specific_records.last()->setField(field->name(), field->get());
        }
        QList<DataRecord*> raw_records = getRaw<T>(specific_records);
        return raw_records;
    }
};

#endif // DATARECORDCONVERTER_H
