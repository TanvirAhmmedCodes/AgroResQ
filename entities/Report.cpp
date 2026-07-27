#include "Report.h"

#include <sstream>


namespace AgroResQ
{
namespace Entities
{


Report::Report()
{
}



Report::Report(
    int id,
    const std::string& title,
    const std::string& description,
    const std::string& date)
{

    setId(id);

    this->title = title;

    this->description = description;

    this->date = date;

}






void Report::setTitle(
    const std::string& title)
{

    this->title = title;

}



void Report::setDescription(
    const std::string& description)
{

    this->description = description;

}



void Report::setDate(
    const std::string& date)
{

    this->date = date;

}






std::string Report::getTitle() const
{

    return title;

}



std::string Report::getDescription() const
{

    return description;

}



std::string Report::getDate() const
{

    return date;

}






std::string Report::toString() const
{

    std::stringstream stream;


    stream
    << getId()
    << ","
    << title
    << ","
    << description
    << ","
    << date;



    return stream.str();

}


}
}