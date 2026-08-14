#include "ReportMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/report/ReportRepository.h"
#include <iomanip>
#include <iostream>

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
        std::cout << "\n=========================================\n";
        std::cout << "             REPORT MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Report\n";
        std::cout << "2. View Reports\n";
        std::cout << "3. Search Report\n";
        std::cout << "4. Update Report\n";
        std::cout << "5. Delete Report\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1: addReport(); break;
        case 2: viewAllReports(); break;
        case 3: searchReport(); break;
        case 4: updateReport(); break;
        case 5: deleteReport(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void ReportMenu::addReport()
{
    std::string title, description, date;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tReport Title: ";
    std::getline(std::cin, title);
    std::cout << "\t\t\t\t\t\tDescription: ";
    std::getline(std::cin, description);
    std::cout << "\t\t\t\t\t\tDate: ";
    std::getline(std::cin, date);
    if(reportService.addReport(title, description, date))
        std::cout << "\n\t\t\t\t\t\tReport Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Report.\n";
}

void ReportMenu::viewAllReports()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Report> reports;
    if (Core::AuthManager::isAdmin())
        reports = reportService.getAllReports();
    else {
        Repositories::ReportRepository repo;
        reports = repo.getByTenant(currentTenant);
    }
    if(reports.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Report Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t====================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tTitle\t\t\t\tDate\n";
    std::cout << "\t\t\t\t\t\t====================================================================\n";
    for(auto& r : reports) {
        std::cout << "\t\t\t\t\t\t" << r.getId() << "\t"
                  << r.getTitle() << "\t\t\t\t"
                  << r.getDate() << "\n";
    }
}

void ReportMenu::searchReport()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tReport ID: ";
    std::cin >> id;
    Entities::Report report;
    if(reportService.searchReport(id, report)) {
        std::cout << "\n\t\t\t\t\t\tID          : " << report.getId();
        std::cout << "\n\t\t\t\t\t\tTitle       : " << report.getTitle();
        std::cout << "\n\t\t\t\t\t\tDescription : " << report.getDescription();
        std::cout << "\n\t\t\t\t\t\tDate        : " << report.getDate() << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tReport Not Found.\n";
    }
}

void ReportMenu::updateReport()
{
    int id;
    std::string title, description, date;
    std::cout << "\n\t\t\t\t\t\tReport ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tTitle: ";
    std::getline(std::cin, title);
    std::cout << "\t\t\t\t\t\tDescription: ";
    std::getline(std::cin, description);
    std::cout << "\t\t\t\t\t\tDate: ";
    std::getline(std::cin, date);
    if(reportService.updateReport(id, title, description, date))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void ReportMenu::deleteReport()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tReport ID: ";
    std::cin >> id;
    if(reportService.deleteReport(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

}
}