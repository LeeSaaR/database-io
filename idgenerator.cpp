#include "idgenerator.h"

#include <QRandomGenerator>

IDGenerator* IDGenerator::m_instance = nullptr;

IDGenerator::IDGenerator()
{

}

IDGenerator *IDGenerator::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new IDGenerator();

    return m_instance;
}

IDGenerator::~IDGenerator()
{

}

QString IDGenerator::generate(const QString &id_format)
{
    // this method generates an id
    QString id;
    for (int i = 0; i < id_format.size(); i++) {
        if (id_format.at(i) == 'C') {
            id.append(randomChar());
        }
        else if (id_format.at(i) == 'N') {
            id.append(randomNumber());
        }
        else {
            id.append(id_format.at(i));
        }
    }
    return id;
}

QString IDGenerator::randomChar()
{
    // returns a random charakter from m_id_characters
    return QString(m_id_characters.at(QRandomGenerator::global()->bounded(0, m_id_characters.size())));
}

QString IDGenerator::randomNumber()
{
    // returns a random number m_id_numbers
    return QString(m_id_numbers.at(QRandomGenerator::global()->bounded(0, m_id_numbers.size())));
}
