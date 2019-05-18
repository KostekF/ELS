#include "Book.h"

Book::Book()
{
    //author_;
    category_="";
    title_="";
    description_="";
    key_words_="";
    release_date_="";
   // book_ids_.push_back("000000");
}


/*
Book::Book(authorStruct author,QString category,QString title, QString description, QString key_words, QString release_date,std::vector<QString> book_ids)
{
    author_=author;
    category_=category;
    title_=title;
    description_=description;
    key_words_=key_words;
    release_date_=release_date;
    book_ids_=book_ids;
}
*/

Book::Book(authorStruct author,QString category,QString title, QString description, QString key_words, QString release_date)
 {
     author_=author;
     category_=category;
     title_=title;
     description_=description;
     key_words_=key_words;
     release_date_=release_date;
 }
QString Book::category() const
{
    return category_;
}

void Book::setCategory(const QString &category)
{
    category_ = category;
}

QString Book::title() const
{
    return title_;
}

void Book::setTitle(const QString &title)
{
    title_ = title;
}

QString Book::description() const
{
    return description_;
}

void Book::setDescription(const QString &description)
{
    description_ = description;
}

QString Book::key_words() const
{
    return key_words_;
}

void Book::setKey_words(const QString &key_words)
{
    key_words_ = key_words;
}

QString Book::release_date() const
{
    return release_date_;
}

void Book::setRelease_date(const QString &release_date)
{
    release_date_ = release_date;
}

/*
const std::vector<QString> & Book::book_ids() const
{
    return book_ids_;
}

void Book::setBook_ids(const std::vector<QString> &book_ids)
{
    book_ids_ = book_ids;
}
*/
authorStruct Book::author() const
{
    return author_;
}

void Book::setAuthor(const authorStruct &author)
{
    author_ = author;
}
