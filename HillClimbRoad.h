/* Guards

Includes

class HillClimbRoad
   public
     MAX_PART_COUNT
     X_ROAD_START
     Y_ROAD_START
     DEFAULT_ROAD_LENGTH

     HillClimbRoad(winWidth, winHeight)
     move(x)
     getPartCoords()
     getPartCount()
     reset()
   private
       partCoords
       addPart(x, y)
       calculateNewPartX(prevPartX)
       double calculateNewPartY()
       void generatePartsAhead()
       deletePartsBehind()

Guards end */
