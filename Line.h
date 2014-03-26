#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line
{
private:
	Point start;
	Point end;

	bool hasInnerPoint(const Point &p) const;
public:
	Line(void);
	Line(const Point &start, const Point &end);
	Line(const Line &l);

	Line &operator=(const Line &l);
	bool operator==(const Line &l) const;

	Point getStart() const;
	Point getEnd() const;
	bool intersectsWith(const Line &l, Point &p) const;
};

#endif