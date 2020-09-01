#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/******************************************************************************
 *  AUTHOR         : Jousha McDermott, Seongkyoo Maeng, Chak Hei Tin
 *  Project #2     : I Love Baseball
 *  CLASS          : CS 008
 *  DUE DATE       : 06/02/2020
 ******************************************************************************/

#include "graph.h"
#include "stadium.h"
#include <QMainWindow>
#include <vector>
#include <QGraphicsScene>
#include "fan.h"
#include "product.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*******************************************
 * Class MainWindow
 * - This class represents the main window of the gui.
 *  it contains many interface related functions.
 ******************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //CONSTRUCTOR & DESTRUCTOR
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //MUTATORS
    void buildStadiumGraph();
    void drawEdges();
    void buildComboBoxes();
    void makeProposedFile();
    void readProposedFile();
    void drawProposed();
    void updateNextStop();
    void readSouvenirFile();
    void writeSouvenirFile();
    void readReceiptFile();
    void writeReceiptFile();
    void buildFanComboBox();
    void forceLogin();
    void buildSouvenirComboBox();
    void buildModifyValueComboBox();

    //ACCESSORS
    vector<Stadium> stadium_list( );
    vector<Stadium> major_league_list( );
    vector<Stadium> american_list( );
    vector<Stadium> national_list( );
    vector<Stadium> grass_list( );
    vector<Stadium> date_opened_list( );
    vector<Stadium> sort_by_stadium_name(vector<Stadium> stadiums);
    vector<Stadium> sort_by_team_name(vector<Stadium> stadiums);
    vector<Stadium> sort_by_date_opened(vector<Stadium> stadiums);
    string print(vector<Stadium> in);

private slots:

    void on_getInfoButton_clicked();
    void on_getDistanceButton_clicked();
    void on_addNewStadiumButton_clicked();
    void on_addLocationButton_clicked();
    void on_updateCoordinateButton_clicked();
    void on_startTripButton_clicked();
    void on_moveButton_clicked();
    void on_finishTripButton_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_buySouvenirButton_clicked();
    void on_souvenirModifyBox_currentIndexChanged(int index);
    void on_modifySouvenirButton_clicked();
    void on_removeSouvenirButton_clicked();
    void on_addSouvenirButton_clicked();
    void on_addFanButton_clicked();
    void on_souvenirReportButton_clicked();
    void on_commitModificationsButton_clicked();
    void on_modifyStadiumBox_currentIndexChanged(int index);
    void on_modifiedValueBox_currentIndexChanged(int index);
    void on_addLocationButtonModify_clicked();
    void on_updateCoordinateButtonModify_clicked();
    void on_removeStadiumButton_clicked();
    void on_distanceThroughAllButton_clicked();
    void on_getStadiumList_clicked();

private:
    Ui::MainWindow *ui;             //IN/OUT - pointer to ui
    vector<Stadium> plannedStadiums;//IN/OUT - planned stadium vector
    Graph<Stadium> graph;           //IN/OUT - the main graph
    vector<Stadium> stadiums;       //IN/OUT - plain stadium vector
    QGraphicsScene * scene;         //IN/OUT - scene for adding new stadiums
    QGraphicsScene * sceneForTrip;  //IN/OUT - scene for trip
    QGraphicsScene * generalScene;  //IN/OUT - general info scene
    int currentStadiumToModify;     //IN/OUT - Current stadium operating on
    bool modifyProposed;            //IN/OUT - true iff they chose planned
    int currentTripIndex;           //IN/OUT - the current index for the trip
    vector<Fan> fanList;            //IN/OUT - a list of fans for trips
    vector<Product> souvenirList;   //IN/OUT - a list of souvenirs
    vector<int> currentTrip;        //IN/OUT - a vector of indices for the trip
    bool userPlannedTrip;           //IN/OUT - true iff the user planned trip
    int prePlannedTripIndex;        //IN/OUT - index for the above type of trip





};

/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/*******************************************************************************
 *  MainWindow(QWidget *parent = nullptr)
 *    Constructor; initialize variables and set up Ui
 *    Parameters: QWidget *parent
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  ~MainWindow()
 *    Destructor; Update various files and delete Ui
 *    Parameters: none
 *    Return: void
 *******************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/*******************************************************************************
 *  vector<Stadium> stadium_list( );
 *    Accessor; Returns a vector of stadiums sorted by stadium name
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  vector<Stadium> major_league_list( );
 *    Accessor; This returns a list of stadiums sorted by team name
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  vector<Stadium> american_list( );
 *    Accessor; This returns a list of AL Stadiums sorted by team name
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  vector<Stadium> national_list( );
 *    Accessor; This returns a list of NL Stadiums sorted by team name
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  vector<Stadium> grass_list( );
 *    Accessor; This returns a list of all Stadiums with grass surface
 *     sorted by team name
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  vector<Stadium> date_opened_list( );
 *    Accessor; This returns a list of all Stadiums sorted by date opened
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  vector<Stadium> sort_by_stadium_name(vector<Stadium> stadiums);
 *    Accessor; This returns a list of the passed in stadiums sorted by stadium
 *     name
 * -----------------------------------------------------------------------------
 *    Parameters: vector<Stadium> stadiums - a list of stadiums
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  vector<Stadium> sort_by_team_name(vector<Stadium> stadiums);
 *    Accessor; This returns a list of the passed in stadiums sorted by team
 *     name
 * -----------------------------------------------------------------------------
 *    Parameters: vector<Stadium> stadiums - a list of stadiums
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  vector<Stadium> sort_by_date_opened(vector<Stadium> stadiums);
 *    Accessor; This returns a list of the passed in stadiums sorted by date
 *     opened
 * -----------------------------------------------------------------------------
 *    Parameters: vector<Stadium> stadiums - a list of stadiums
 * -----------------------------------------------------------------------------
 *    Return: vector of stadiums sorted as stated above
 *******************************************************************************/

