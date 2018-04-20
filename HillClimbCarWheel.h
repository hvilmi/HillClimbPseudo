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
