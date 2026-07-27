#pragma once

#include "../services/ReportService.h"


namespace AgroResQ
{
namespace UI
{

class ReportMenu
{

private:

    Services::ReportService reportService;


    void addReport();

    void viewAllReports();

    void searchReport();

    void updateReport();

    void deleteReport();



public:

    ReportMenu();


    void show();

};

}
}