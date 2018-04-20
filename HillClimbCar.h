#ifndef __HILLCLIMB_CAR_H__
#define __HILLCLIMB_CAR_H__

#include <vector>
#include <memory>

#include "HillClimbRoad.h"
#include "HillClimbCarWheel.h"

namespace hillclimb {
    
    class HillClimbCar {
    public:
        HillClimbCar(double x, double y, double scale);
        
        void update(HillClimbRoad road, double dt);
        void updateThrottle(double dthrottle);
        double getPositionY() const;
        double getTransitionX(double dt) const;
        double getAngle() const;
        bool touchesRoad() const;
        void reset(double y);
    private:
        double X_POS;
        double SCALE;
        double y;
        //velocity
        double v_x;
        double v_y;
        //acceleration
        double a_x;
        double a_y;
        
        double angle;
        double v_ang;
        double a_ang;
        double throttle;
        
        // These are separate wheel classes instantiated
        std::shared_ptr<CarWheel> leftWheel;
        std::shared_ptr<CarWheel> rightWheel;
        
        std::vector<RoadPartTouching> roadPartsTouching; //Placeholder
        
        void updatePosY(double dt);
        void updateVelocityY(double dt);
        void updateVelocityX(double dt);
        void updateAccelerations(double dt);
        void updateAngle(double dt);
        void updateAngularVelocity(double dt);
        void updateAngularAcceleration(double dt);
        void updateRoadPartsTouching();
        void updateWheels(HillClimbRoad road);
    };
}

/* Guards

includes 

namespace

    class HillClimbCar
      public
        HillClimbCar(x, y, scale)
        update(road, dt)
        updateThrottle(dthrottle)
        getPositionY()
        getTransitionX(dt)
        getAngle()
        touchesRoad()
        reset(y)
      private
        X_POS
        SCALE
        y
        v_x
        v_y
        a_x
        a_y
        angle
        v_ang
        a_ang
        throttle
        leftWheel
        rightWheel
        roadPartsTouching
    
        updatePosY(dt)
        updateVelocityY(dt)
        updateVelocityX(dt)
        updateAccelerations(dt)
        updateAngle(dt)
        updateAngularVelocity(dt)
        updateAngularAcceleration(dt)
        updateRoadPartsTouching()
        updateWheels(road)

Guards end
*/
#endif