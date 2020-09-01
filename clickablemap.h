#ifndef CLICKABLEMAP_H
#define CLICKABLEMAP_H

/******************************************************************************
 *  AUTHOR         : Jousha McDermott, Seongkyoo Maeng, Chak Hei Tin
 *  Project #2     : I Love Baseball
 *  CLASS          : CS 008
 *  DUE DATE       : 06/02/2020
 ******************************************************************************/

#include <QtWidgets>
#include <vector>

/****************************************************
 * class clickableMap
 * - This class is used to set x coordinates and
 * y coordinates on the map so when users click on
 * the map, the coordinates will be set.
 ****************************************************/
class clickableMap :public QGraphicsView
{
public:

    //CONSTRUCTOR
    clickableMap(QWidget *parent =0);

    //MEMBER VARAIBLES
    std::vector<int> xCoords;
    std::vector<int> yCoords;
protected:
    //MUTATOR
    void mousePressEvent(QMouseEvent *event);

    // QGraphicsItem interface
public:

    //MUTATOR
    void clearVectors();

};

/*******************************************
 * clickableMap(QWidget *parent =0);
 * Constructor: Constructs clickableMap object
 * Parameters : parent (QWidget)
 * Return     : none
 ******************************************/

/*******************************************
 * mousePressEvent(QMouseEvent *event);
 * mutator: set the x coordinates and y coordinates
 *          by clicking on the map
 * Parameters : event (QMouseEvent) //IN - position on tha map
 * Return     : none
 ******************************************/

/*******************************************
 * clearVectors();
 * mutator: clear the vectors of x coordinates and y coordinates
 * Parameters : none
 * Return     : none
 ******************************************/

#endif // CLICKABLEMAP_H
