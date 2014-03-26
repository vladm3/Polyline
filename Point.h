#ifndef POINT_H
#define POINT_H

class Point
{
private:
	double x;
	double y;
public:
	Point(double x = 0, double y = 0);
	Point(const Point &p);
	Point &operator=(const Point &p);
	bool operator==(const Point &p) const;
	bool operator<(const Point &p) const;

	double getX() const;
	double getY() const;

	void setX(double x);
	void setY(double y);
};

#endif