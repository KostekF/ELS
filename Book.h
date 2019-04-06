/*
* Class for storing information of single book
* and maybe in the future to do something on those info?
* ex. sort, look by key words etc.
*
*/
#ifndef BOOK_H
#define BOOK_H
#include"QString"
#include"vector"
struct authorStruct
{
    QString name="";
    QString last_name="";
};

class Book
{
public:
    Book();
    Book(authorStruct author,QString category,QString title, QString description, QString key_words, QString release_date,std::vector<QString> book_ids);

    authorStruct author() const;
    void setAuthor(const authorStruct &author);

    QString category() const;
    void setCategory(const QString &category);

    QString title() const;
    void setTitle(const QString &title);

    QString description() const;
    void setDescription(const QString &description);

    QString key_words() const;
    void setKey_words(const QString &key_words);

    QString release_date() const;
    void setRelease_date(const QString &release_date);


    const std::vector<QString> & book_ids() const;
    void setBook_ids(const std::vector<QString> &book_ids);

private:
    authorStruct author_;
    QString category_;
    QString title_;
    QString description_;
    QString key_words_;
    QString release_date_;
    std::vector<QString> book_ids_;
};

#endif // BOOK_H
