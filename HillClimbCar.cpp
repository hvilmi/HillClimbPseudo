#include <vector>
#include <cmath>
#include <iostream>

#include "HillClimbCar.h"
#include "HillClimbCarWheel.h"
#include "HillClimbUtility.h"

namespace hillclimb {
    
    HillClimbCar::HillClimbCar(double x, double y, double scale) {
        this->leftWheel = std::make_shared<CarWheel>(-scale, -scale, 5.0);
        this->leftWheel = std::make_shared<CarWheel>(-scale, -scale, 5.0);
    
    }
    
    void HillClimbCar::update(HillClimbRoad road, double dt) {
        /*
        update road parts touching
        update wheels
        update angular acceleration
        update angular velocity
        update angle
        update accelerations
        update velocity x
        update velocity y
        update pos y
        */
        this->updateRoadPartsTouching();
        this->updateWheels(road);
        this->updateAngularVelocity(dt);
        this->updateAngle(dt);
        this->updateAccelerations(dt);
        this->updateVelocityX(dt);
        this->updateVelocityY(dt);
        this->updatePosY(dt);
    }
    
    void HillClimbCar::updateThrottle(double dthrottle) {
        std::cout << "Throttle " << throttle << std::endl;
        this->throttle += dthrottle;
        
    }
        
    double HillClimbCar::getPositionY() const {
        return this->y;
    }
        
    double HillClimbCar::getTransitionX(double dt) const {
        std::cout << "X Transition: " << this->v_x * dt << std::endl;
        return this->v_x * dt;
    }
        
    double HillClimbCar::getAngle() const {
        return this->angle;
    }
        
    bool HillClimbCar::touchesRoad() const {
        if (this->roadPartsTouching.size() > 0) {
            return true;
        }
        else {
            return false;
        }
    }
        
    void HillClimbCar::reset(double y) {
        this->y = y;
        this->X_POS = 0;
        //Rest of the variable need to be reset also.
    }

    void HillClimbCar::updateVelocityX(double dt) {
        
        
        this->v_x += this->a_x * dt;
        
    }

    void HillClimbCar::updatePosY(double dt) {
        this->y = this->v_y * dt;
        
    }

    void HillClimbCar::updateVelocityY(double dt) {
        this->v_y += this->a_y * dt;
        
    }

    void HillClimbCar::updateAngle(double dt) {
        this->angle += this->v_ang * dt;
    }

    void HillClimbCar::updateAngularVelocity(double dt) {
        this->v_ang += this->a_ang * dt;
        
    }

    void HillClimbCar::updateAngularAcceleration(double dt) {
        //Very crude algorithm for the angular acceleration of the car.
        //You can use this or come up with something better.

        const double PARALLEL_WITH_ROAD = 0.02;
        const double ALMOST_PARALLEL_WITH_ROAD = 0.05;
        const double DIFF_FACTOR = 200;
        const double ANGULAR_ACCELERATION = 3.0;
        const double STEEP_SLOPE = RIGHT_ANGLE / 4;

        double slope;
        double slopeAngle;
        double angleDiff;
        double angleDiffAbs;

        for (auto roadPart: this->roadPartsTouching) {
            slope = roadPart.slope;
            slopeAngle = atan(slope);
            angleDiff = calculateAngleDiff(slopeAngle, -this->angle);
            angleDiffAbs = std::abs(angleDiff);

            if (angleDiffAbs <= PARALLEL_WITH_ROAD) {
                this->a_ang = -this->v_ang / dt;
            } else if (angleDiffAbs <= ALMOST_PARALLEL_WITH_ROAD) {
                this->a_ang = -this->v_ang / dt - angleDiff * DIFF_FACTOR;
            } else if (angleDiffAbs <= RIGHT_ANGLE / 2 || slope < -STEEP_SLOPE || slope > STEEP_SLOPE) {
                this->a_ang = -angleDiff * ANGULAR_ACCELERATION;
            }
        }

    }

    void HillClimbCar::updateRoadPartsTouching() {
        
        this->roadPartsTouching.empty();
        std::vector<RoadPartTouching> leftWheelRoadParts = this->leftWheel->getRoadPartsTouching();
        this->roadPartsTouching.insert(this->roadPartsTouching.end(), leftWheelRoadParts.begin(), leftWheelRoadParts.end());
        
        std::vector<RoadPartTouching> rightWheelRoadParts = this->rightWheel->getRoadPartsTouching();
        this->roadPartsTouching.insert(this->roadPartsTouching.end(), rightWheelRoadParts.begin(), leftWheelRoadParts.end());
        
        //clear roadPartsTouching
        //combine roadPaRoad partrtsTouching of leftWheel and rightWheel into roadPartsTouching of car
    }

    void HillClimbCar::updateWheels(HillClimbRoad road) {
        //clear previous state of wheels
        //update state of wheels
    }

