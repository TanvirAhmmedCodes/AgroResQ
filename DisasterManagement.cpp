#include <bits/stdc++.h>
using namespace std;

struct Disaster
{
    string disasterID, date;
    int disasterType, division, district, severity, affectedPeople, status;
};

Disaster disaster;

string DisasterType[] = {"", "Flood", "Cyclone", "Riverbank Erosion", "Earthquake", "Fire"};

string divisions[] = {"", "Dhaka", "Chattogram", "Rajshahi", "Rangpur ", "Khulna ", "Barishal ", "Sylhet", "Mymensingh"};

string dhakaDistricts[] = {"", "Dhaka", "Faridpur", "Gazipur", "Gopalganj", "Kishoreganj", "Madaripur", "Manikganj", "Munshiganj", "Narayanganj", "Narsingdi", "Rajbari", "Shariatpur", "Tangail"};
string chattogramDistrict[] = {"", "Chattogram", "Bandarban", "Brahmanbaria", "Chandpur", "Cumilla", "Coxsbazar", "Feni", "Khagrachari", "Lakshmipur", "Noakhali", "Rangamati"};
string rajshahiDistrict[] = {"", "Rajshahi", "Bogura", "Joypurhat", "Naogaon", "Natore", "Chapainawabganj", "Pabna", "Sirajganj"};
string rangpurDistrict[] = {"", "Rangpur", "Dinajpur", "Gaibandha", "Kurigram", "Lalmonirhat", "Nilphamari", "Panchagarh", "Thakurgaon"};
string khulnaDistrict[] = {"", "Khulna", "Bagerhat", "Chuadanga", "Jashore", "Jhenaidah", "Kushtia", "Magura", "Meherpur", "Narail", "Satkhira"};
string barishalDistrict[] = {"", "Barishal", "Barguna", "Bhola", "Jhalakathi", "Patuakhali", "Pirojpur"};
string sylhetDistrict[] = {"", "Sylhet", "Habiganj", "Moulivibazar", "Sunamganj"};
string mymensinghDistrict[] = {"", "Mymensingh", "Jamalpur", "Netrokona", "Sherpur"};
string *allDistricts[] = {nullptr, dhakaDistricts, chattogramDistrict, rajshahiDistrict, rangpurDistrict, khulnaDistrict, barishalDistrict, sylhetDistrict, mymensinghDistrict};
int districtCount[] = {0, 13, 11, 8, 8, 10, 6, 4, 4};

string Severity[] = {"", "Low", "Medium", "High", "Critical"};
string Status[] = {"", "Active", "Under Control", "Resolved"};

void showDisasterMenu()
{
    cout << "\n\n\t\t\t\t\t\t----Disaster Management----\n\n\t\t\t\t\t\t Choose an option.\n\t\t\t\t\t\t1. Register Disaster\n\t\t\t\t\t\t2. View Disaster\n\t\t\t\t\t\t3. Search Disaster\n\t\t\t\t\t\t4. Update Disaster\n\t\t\t\t\t\t5. Delete Disaster\n\t\t\t\t\t\t6. Back";
    cout << "\n\n\t\t\t\t\t\tEnter a option: ";
}

void showInvalidMessage()
{
    cout << "\n\t\t\t\t\t\tInvalid Choice.\n\t\t\t\t\t\tTry Again.";
    cout << "\n\n\t\t\t\t\t\tEnter your choice: ";
}

int inputChoice(int min, int max)
{
    int value;
    while (true)
    {
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\n\t\t\t\t\t\tInvalid input.";
            cout << "\n\t\t\t\t\t\tPlease enter a number: ";
        }
        else if (value < min || value > max)
        {
            cout << "\n\t\t\t\t\t\tInvalid Choice.";
            cout << "\n\t\t\t\t\t\tEnter again: ";
        }
        else
        {
            return value;
        }
    }
}

int inputPositiveInteger()
{
    int value;
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\n\t\t\t\t\t\tInvalid input.";
            cout << "\n\t\t\t\t\t\tEnter again: ";
        }
        else if (value < 0)
        {
            cout << "\n\t\t\t\t\t\tValue cannot be negative.";
            cout << "\n\t\t\t\t\t\tEnter again: ";
        }
        else
        {
            return value;
        }
    }
}

void inputDisasterID()
{
    cout << "\n\t\t\t\t\t\tEnter Disaster ID: ";
    cin >> disaster.disasterID;
}

