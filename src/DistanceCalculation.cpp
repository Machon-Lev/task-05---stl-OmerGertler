#include "DistanceCalculation.h"
#include <cmath>

void DistanceCalculation::setDistanceFunction(int normChoice)
{
    if (normChoice >= 0 && normChoice < _normFunctions.size())
    {
        _distanceFunction = _normFunctions[normChoice];
    }
    else
    {
        // Default behavior or error handling if normChoice is invalid
        _distanceFunction = nullptr;  // You can modify this based on your requirements
    }
}

double DistanceCalculation::calculateDistance(const Location& loc1, const Location& loc2)
{
    if (_distanceFunction)
    {
        return _distanceFunction(loc1, loc2);
    }
    else
    {
        // Default behavior or error handling if no distance function is set
        return 0.0;  // You can modify this based on your requirements
    }
}

// Euclidean distance (2l norm)
double DistanceCalculation::euclideanDistance(const Location& loc1, const Location& loc2)
{
    int dx = loc2.getCol() - loc1.getCol();
    int dy = loc2.getRow() - loc1.getRow();
    return std::sqrt(dx * dx + dy * dy);
}

// INFl norm (Chebyshev distance)
double DistanceCalculation::chebyshevDistance(const Location& loc1, const Location& loc2)
{
    int dx = std::abs(loc2.getCol() - loc1.getCol());
    int dy = std::abs(loc2.getRow() - loc1.getRow());
    return std::max(dx, dy);
}

// 1l norm (Manhattan distance)
double DistanceCalculation::manhattanDistance(const Location& loc1, const Location& loc2)
{
    int dx = std::abs(loc2.getCol() - loc1.getCol());
    int dy = std::abs(loc2.getRow() - loc1.getRow());
    return dx + dy;
}
