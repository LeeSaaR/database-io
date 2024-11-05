#include "datarecordrawlist.h"

DataRecordRawList::DataRecordRawList()
{

}

DataRecordRawList::~DataRecordRawList()
{
    while (!m_holder.isEmpty()){
        DataFieldHolder* _holder = m_holder.last();
        m_holder.removeLast();
        delete _holder;
    }
}

void DataRecordRawList::add(DataFieldHolder *holder)
{
    m_holder.append(holder);
}

QList<DataFieldHolder *> DataRecordRawList::holder()
{
    return m_holder;
}

//void DataRecordRawList::printSize()
//{
//    qDebug() << "holder size:" << m_holder.size();
//}
