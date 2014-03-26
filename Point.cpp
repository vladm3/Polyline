#include "Point.h"
#include <cmath>

Point::Point(double ax, double ay)
{
	x = ax;
	y = ay;
}

Point::Point(const Point &p)
{
	x = p.x;
	y = p.y;
}

Point &Point::operator=(const Point &p)
{
	if(this == &p)
	{
		return *this;
	}

	x = p.x;
	y = p.y;

	return *this;
}

bool Point::operator==(const Point &p) const
{
	double EPS = 1e-10;
	return (abs(x - p.x) < EPS) && (abs(y - p.y) < EPS);
}

bool Point::operator<(const Point &p) const
{
	double EPS = 1e-10;
	return x < p.x - EPS || abs(x - p.x) < EPS && y < p.y - EPS;
}

double Point::getX() const
{
	return x;
}

double Point::getY() const
{
	return y;
}

void Point::setX(double ax)
{
	x = ax;
}

void Point::setY(double ay)
{
	y = ay;
}