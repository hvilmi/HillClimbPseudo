#include "HillClimbRoad.h"
#include "HillClimbUtility.h"

namespace hillclimb {

   const double ROAD_LENGHT_FACTOR = 5;//Should change later

   HillClimbRoad::HillClimbRoad(double winWidth, double winHeight) {
       this->addPart(0, winHeight/2);
       this->addPart(winWidth/4, winHeight/2 + 200);
   
   }

   int HillClimbRoad::getPartCount() const {
       return static_cast<int>(partCoords.size());
   }

   std::vector<Coordinates> HillClimbRoad::getPartCoords() {
       return partCoords;
   }

   void HillClimbRoad::addPart(double x, double y) {
       Coordinates partCoord = {
           .x = x,
           .y = y
       };
       partCoords.push_back(partCoord);
   
   }

   double HillClimbRoad::calculateNewPartX(double prevPartX) {
       //randomize length of the new part using some factor
       double i = 0;
       return i;
   }


   double HillClimbRoad::calculateNewPartY() {
       //randomize y position of the end point of the new part
       return 0;
   }

   void HillClimbRoad::generatePartsAhead() {
      //generate parts as many as MAX_PART_COUNT - currentPartCount
   }

   void HillClimbRoad::deletePartsBehind() {
       
   }

   void HillClimbRoad::move(double x) {
       //move the x's of parts
       //deletePartsBehind
       //generatePartsAhead
   }

   void HillClimbRoad::reset() {
       //clear partCoords
       //add two horizontal parts
       //generatePartsAhead
   }

}