#include "Polygon.h"
#include "Line.h"
#include <algorithm>

Polygon::Polygon(const std::vector<Point> &vert)
{
	initVertices = vert;
	buildGraph();
	findFacets();
}

int Polygon::getVertexId(const Point &p)
{
	std::vector<Point>::iterator it = std::find(vertices.begin(), vertices.end(), p);
	int res = 0;

	if(it == vertices.end())
	{
		res = vertices.size();
		vertices.push_back(p);
		graph.resize(graph.size() + 1);
	}
	else
	{
		res = it - vertices.begin();
	}

	return res;
}

void Polygon::buildGraph()
{
	std::vector<Line> edges;
	edges.reserve(initVertices.size());
	vertices = initVertices;
	graph.resize(initVertices.size());

	for(int i = 0; i < initVertices.size() - 1; i++)
	{
		edges.push_back(Line(initVertices[i], initVertices[i+1]));
	}
	edges.push_back(Line(initVertices[initVertices.size()-1], initVertices[0]));

	for(int i = 0; i < edges.size(); i++)
	{
		std::vector<Point> cur;
		for(int j = 0; j < edges.size(); j++)
		{
			if(abs(i - j) == 1 || abs(i - j) == (edges.size()-1))
			{
				continue;
			}

			if(i == j)
			{
				cur.push_back(edges[i].getStart());
				cur.push_back(edges[i].getEnd());
				continue;
			}

			Point intPoint;
			if(edges[i].intersectsWith(edges[j], intPoint))
			{
				cur.push_back(intPoint);
			}
		}

		std::sort(cur.begin(), cur.end());

		for(int j = 0; j < cur.size() - 1; j++)
		{
			int x = getVertexId(cur[j]);
			int y = getVertexId(cur[j+1]);

			if(x != y)
			{
				graph[x].push_back(y);
				graph[y].push_back(x);
			}
		}
	}

	for(int i = 0; i < graph.size(); i++)
	{
		std::sort(graph[i].begin(), graph[i].end(), [this, i](int a, int b)
			{
				return atan2(vertices[a].getY() - vertices[i].getY(),
					   vertices[i].getX() - vertices[a].getX()) >
					   atan2(vertices[b].getY() - vertices[i].getY(),
					   vertices[i].getX() - vertices[b].getX());
			}
		);

		graph[i].erase(std::unique(graph[i].begin(), graph[i].end()), graph[i].end());
	}
}

void Polygon::findFacets()
{
	int n = vertices.size();
	std::vector< std::vector<char> > used(n);

	for(int i = 0; i < n; i++)
	{
		used[i].resize(graph[i].size());
	}

	for(int i = 0; i < n; i++)
	{
		for(size_t j = 0; j < graph[i].size(); j++)
		{
			if(!used[i][j])
			{
				used[i][j] = true;
				int v = graph[i][j], pv = i;
				std::vector<int> facet;

				while(true)
				{
					facet.push_back(v);
					std::vector<int>::iterator it = std::find(graph[v].begin(), graph[v].end(), pv);

					if(++it == graph[v].end())
					{
						it = graph[v].begin();
					}

					if(used[v][it - graph[v].begin()])
					{
						break;
					}

					used[v][it - graph[v].begin()] = true;
					pv = v; v = *it;
				}

				facets.push_back(facet);
			}
		}
	}
}

std::vector< std::vector<Point> > Polygon::getFacets() const
{
	std::vector< std::vector<Point> > res(facets.size() - 1);
	for(int i = 1; i < facets.size(); i++)
	{
		res[i-1].reserve(facets[i].size());
		for(int j = 0; j < facets[i].size(); j++)
		{
			res[i-1].push_back(vertices[facets[i][j]]);
		}
	}

	return res;
}

std::vector<Point> Polygon::getVertices() const
{
	return vertices;
}