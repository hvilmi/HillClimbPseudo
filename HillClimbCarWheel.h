#ifndef __HILLCLIMB_WHEEL_H__
#define __HILLCLIMB_WHEEL_H__

#include "HillClimbUtility.h"
#include "HillClimbRoad.h"

#include <vector>


namespace hillclimb {
    
    struct RoadPartTouching {
        double wheelSubmersion;// how much wheel has submerged beneath the surface of the road
        double slope;
    };
    
    class CarWheel {
    public:
        //x_offset = -57.0 | 58
        //y_offset = -43
        //radius = 18
        CarWheel(double x_offset, double y_offset, double radius);
        
        double getForceX() const;
        double getForceY() const;
        std::vector<RoadPartTouching> getRoadPartsTouching() const;
        void updateState(int throttle, Coordinates carPos, double carAngle, HillClimbRoad road);
        void clearPreviousState();
    private:
        double OFFSET;
        double OFFSET_ANGLE;
        double RADIUS;
        double x;
        double y;
        double force_x;
        double force_y;
        std::vector<RoadPartTouching> roadPartsTouching;
    
        bool touchesRoad();
        void updatePosX(double carX, double carAngle);
        void updatePosY(double carY, double carAngle);
        void updateRoadPartsTouching(HillClimbRoad road);
        void updateForces(double throttle);
    };
}


/* Guards
  
Includes

Namespace

    struct RoadPartTouching
        wheelSubmersion (how much wheel has submerged beneath the surface of the road)
        slope

    class CarWheel
      public
        CarWheel(x_offset, y_offset, radius)
        getForceX()
        getForceY()
        getRoadPartsTouching()
        updateState(throttle, carPos, carAngle, road)
        clearPreviousState()
      private:
        OFFSET
        OFFSET_ANGLE
        RADIUS
        x
        y
        force_x
        force_y
        roadPartsTouching
    
        touchesRoad()
        updatePosX(carX, carAngle)
        updatePosY(carY, carAngle)
        updateRoadPartsTouching(road)
        void updateForces(throttle)

Guards end
*/

#endif