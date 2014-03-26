#include "Line.h"

Line::Line(void)
{
	start = end = Point();
}

Line::Line(const Point &s, const Point &e)
{
	if(s.getX() < e.getX())
	{
		start = s;
		end = e;
	}
	else
	{
		end = s;
		start = e;
	}
}

Line::Line(const Line &l)
{
	start = l.start;
	end = l.end;
}

Line &Line::operator=(const Line &l)
{
	if(this == &l)
	{
		return *this;
	}

	start = l.start;
	end = l.end;

	return *this;
}

bool Line::operator==(const Line &l) const
{
	return start == l.start && end == l.end;
}

Point Line::getStart() const
{
	return start;
}

Point Line::getEnd() const
{
	return end;
}

bool Line::hasInnerPoint(const Point &p) const
{
	if(start.getY() < end.getY())
		return p.getX() >= start.getX() && p.getX() <= end.getX() && p.getY() >= start.getY() && p.getY() <= end.getY();
	else
		return p.getX() >= start.getX() && p.getX() <= end.getX() && p.getY() <= start.getY() && p.getY() >= end.getY();
}

bool Line::intersectsWith(const Line &l, Point &p) const
{
	auto det = [](double a, double b, double c, double d) -> double
	{
		return a * d - b * c;
	};

	auto getParams = [](const Line &l, double &a, double &b, double &c)
	{
		a = l.end.getY() - l.start.getY();
		b = -l.end.getX() + l.start.getX(); 
		c = l.start.getY() * l.end.getX() - l.end.getY() * l.start.getX();
	};

	double a1, b1, c1;
	double a2, b2, c2;

	getParams(*this, a1, b1, c1);
	getParams(l, a2, b2, c2);

	if(a1/c1 == a2/c2)
		return false;

	double zn = det(a1, b1, a2, b2);

	p.setX(-det(c1, b1, c2, b2) / zn);
	p.setY(-det(a1, c1, a2, c2) / zn);

	if(this->hasInnerPoint(p) && l.hasInnerPoint(p))
		return true;

	return false;
}