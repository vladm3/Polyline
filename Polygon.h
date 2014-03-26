#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "Point.h"

class Polygon
{
private:
	std::vector<Point> initVertices;
	std::vector< std::vector<int> > graph;
	std::vector<Point> vertices;
	std::vector< std::vector<int> > facets;

	void buildGraph();
	int getVertexId(const Point &p);
	void findFacets();

public:
	Polygon(const std::vector<Point> &vertices);

	std::vector< std::vector<Point> > getFacets() const;
	std::vector<Point> getVertices() const;
};

#endif