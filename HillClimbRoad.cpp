#include "HillClimbRoad.h"
#include "HillClimbUtility.h"
#include <random>
#include <iostream>

namespace hillclimb {

   const double ROAD_LENGHT_FACTOR = 400;//Should change later

   HillClimbRoad::HillClimbRoad(double winWidth, double winHeight) 
                        : Y_ROAD_START(winHeight/2), X_ROAD_START(0) {
       this->addPart(0, winHeight/2);
       generatePartsAhead();
   
   }

   int HillClimbRoad::getPartCount() const {
       std::cout << "Part count: " << static_cast<int>(partCoords.size()) << std::endl; 
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
       std::cout << "Part added with coords " << x << " " << y << std::endl;
   
   }

   double HillClimbRoad::calculateNewPartX(double prevPartX) {

       double randomPercent = 1.5 - (static_cast<double>(std::rand()) / RAND_MAX);
       
       return prevPartX + ROAD_LENGHT_FACTOR * randomPercent;
   }


   double HillClimbRoad::calculateNewPartY() {
       //This should raise almost constantly. Now it fluctuates around middle of the screen.
       double randomPercent = 1.5 - (static_cast<double>(std::rand()) / RAND_MAX);
       std::cout << "Random number: " << randomPercent << std::endl;
       
       return this->Y_ROAD_START * randomPercent;
   }

   void HillClimbRoad::generatePartsAhead() {
       if (getPartCount() < MAX_PART_COUNT) {
           std::cout << "Generating new parts" << std::endl;
           for (int i=getPartCount();i < MAX_PART_COUNT; i++) {
               Coordinates prevCoord = partCoords[i-1];
               double newX = calculateNewPartX(prevCoord.x);
               double newY = calculateNewPartY();
               addPart(newX, newY);
           }
       }
       std::cout << "No new parts needed" << std::endl;
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