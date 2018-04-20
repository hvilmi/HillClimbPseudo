#include <cmath>
#include <iostream>

#include "cocos2d.h"
#include "HillClimbUtility.h"

namespace hillclimb {
    
    const cocos2d::Size DESIGN_RESOLUTION_SIZE = cocos2d::Size(1920, 1080);
    const cocos2d::Size SMALL_RESOLUTION_SIZE = cocos2d::Size(480, 320);
    const cocos2d::Size MEDIUM_RESOLUTION_SIZE = cocos2d::Size(1024, 768);
    const cocos2d::Size LARGE_RESOLUTION_SIZE = cocos2d::Size(2048, 1536);

    const double RIGHT_ANGLE = M_PI / 2;
    const double STRAIGHT_ANGLE = M_PI;
    const double FULL_CIRCLE = M_PI * 2;

    double calculateSlope(const Coordinates p1, const Coordinates p2) {
        return (p2.y - p1.y) / (p2.x - p1.x);
    }

    double calculateAngleFromComponents(const double x, const double y) {
        if (x == 0 && y >= 0) {
            return RIGHT_ANGLE;
        } else if (x == 0 && y < 0) {
            return -RIGHT_ANGLE;
        } else if (y > 0 && x < 0) {
            return std::atan(y / x) + STRAIGHT_ANGLE;
        } else if (y <= 0 && x < 0) {
            return std::atan(y / x) - STRAIGHT_ANGLE;
        } else {
            return std::atan(y / x);
        }
    }

    double calculateNormalAngleFromSlope(const double slope) {
        return std::atan(slope) - RIGHT_ANGLE;
    }

    double calculateProjection(const double vectorLength, const double vectorAngle, const double lineAngle) {
        const double angleDiff = std::abs(vectorAngle - lineAngle);
        if (angleDiff <= RIGHT_ANGLE) {
            return std::cos(angleDiff) * vectorLength;
        } else if (angleDiff <= STRAIGHT_ANGLE) {
            return std::cos(angleDiff - RIGHT_ANGLE) * -vectorLength;
        } else {
            return std::cos(FULL_CIRCLE - angleDiff) * vectorLength;
        }
    }

    double calculateHypotenuse(const double a, const double b) {
        return std::sqrt(std::pow(a, 2) + std::pow(b, 2));
    }

    double calculateDistanceBetweenPoints(const double x1, const double y1, const double x2, const double y2) {
        return calculateHypotenuse(y2 - y1, x2 - x1);
    }

    double calculateDistanceToLine(const double x, const double y, const double slope, const double c) {
        return std::abs(-slope * x + y + c) / calculateHypotenuse(1, slope);
    }

    double calculateAngleDiff(const double angle1, const double angle2) {
        double angleDiff = angle1 - angle2;
        if (angleDiff > STRAIGHT_ANGLE) {
            angleDiff = -std::abs(FULL_CIRCLE - angleDiff);
        } else if (angleDiff < -STRAIGHT_ANGLE) {
            angleDiff = std::abs(-FULL_CIRCLE - angleDiff);
        }
        return angleDiff;
    }

    double calculateDistanceToLineSegment(const double x, const double y,
                                          const Coordinates beginSegment, const Coordinates endSegment) {
        const double lineX1 = beginSegment.x;
        const double lineY1 = beginSegment.y;
        const double lineX2 = endSegment.x;
        const double lineY2 = endSegment.y;
    
        const double slopeLine = calculateSlope(beginSegment, endSegment);
        const double normalAngle = calculateNormalAngleFromSlope(slopeLine);
        const double angleToSegmentBegin = calculateAngleFromComponents(lineX1 - x, lineY1 - y);
        const double angleToSegmentEnd = calculateAngleFromComponents(lineX2 - x, lineY2 - y);

        double angleDiffBegin = calculateAngleDiff(normalAngle, angleToSegmentBegin);
        double angleDiffEnd = calculateAngleDiff(normalAngle, angleToSegmentEnd);
    
        if ((angleDiffBegin > 0 && angleDiffEnd < 0) || (angleDiffBegin < 0 && angleDiffEnd > 0)) {
            const double c = -lineY1 + slopeLine * lineX1;
            return calculateDistanceToLine(x, y, slopeLine, c);
        } else if (abs(angleDiffBegin) < abs(angleDiffEnd)) {
            return calculateDistanceBetweenPoints(x, y, lineX1, lineY1);
        } else {
            return calculateDistanceBetweenPoints(x, y, lineX2, lineY2);
        }
    }
}
