#include "DecisionSupportEngine.h"

#include <sstream>


namespace AgroResQ
{
namespace Algorithms
{


DecisionSupportEngine::DecisionSupportEngine() = default;





std::string DecisionSupportEngine::generateReport(
    const Entities::Soil& soil,
    const Entities::Weather& weather)
{

    std::stringstream report;



    double healthScore =
        soilHealthScore.calculate(soil);



    std::string disease =
        diseasePrediction.predict(
            soil,
            weather);



    std::string irrigation =
        irrigationPlanner.calculatePlan(
            soil,
            weather);



    std::string recovery =
        recoveryPlanner.createPlan(
            soil,
            weather);




    report
    << "========== AGRICULTURE DECISION REPORT ==========\n\n";


    report
    << "Soil Health Score : "
    << healthScore
    << "/100\n\n";



    report
    << "Disease Analysis:\n"
    << disease
    << "\n\n";



    report
    << "Irrigation Plan:\n"
    << irrigation
    << "\n\n";



    report
    << "Recovery Plan:\n"
    << recovery
    << "\n";



    report
    << "\n===============================================\n";



    return report.str();

}


}
}