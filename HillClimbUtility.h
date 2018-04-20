#ifndef __HILLCLIMB_UTILITY_H__
#define __HILLCLIMB_UTILITY_H__

#include "cocos2d.h"

namespace hillclimb {

    extern const cocos2d::Size DESIGN_RESOLUTION_SIZE;
    extern const cocos2d::Size SMALL_RESOLUTION_SIZE;
    extern const cocos2d::Size MEDIUM_RESOLUTION_SIZE;
    extern const cocos2d::Size LARGE_RESOLUTION_SIZE;

    extern const double RIGHT_ANGLE;
    extern const double STRAIGHT_ANGLE;
    extern const double FULL_CIRCLE;

    struct Coordinates {
        double x;
        double y;
    };

    double calculateSlope(const Coordinates p1, const Coordinates p2);
    double calculateAngleFromComponents(const double x, const double y);
    double calculateNormalAngleFromSlope(const double slope);
    double calculateProjection(const double vectorLength, const double vectorAngle, const double lineAngle);
    double calculateHypotenuse(const double a, const double b);
    double calculateDistanceBetweenPoints(const double x1, const double y1, const double x2, const double y2);
    double calculateDistanceToLine(const double pointX, const double pointY, const double slope, const double c);
    double calculateAngleDiff(const double angle1, const double angle2);
    double calculateDistanceToLineSegment(const double x, const double y,
                                          const Coordinates beginSegment, const Coordinates endSegment);
}
    
#endif
