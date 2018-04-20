
#include <cmath>
#include <vector>

#include "HillClimbCarWheel.h"
#include "HillClimbUtility.h"

namespace hillclimb {
        CarWheel::CarWheel(double x_offset, double y_offset, double radius) {
            
        }
        
        double CarWheel::getForceX() const {
            return this->force_x;
        }
        
        double CarWheel::getForceY() const {
            return this->force_y;
        }
        
        std::vector<RoadPartTouching> CarWheel::getRoadPartsTouching() const {
            return this->roadPartsTouching;
        }
        
        void CarWheel::updateState(int throttle, Coordinates carPos, double carAngle, HillClimbRoad road) {
            
        }
        
        void CarWheel::clearPreviousState() {
            
        }


   void CarWheel::updateForces(double throttle) {
      const double WHEEL_FRICTION = 1;//This should be edited and perhaps moved. 
      
      if (this->roadPartsTouching.size() > 0) {
          throttle = throttle / roadPartsTouching.size();
      }


      for (auto roadPart : this->roadPartsTouching) {
          double friction;
          if (roadPart.slope >= 0) {
              friction = WHEEL_FRICTION * (roadPart.slope + 1);
          }
          else {
              friction = WHEEL_FRICTION / (std::abs(roadPart.slope) + 1);
          }
          double resThrottle = throttle - friction;
          this->force_x += std::cos(calculateNormalAngleFromSlope(roadPart.slope)) * resThrottle;
          this->force_y += std::sin(calculateNormalAngleFromSlope(roadPart.slope)) * resThrottle;
      }

   }

   void CarWheel::updateRoadPartsTouching(HillClimbRoad road) {
       std::vector<Coordinates> roadCoords = road.getPartCoords();
       
       for (int i = 0; i < road.getPartCount() - 1; i++) {
           Coordinates leftCoord = roadCoords[i];
           Coordinates rightCoord = roadCoords[i+1];
           
           double distance = calculateDistanceToLineSegment(this->x, this->y, leftCoord, rightCoord);
           if (distance < this->RADIUS) {
               RoadPartTouching roadPart {
                   this->RADIUS - distance, //wheelSubmersion
                   calculateSlope(leftCoord, rightCoord) //slope
               };
               this->roadPartsTouching.push_back(roadPart);

           }
       }

   }
}

/* Includes

namespace

   CarWheel constructor

   function getForceX

   function getForceY

   function getRoadPartsTouching

   function updatePosX

   function updatePosY

   function touchesRoad

   function clearPreviousState

   function updateForces(throttle) {
      if count of road parts touching > 0
          divide throttle by count of road parts touching

      loop through road parts touching
          get slope and slopeAngle
          if slope >= 0
              friction = SOME_FRICTION_CONST * (slope + 1)
          else
              friction = SOME_FRICTION_CONST / (abs(slope) + 1)
          resThrottle = throttle - friction
          increment force_x with cos(slopeAngle) * resThrottle
          increment force_y with sin(slopeAngle) * resThrottle
   }

   function updateRoadPartsTouching {
        use calculateDistanceToLineSegment for each road part on the road
        check if they are closer than RADIUS
        if they are calculateSlope and wheelSubmersion (RADIUS - distance) and generate RoadPartTouching
   }

   function updateState
*/
