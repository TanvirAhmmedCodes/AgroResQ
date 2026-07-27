#include "ReportMenu.h"

#include <iostream>
#include <iomanip>


namespace AgroResQ
{
namespace UI
{


ReportMenu::ReportMenu() = default;






void ReportMenu::show()
{

    int choice;


    do
    {

        std::cout
        << "\n=========================================\n";

        std::cout
        << "             REPORT MANAGEMENT\n";

        std::cout
        << "=========================================\n";


        std::cout
        << "1. Add Report\n";

        std::cout
        << "2. View Reports\n";

        std::cout
        << "3. Search Report\n";

        std::cout
        << "4. Update Report\n";

        std::cout
        << "5. Delete Report\n";

        std::cout
        << "0. Back\n";


        std::cout
        << "=========================================\n";


        std::cout
        << "Enter Choice: ";


        std::cin >> choice;



        switch(choice)
        {

        case 1:
            addReport();
            break;


        case 2:
            viewAllReports();
            break;


        case 3:
            searchReport();
            break;


        case 4:
            updateReport();
            break;


        case 5:
            deleteReport();
            break;


        case 0:
            break;


        default:

            std::cout
            << "\nInvalid Choice.\n";

        }


    }while(choice != 0);

}








void ReportMenu::addReport()
{

    std::string title;

    std::string description;

    std::string date;



    std::cin.ignore();



    std::cout
    << "\nReport Title: ";

    getline(std::cin,title);



    std::cout
    << "Description: ";

    getline(std::cin,description);



    std::cout
    << "Date: ";

    getline(std::cin,date);





    if(reportService.addReport(
        title,
        description,
        date))
    {

        std::cout
        << "\nReport Added Successfully.\n";

    }
    else
    {

        std::cout
        << "\nFailed To Add Report.\n";

    }

}








void ReportMenu::viewAllReports()
{

    auto reports =
        reportService.getAllReports();



    if(reports.empty())
    {

        std::cout
        << "\nNo Report Found.\n";

        return;

    }




    std::cout
    << "\n====================================================================\n";


    std::cout
    << std::left
    << std::setw(5)
    << "ID"

    << std::setw(25)
    << "Title"

    << std::setw(20)
    << "Date"

    << "\n";



    std::cout
    << "====================================================================\n";




    for(auto& report : reports)
    {

        std::cout
        << std::left

        << std::setw(5)
        << report.getId()

        << std::setw(25)
        << report.getTitle()

        << std::setw(20)
        << report.getDate()

        << "\n";

    }

}








void ReportMenu::searchReport()
{

    int id;


    std::cout
    << "\nReport ID: ";

    std::cin >> id;




    Entities::Report report;



    if(reportService.searchReport(
        id,
        report))
    {

        std::cout
        << "\nID          : "
        << report.getId();


        std::cout
        << "\nTitle       : "
        << report.getTitle();


        std::cout
        << "\nDescription : "
        << report.getDescription();


        std::cout
        << "\nDate        : "
        << report.getDate()

        << "\n";

    }
    else
    {

        std::cout
        << "\nReport Not Found.\n";

    }

}








void ReportMenu::updateReport()
{

    int id;


    std::string title;

    std::string description;

    std::string date;



    std::cout
    << "\nReport ID: ";

    std::cin >> id;



    std::cin.ignore();



    std::cout
    << "Title: ";

    getline(std::cin,title);



    std::cout
    << "Description: ";

    getline(std::cin,description);



    std::cout
    << "Date: ";

    getline(std::cin,date);






    if(reportService.updateReport(
        id,
        title,
        description,
        date))
    {

        std::cout
        << "\nUpdated Successfully.\n";

    }
    else
    {

        std::cout
        << "\nUpdate Failed.\n";

    }

}








void ReportMenu::deleteReport()
{

    int id;


    std::cout
    << "\nReport ID: ";

    std::cin >> id;




    if(reportService.deleteReport(id))
    {

        std::cout
        << "\nDeleted Successfully.\n";

    }
    else
    {

        std::cout
        << "\nDelete Failed.\n";

    }

}


}
}