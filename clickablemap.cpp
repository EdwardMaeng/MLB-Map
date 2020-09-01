#include "clickablemap.h"
#include "mainwindow.h"

/**************************************************************
* clickableMap(QWidget *parent) : QGraphicsView(parent)
* ____________________________________________________________
* Constructor
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* parent (QWidget) //IN -- the parent Qwidget
* POST-CONDITIONS
* -clickableMap created
***************************************************************/
clickableMap::clickableMap(QWidget *parent) : QGraphicsView(parent)
{



}

/**************************************************************
* mousePressEvent(QMouseEvent *event)
* ____________________________________________________________
* This method sets the x coordinates and y coordinates on the map
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* event (QMouseEvent) //IN -- the position on the map
* POST-CONDITIONS
* -the coordinates are set
***************************************************************/
void clickableMap::mousePressEvent(QMouseEvent *event)
{
    QPointF pt = mapToScene(event->pos());
    xCoords.push_back(pt.x());
    yCoords.push_back(pt.y());
}

/**************************************************************
* clearVectors()
* ____________________________________________________________
* This method empties the vectors of x and y coordinates
* ___________________________________________________________
* PRE-CONDITIONS
* none
* POST-CONDITIONS
* -the vectors are clear
***************************************************************/
void clickableMap::clearVectors()
{
    xCoords.clear();
    yCoords.clear();
}
