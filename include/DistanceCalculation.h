#pragma once
#include"Location.h"
#include <vector>

class DistanceCalculation {
public:
    using NormFunction = double (*)(const Location&, const Location&);

    void setDistanceFunction(int normChoice);

    double calculateDistance(const Location& loc1, const Location& loc2);

private:
    NormFunction _distanceFunction = nullptr;

    // Vector of norm calculation functions
    std::vector<NormFunction> _normFunctions = {
        euclideanDistance,
        chebyshevDistance,
        manhattanDistance
    };

    // Euclidean distance (2l norm)
    static double euclideanDistance(const Location& loc1, const Location& loc2);

    // INFl norm (Chebyshev distance)
    static double chebyshevDistance(const Location& loc1, const Location& loc2);

    // 1l norm (Manhattan distance)
    static double manhattanDistance(const Location& loc1, const Location& loc2);

};
