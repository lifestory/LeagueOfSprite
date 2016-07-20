#pragma once
#ifndef __WeaponBezier__
#define __WeaponBezier__

#include <iostream>

#include "cocos2d.h"
USING_NS_CC;


typedef struct _ccQuadBezierConfig {
	Point endPosition;
	Point controlPoint;
} ccQuadBezierConfig;

class WeaponBezier : public BezierBy
{
public:
	WeaponBezier();
	static WeaponBezier* create(float t, const ccQuadBezierConfig& c);
	bool initWithDuration(float t, const ccQuadBezierConfig& c);
	virtual void update(float time);

private:
	ccQuadBezierConfig _config;
};
#endif