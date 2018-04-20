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
