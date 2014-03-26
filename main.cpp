#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Polygon.h"
#include <QVector>
#include <time.h>

int main(int argc, char *argv[])
{
    std::vector<Point> ps;

    ps.push_back(Point(0, 0));
    ps.push_back(Point(20, 20));
    ps.push_back(Point(20, 100));
    ps.push_back(Point(0, 80));
    ps.push_back(Point(10, 100));
    ps.push_back(Point(10, 40));
    ps.push_back(Point(50, 60));
    ps.push_back(Point(30, 90));
    ps.push_back(Point(30, 20));
    ps.push_back(Point(70, 60));
    ps.push_back(Point(70, 70));
    ps.push_back(Point(0, 70));

    Polygon f(ps);
    std::vector< std::vector<Point> > facets = f.getFacets();

    //Qt graphics part
    QApplication a(argc, argv);
    srand(time(0));

    QGraphicsScene scene(QRect(-10, -10, 400, 400));
    scene.setBackgroundBrush(Qt::white);

    QVector<QPointF> ff;
    for(int i = 0; i < facets.size(); i++)
    {
        ff.clear();
        ff.reserve(facets[i].size());
        for(int j = 0; j < facets[i].size(); j++)
        {
            ff << QPointF(facets[i][j].getX() * 2, facets[i][j].getY() * 2);
        }
        scene.addPolygon(QPolygonF(ff), QPen(QBrush(Qt::black), 2), QColor(rand()%256, rand()%256, rand()%256));
    }

    ff.clear();
    for(int i = 0; i < ps.size(); i++)
    {
        ff << QPointF(ps[i].getX()+200, ps[i].getY());
    }
    scene.addPolygon(QPolygonF(ff), QPen(Qt::yellow), Qt::red);

    QGraphicsView view;
    view.setScene(&scene);
    view.show();

    return a.exec();
}
