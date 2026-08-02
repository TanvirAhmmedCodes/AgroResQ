#include "Disaster.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        static std::string DisasterType[] = {"", "Flood", "Cyclone", "Riverbank Erosion", "Earthquake", "Fire"};
        static std::string Divisions[] = {"", "Dhaka", "Chattogram", "Rajshahi", "Rangpur", "Khulna", "Barishal", "Sylhet", "Mymensingh"};
        static std::string Severity[] = {"", "Low", "Medium", "High", "Critical"};
        static std::string Status[] = {"", "Active", "Under Control", "Resolved"};

        static std::string dhakaDistricts[] = {"", "Dhaka", "Faridpur", "Gazipur", "Gopalganj", "Kishoreganj", "Madaripur", "Manikganj", "Munshiganj", "Narayanganj", "Narsingdi", "Rajbari", "Shariatpur", "Tangail"};
        static std::string chattogramDistricts[] = {"", "Chattogram", "Bandarban", "Brahmanbaria", "Chandpur", "Cumilla", "Coxsbazar", "Feni", "Khagrachari", "Lakshmipur", "Noakhali", "Rangamati"};
        static std::string rajshahiDistricts[] = {"", "Rajshahi", "Bogura", "Joypurhat", "Naogaon", "Natore", "Chapainawabganj", "Pabna", "Sirajganj"};
        static std::string rangpurDistricts[] = {"", "Rangpur", "Dinajpur", "Gaibandha", "Kurigram", "Lalmonirhat", "Nilphamari", "Panchagarh", "Thakurgaon"};
        static std::string khulnaDistricts[] = {"", "Khulna", "Bagerhat", "Chuadanga", "Jashore", "Jhenaidah", "Kushtia", "Magura", "Meherpur", "Narail", "Satkhira"};
        static std::string barishalDistricts[] = {"", "Barishal", "Barguna", "Bhola", "Jhalakathi", "Patuakhali", "Pirojpur"};
        static std::string sylhetDistricts[] = {"", "Sylhet", "Habiganj", "Moulivibazar", "Sunamganj"};
        static std::string mymensinghDistricts[] = {"", "Mymensingh", "Jamalpur", "Netrokona", "Sherpur"};

        static std::string* allDistricts[] = {nullptr, dhakaDistricts, chattogramDistricts, rajshahiDistricts, rangpurDistricts, khulnaDistricts, barishalDistricts, sylhetDistricts, mymensinghDistricts};
        static int districtCount[] = {0, 13, 11, 8, 8, 10, 6, 4, 4};

        Disaster::Disaster() : severity(1), division(0), district(0), disasterType(0), affectedPeople(0), status(1) {}

        Disaster::Disaster(int id, const std::string& name, const std::string& type,
                           const std::string& location, const std::string& date, int severity,
                           int division, int district, int disasterType,
                           int affectedPeople, int status)
        {
            setId(id);
            this->name = name;
            this->type = type;
            this->location = location;
            this->date = date;
            this->severity = severity;
            this->division = division;
            this->district = district;
            this->disasterType = disasterType;
            this->affectedPeople = affectedPeople;
            this->status = status;
        }

        void Disaster::setName(const std::string& name) { this->name = name; }
        void Disaster::setType(const std::string& type) { this->type = type; }
        void Disaster::setLocation(const std::string& location) { this->location = location; }
        void Disaster::setDate(const std::string& date) { this->date = date; }
        void Disaster::setSeverity(int severity) { this->severity = severity; }
        void Disaster::setDivision(int division) { this->division = division; }
        void Disaster::setDistrict(int district) { this->district = district; }
        void Disaster::setDisasterType(int disasterType) { this->disasterType = disasterType; }
        void Disaster::setAffectedPeople(int affectedPeople) { this->affectedPeople = affectedPeople; }
        void Disaster::setStatus(int status) { this->status = status; }

        std::string Disaster::getName() const { return name; }
        std::string Disaster::getType() const { return type; }
        std::string Disaster::getLocation() const { return location; }
        std::string Disaster::getDate() const { return date; }
        int Disaster::getSeverity() const { return severity; }
        int Disaster::getDivision() const { return division; }
        int Disaster::getDistrict() const { return district; }
        int Disaster::getDisasterType() const { return disasterType; }
        int Disaster::getAffectedPeople() const { return affectedPeople; }
        int Disaster::getStatus() const { return status; }

        std::string Disaster::getDivisionName() const
        {
            return (division >= 1 && division <= 8) ? Divisions[division] : "Unknown";
        }

        std::string Disaster::getDistrictName() const
        {
            if (division >= 1 && division <= 8 && district >= 1 && district <= districtCount[division])
                return allDistricts[division][district];
            return "Unknown";
        }

        std::string Disaster::getDisasterTypeName() const
        {
            return (disasterType >= 1 && disasterType <= 5) ? DisasterType[disasterType] : "Unknown";
        }

        std::string Disaster::getStatusName() const
        {
            return (status >= 1 && status <= 3) ? Status[status] : "Unknown";
        }

        std::string Disaster::getSeverityName() const
        {
            return (severity >= 1 && severity <= 4) ? Severity[severity] : "Unknown";
        }

        std::string Disaster::toString() const
        {
            std::stringstream stream;
            stream << getId() << "," << name << "," << type << "," << location << ","
                   << date << "," << severity << "," << division << "," << district << ","
                   << disasterType << "," << affectedPeople << "," << status;
            return stream.str();
        }
    }
}