void inputDisasterType()
{

    cout << "\n\t\t\t\t\t\tSelect Disaster Type:\n\t\t\t\t\t\t1. Flood\n\t\t\t\t\t\t2. Cyclone\n\t\t\t\t\t\t3. Riverbank Erosion\n\t\t\t\t\t\t4. Earthquake\n\t\t\t\t\t\t5. Fire";
    cout << "\n\t\t\t\t\t\tEnter your choice: ";
    disaster.disasterType = inputChoice(1, 5);
}

void inputDivDis()
{
    cout << "\n\t\t\t\t\t\tSelect Division:\n\t\t\t\t\t\t1. Dhaka\n\t\t\t\t\t\t2. Chattogram\n\t\t\t\t\t\t3. Rajshahi\n\t\t\t\t\t\t4. Rangpur\n\t\t\t\t\t\t5. Khulna\n\t\t\t\t\t\t6. Barishal\n\t\t\t\t\t\t7. Sylhet\n\t\t\t\t\t\t8. Mymensingh";
    cout << "\n\t\t\t\t\t\tEnter your choice: ";
    disaster.division = inputChoice(1, 8);

    switch (disaster.division)
    {
    case 1:
        cout << "\n\t\t\t\t\t\tSelect District:\n\t\t\t\t\t\t1. Dhaka\n\t\t\t\t\t\t2. Faridpur\n\t\t\t\t\t\t3. Gazipur\n\t\t\t\t\t\t4. Gopalganj\n\t\t\t\t\t\t5. Kishoreganj\n\t\t\t\t\t\t6. Madaripur\n\t\t\t\t\t\t7. Manikganj\n\t\t\t\t\t\t8. Munshiganj\n\t\t\t\t\t\t9. Narayanganj\n\t\t\t\t\t\t10. Narsingdi\n\t\t\t\t\t\t11. Rajbari\n\t\t\t\t\t\t12. Shariatpur\n\t\t\t\t\t\t13. Tangail ";
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        disaster.district = inputChoice(1, districtCount[disaster.division]);
        break;
    case 2:
        cout << "\n\t\t\t\t\t\tSelect District:\n\t\t\t\t\t\t1. Chattogram\n\t\t\t\t\t\t2. Bandarban\n\t\t\t\t\t\t3. Brahmanbaria\n\t\t\t\t\t\t4. Chandpur\n\t\t\t\t\t\t5. Cumilla\n\t\t\t\t\t\t6. Coxsbazar\n\t\t\t\t\t\t7. Feni\n\t\t\t\t\t\t8. Khagrachari\n\t\t\t\t\t\t9. Lakshmipur\n\t\t\t\t\t\t10. Noakhali\n\t\t\t\t\t\t11. Rangamati";
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        disaster.district = inputChoice(1, districtCount[disaster.division]);
        break;
    case 3:
        cout << "\n\t\t\t\t\t\tSelect District:\n\t\t\t\t\t\t1. Rajshahi\n\t\t\t\t\t\t2. Bogura\n\t\t\t\t\t\t3. Joypurhat\n\t\t\t\t\t\t4. Naogaon\n\t\t\t\t\t\t5. Natore\n\t\t\t\t\t\t6. Chapainawabganj\n\t\t\t\t\t\t7. Pabna\n\t\t\t\t\t\t8. Sirajganj";
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        disaster.district = inputChoice(1, districtCount[disaster.division]);
        break;
    case 4:
        cout << "\n\t\t\t\t\t\tSelect District:\n\t\t\t\t\t\t1. Rangpur\n\t\t\t\t\t\t2. Dinajpur\n\t\t\t\t\t\t3. Gaibandha\n\t\t\t\t\t\t4. Kurigram\n\t\t\t\t\t\t5. Lalmonirhat\n\t\t\t\t\t\t6. Nilphamari\n\t\t\t\t\t\t7. Panchagarh\n\t\t\t\t\t\t8. Thakurgaon";
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        disaster.district = inputChoice(1, districtCount[disaster.division]);
        break;
    case 5:
        cout << "\n\t\t\t\t\t\tSelect District:\n\t\t\t\t\t\t1. Khulna\n\t\t\t\t\t\t2. Bagerhat\n\t\t\t\t\t\t3. Chuadanga\n\t\t\t\t\t\t4. Jashore\n\t\t\t\t\t\t5. Jhenaidah\n\t\t\t\t\t\t6. Kushtia\n\t\t\t\t\t\t7. Magura\n\t\t\t\t\t\t8. Meherpur\n\t\t\t\t\t\t9. Narail\n\t\t\t\t\t\t10. Satkhira";
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        disaster.district = inputChoice(1, districtCount[disaster.division]);
        break;
    case 6:
        cout << "\n\t\t\t\t\t\tSelect District:\n\t\t\t\t\t\t1. Barishal\n\t\t\t\t\t\t2. Barguna\n\t\t\t\t\t\t3. Bhola\n\t\t\t\t\t\t4. Jhalakathi\n\t\t\t\t\t\t5. Patuakhali\n\t\t\t\t\t\t6. Pirojpur";
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        disaster.district = inputChoice(1, districtCount[disaster.division]);
        break;
    case 7:
        cout << "\n\t\t\t\t\t\tSelect District:\n\t\t\t\t\t\t1. Sylhet\n\t\t\t\t\t\t2. Habiganj\n\t\t\t\t\t\t3. Moulivibazar\n\t\t\t\t\t\t4. Sunamganj";
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        disaster.district = inputChoice(1, districtCount[disaster.division]);
        break;
    case 8:
        cout << "\n\t\t\t\t\t\tSelect District:\n\t\t\t\t\t\t1. Mymensingh\n\t\t\t\t\t\t2. Jamalpur\n\t\t\t\t\t\t3. Netrokona\n\t\t\t\t\t\t4. Sherpur";
        cout << "\n\t\t\t\t\t\tEnter your choice: ";
        disaster.district = inputChoice(1, districtCount[disaster.division]);
        break;
    }
}

