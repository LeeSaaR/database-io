#ifndef DATAFIELD_H
#define DATAFIELD_H

#include <QString>

class DataField
{
private:
    /*
     * Is the column or field name of the table
    */
    const QString m_name;

    /*
     * Field value
    */
    QString m_value;

    /*
     * Keep track of if the field is a string.
     * Mostly used to enclose by quotes.
     * Is true by default.
    */
    bool m_isString;

public:
    DataField(const QString& name, const bool& isString = true);
    DataField(const QString& name, const QString& newValue, const bool &isString = true);
    ~DataField();

public:
    // GETTER & SETTER
    QString name() const;
    QString get() const;
    QString getQuoted() const;
    void set(const QString& newValue);
    bool isString() const;
};

#endif // DATAFIELD_H