/*******************************************************************************
 *  string print(vector<Stadium> in);
 *    Accessor; This returns a string displaying a vector of stadiums and some
 *      of its properties.
 * -----------------------------------------------------------------------------
 *    Parameters: vector<Stadium> in - a list of stadiums
 * -----------------------------------------------------------------------------
 *    Return: string that displays the list
 *******************************************************************************/

/***********************************
 ** MUTATORS **
 ***********************************/

/*******************************************************************************
 *  void buildStadiumGraph
 *
 *    Builds the definite stadiums.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void drawEdges
 *
 *    THis draws the edges of the stadium
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void buildComboBoxes
 *
 *    Builds the various comboboxes.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void makePropposedFile
 *
 *    Makes the proposed stadiums file
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void readProposedFile
 *
 *    Creates the proposed file for saving
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void drawProposed
 *
 *    Draws all of the proposed stadiums
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void updateNextStop
 *
 *    Updates the available next stop box
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void readSouvenirFile
 *
 *    Reads from the souvenir file to allow program access
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void writeSouvenirFile
 *
 *    Writes the vector of current souvenirs available to a file
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void readReceiptFile
 *
 *    Reads teh receipt file for the purchases made by fans
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void writeReceiptFile
 *
 *    Writes the receipt file for the fans
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void buildFanCombobox
 *
 *    Builds the fan combobox from the fan vector
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void forceLogin
 *
 *    Forces the user to login to the current page
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void buildSouvenirComboBox
 *
 *    Builds the available souvenirs combobox
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void buildModifyValueComboBox
 *
 *    Builds the values to modify combobox
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************
 ** Private Slots **
 *******************/
/*******************************************************************************
 *  void on_getInfoButton_clicked();
 *
 *    Gets all of the infor for the selected stadium and displays it in the box
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_getDistanceButton_clicked();
 *
 *    Calculates and displays (both on the map and in the box) the distance b/w
 *      the two selected stadiums
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_addNewStadiumButton_clicked();
 *
 *    Adds the new stadium to the list
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_addLocationButton_clicked();
 *
 *    Takes the user through adding a new physical location
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_updateCoordinateButton_clicked();
 *
 *    Actually sets the coordinate boxes according to the click
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_startTripButton_clicked();
 *
 *    Sets the current trip in motion
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_moveButton_clicked();
 *
 *    Takes the user to the next location on the trip
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_finishTripButton_clicked();
 *
 *    Finishes the user trip
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_tabWidget_currentChanged(int index);
 *
 *    Calls the forceLogin function if the tab is a particular one
 * -----------------------------------------------------------------------------
 *    Parameters: int index - the current index
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_buySouvenirButton_clicked();
 *
 *    Adds the souvenir to the fans personal vector
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_souvenirModifyBox_currentIndexChanged(int index);
 *
 *    Changes the possibilties displayed in the modify souvenir tab
 * -----------------------------------------------------------------------------
 *    Parameters: int index - the current index of the souvenir modify box
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_modifySouvenirButton_clicked();
 *
 *    Commits the souvenir modifications
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_removeSouvenirButton_clicked();
 *
 *    Removes the selected souvenir
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_addSouvenirButton_clicked();
 *
 *    Adds teh new souvenir to the various vectors
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_addFanButton_clicked();
 *
 *    Adds the new fan to the vector
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_souvenirReportButton_clicked();
 *
 *    Reports all of the souvenir purchases, updating the gui report area
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_commitModificationsButton_clicked();
 *
 *    Modifies the appropriate stadium
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_modifyStadiumBox_currentIndexChanged(int index);
 *
 *    Changes the available fields to modify
 * -----------------------------------------------------------------------------
 *    Parameters: int index - the current index
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_modifiedValueBox_currentIndexChanged(int index);
 *
 *    Changes what type of input will be gathered
 * -----------------------------------------------------------------------------
 *    Parameters: int index - the current index
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_addLocationButtonModify_clicked();
 *
 *    Adds the new location in the modify stadium section
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_updateCoordinateButtonModify_clicked();
 *
 *    Updates the coordinates in the modify stadium section
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_removeStadiumButton_clicked();
 *
 *    Removes the currently selected stadium
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_distanceThroughAllButton_clicked();
 *
 *    Updates the map and the text box to display a trip through all stadiums
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_getStadiumList_clicked();
 *
 *    Displays the currently selected list type
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/








#endif // MAINWINDOW_H