void inputDate()
{
    cout << "\n\t\t\t\t\t\tEnter Date(DD-MM-YYYY): ";
    cin >> disaster.date;
}

void inputSeverity()
{
    cout << "\n\t\t\t\t\t\tSelect Severity:\n\t\t\t\t\t\t1. Low\n\t\t\t\t\t\t2. Medium\n\t\t\t\t\t\t3. High\n\t\t\t\t\t\t4. Critical";
    cout << "\n\t\t\t\t\t\tEnter your choice: ";
    disaster.severity = inputChoice(1, 4);
}

void inputAffectedPeople()
{
    cout << "\n\t\t\t\t\t\tEnter number of affected people(estimated): ";
    disaster.affectedPeople = inputPositiveInteger();
}

void inputStatus()
{
    cout << "\n\t\t\t\t\t\tSelect Status: \n\t\t\t\t\t\t1. Active\n\t\t\t\t\t\t2. Under Control\n\t\t\t\t\t\t3. Resolved";
    cout << "\n\t\t\t\t\t\tEnter your choice: ";
    disaster.status = inputChoice(1, 3);
}

void showDisasterDetails()
{

    cout << "\n\n\t\t\t\t\t\t----Disaster Details----\n";
    cout << "\n\t\t\t\t\t\tDisaster ID: " << disaster.disasterID;

    string disasterName, divisionName, districtName, severityLvl, Stat;

    cout << "\n\t\t\t\t\t\tDisaster Type: " << DisasterType[disaster.disasterType];

    cout << "\n\t\t\t\t\t\tDivision: " << divisions[disaster.division];
    cout << "\n\t\t\t\t\t\tDistrict: " << allDistricts[disaster.division][disaster.district];

    cout << "\n\t\t\t\t\t\tDate: " << disaster.date;

    cout << "\n\t\t\t\t\t\tSeverity: " << Severity[disaster.severity];

    cout << "\n\t\t\t\t\t\tNumber of affected people(estimated): " << disaster.affectedPeople;

    cout << "\n\t\t\t\t\t\tStatus: " << Status[disaster.status];
}

void registerDisaster()
{
    cout << "\n\n\t\t\t\t\t\t----Register Disaster----\n\n\t\t\t\t\t\tEnter Disaster Details.\n";

    inputDisasterID();
    inputDisasterType();
    inputDivDis();
    inputDate();
    inputSeverity();
    inputAffectedPeople();
    inputStatus();
    showDisasterDetails();
}

void viewDisaster()
{
}

void SearchDisaster()
{
}

void updateDisaster()
{
}

void deleteDisaster()
{
}

void Back()
{
    cout << "\n\t\t\t\t\t\tThank you.";
}
int main()
{
    int option;

    while (true)
    {
        showDisasterMenu();

        option = inputChoice(1, 6);

        switch (option)
        {
        case 1:
            registerDisaster();
            break;
        case 2:
            viewDisaster();
            break;
        case 3:
            SearchDisaster();
            break;
        case 4:
            updateDisaster();
            break;
        case 5:
            deleteDisaster();
            break;
        case 6:
            Back();
            return 0;
        }
        cout << "\n\n\n\t\t\t\t\t\tPress enter to continue.......";
        cin.ignore();
        cin.get();
    }
    return 0;
}