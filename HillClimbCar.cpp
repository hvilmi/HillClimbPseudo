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
