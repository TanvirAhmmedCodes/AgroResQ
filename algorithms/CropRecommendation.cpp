#include "CropRecommendation.h"

#include <algorithm>


namespace AgroResQ
{
namespace Algorithms
{


CropRecommendation::CropRecommendation() = default;



double CropRecommendation::calculateScore(
    const Entities::Crop& crop,
    const Entities::Soil& soil) const
{

    double score = 0;


    if(crop.getSuitableSoil() == soil.getSoilType())
    {
        score += 50;
    }


    if(soil.getPhLevel() >= 5 &&
       soil.getPhLevel() <= 8)
    {
        score += 25;
    }


    if(soil.getMoisture() >= 30 &&
       soil.getMoisture() <= 70)
    {
        score += 25;
    }


    return score;
}



std::vector<Entities::Crop> CropRecommendation::recommend(
    const std::vector<Entities::Crop>& crops,
    const Entities::Soil& soil) const
{

    std::vector<std::pair<double, Entities::Crop>> scoredCrops;


    for(const auto& crop : crops)
    {

        double score =
            calculateScore(crop, soil);


        scoredCrops.push_back(
            {score, crop});
    }



    std::sort(
        scoredCrops.begin(),
        scoredCrops.end(),
        [](const auto& first,
           const auto& second)
        {
            return first.first > second.first;
        });



    std::vector<Entities::Crop> result;


    for(const auto& item : scoredCrops)
    {
        result.push_back(item.second);
    }


    return result;
}


}
}