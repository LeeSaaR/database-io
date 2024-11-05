#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <QMap>
#include <QString>

class IDGenerator
{
private:
    // ID GENERATOR
    QString m_id_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    QString m_id_numbers    = "0123456789";
    QMap<QString, QString> m_id_formats;

private:
    IDGenerator();

protected:
    static IDGenerator *m_instance;

public:
    IDGenerator(IDGenerator& other) = delete;
    void operator=(const IDGenerator& other) = delete;
    static IDGenerator* GetInstance();
    ~IDGenerator();


private:
    QString randomChar();
    QString randomNumber();

public:
    QString generate(const QString &id_format);
};

#endif // IDGENERATOR_H