    void HillClimbCar::updateAccelerations(double dt) {
        //An algorithm for updating the horizontal and vertical acceleration of the car. Lots of physics and math.
        //You can use this or come up with something better.

        const double GRAVITY = 200.0;

        double slope;
        double normalAngle;
        double projectionForce;
        double projectionVelocity;
        double supportForce;

        double residualForce;
        double residualVelocity;
        double residualForceAngle;
        double residualVelocityAngle;

        double residualVelocityX = this->v_x;
        double residualVelocityY = this->v_y;
        double residualForceX = this->leftWheel->getForceX() + this->rightWheel->getForceX();
        double residualForceY = this->leftWheel->getForceY() + this->rightWheel->getForceY() - GRAVITY;

        for (auto roadPart: this->roadPartsTouching) {
            slope = roadPart.slope;
            normalAngle = calculateNormalAngleFromSlope(slope);
            residualForce = calculateHypotenuse(residualForceX, residualForceY);
            residualVelocity = calculateHypotenuse(residualVelocityX, residualVelocityY);
            residualForceAngle = calculateAngleFromComponents(residualForceX, residualForceY);
            residualVelocityAngle  = calculateAngleFromComponents(residualVelocityX, residualVelocityY);
            projectionForce = calculateProjection(residualForce, residualForceAngle, normalAngle);
            projectionVelocity = calculateProjection(residualVelocity, residualVelocityAngle, normalAngle);
            if (projectionVelocity + projectionForce * dt > 0) {
                supportForce = projectionVelocity / dt + projectionForce;
                residualForceX -= supportForce * cos(normalAngle);
                residualForceY -= supportForce * sin(normalAngle);
                residualVelocityX += residualForceX * dt;
                residualVelocityY += residualForceY * dt;
            }
        }
        this->a_x = residualForceX;
        this->a_y = residualForceY;
    }


/*
    update(road, dt) {
        update road parts touching
        update wheels
        update angular acceleration
        update angular velocity
        update angle
        update accelerations
        update velocity x
        update velocity y
        update pos y
    }
 */

   /*
   reset {
        fundamental type fields back to their original values
        clear previous state of wheels
   }
   */
    
}


/*

Includes

namespace

    HillClimbCar constructor

    function updateVelocityX

    function updatePosY

    function updateVelocityY

    function updateAngle

    function updateAngularVelocity

    function updateAngularAcceleration(dt) {
        Very crude algorithm for the angular acceleration of the car.
        You can use this or come up with something better.

        const double PARALLEL_WITH_ROAD = 0.02;
        const double ALMOST_PARALLEL_WITH_ROAD = 0.05;
        const double DIFF_FACTOR = 200;
        const double ANGULAR_ACCELERATION = 3.0;
        const double STEEP_SLOPE = RIGHT_ANGLE / 4;

        double slope;
        double slopeAngle;
        double angleDiff;
        double angleDiffAbs;

        for (auto roadPart: this->roadPartsTouching) {
            slope = roadPart.slope;
            slopeAngle = atan(slope);
            angleDiff = calculateAngleDiff(slopeAngle, -this->angle);
            angleDiffAbs = std::abs(angleDiff);

            if (angleDiffAbs <= PARALLEL_WITH_ROAD) {
                this->a_ang = -this->v_ang / dt;
            } else if (angleDiffAbs <= ALMOST_PARALLEL_WITH_ROAD) {
                this->a_ang = -this->v_ang / dt - angleDiff * DIFF_FACTOR;
            } else if (angleDiffAbs <= RIGHT_ANGLE / 2 || slope < -STEEP_SLOPE || slope > STEEP_SLOPE) {
                this->a_ang = -angleDiff * ANGULAR_ACCELERATION;
            }
        }

    }

    function updateRoadPartsTouching {
        clear roadPartsTouching
        combine roadPartsTouching of leftWheel and rightWheel into roadPartsTouching of car
    }

    function updateWheels {
        clear previous state of wheels
        update state of wheels
    }

    updateAccelerations(double dt) {
        An algorithm for updating the horizontal and vertical acceleration of the car. Lots of physics and math.
        You can use this or come up with something better.

        const double GRAVITY = 200.0;

        double slope;
        double normalAngle;
        double projectionForce;
        double projectionVelocity;
        double supportForce;

        double residualForce;
        double residualVelocity;
        double residualForceAngle;
        double residualVelocityAngle;

        double residualVelocityX = this->v_x;
        double residualVelocityY = this->v_y;
        double residualForceX = this->leftWheel->getForceX() + this->rightWheel->getForceX();
        double residualForceY = this->leftWheel->getForceY() + this->rightWheel->getForceY() - GRAVITY;

        for (auto roadPart: this->roadPartsTouching) {
            slope = roadPart.slope;
            normalAngle = calculateNormalAngleFromSlope(slope);
            residualForce = calculateHypotenuse(residualForceX, residualForceY);
            residualVelocity = calculateHypotenuse(residualVelocityX, residualVelocityY);
            residualForceAngle = calculateAngleFromComponents(residualForceX, residualForceY);
            residualVelocityAngle  = calculateAngleFromComponents(residualVelocityX, residualVelocityY);
            projectionForce = calculateProjection(residualForce, residualForceAngle, normalAngle);
            projectionVelocity = calculateProjection(residualVelocity, residualVelocityAngle, normalAngle);
            if (projectionVelocity + projectionForce * dt > 0) {
                supportForce = projectionVelocity / dt + projectionForce;
                residualForceX -= supportForce * cos(normalAngle);
                residualForceY -= supportForce * sin(normalAngle);
                residualVelocityX += residualForceX * dt;
                residualVelocityY += residualForceY * dt;
            }
        }
        this->a_x = residualForceX;
        this->a_y = residualForceY;
    }

    function updateThrottle

    function getTransitionX

    function getPositionY

    function getAngle

    function touchesRoad

    update(road, dt) {
        update road parts touching
        update wheels
        update angular acceleration
        update angular velocity
        update angle
        update accelerations
        update velocity x
        update velocity y
        update pos y
   }

   reset {
        fundamental type fields back to their original values
        clear previous state of wheels
   }
*/
