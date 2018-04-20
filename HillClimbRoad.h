#ifndef __HILLCLIMB_ROAD_H__
#define __HILLCLIMB_ROAD_H__

#include <vector>

#include "HillClimbUtility.h"


namespace hillclimb {


    class HillClimbRoad {
    public:
        int MAX_PART_COUNT = 5;
        double X_ROAD_START = 0;
        double Y_ROAD_START;
        double DEFAULT_ROAD_LENGTH = 5;

        HillClimbRoad(double winWidth, double winHeight);
        
        void move(double x);
        std::vector<Coordinates> getPartCoords();
        int getPartCount() const;
        void reset();
    private:
        std::vector<Coordinates> partCoords;
        void addPart(double x, double y);
        double calculateNewPartX(double prevPartX);
        double calculateNewPartY(); //Should have double prevPartY as parameter?
        void generatePartsAhead();
        void deletePartsBehind();
    };
}

#endif