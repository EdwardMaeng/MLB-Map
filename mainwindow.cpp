#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <sstream>
#include <fstream>

/******************************************************************************
 *  AUTHOR         : Jousha McDermott, Seongkyoo Maeng, Chak Hei Tin
 *  Project #2     : I Love Baseball
 *  CLASS          : CS 008
 *  DUE DATE       : 06/02/2020
 ******************************************************************************/

/******************************************************************************
 *
 *  Constructor MainWindow
 *_____________________________________________________________________________
 *  initialize variables and set up Ui
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    varibles are initalized and mainwindow is set up
 *****************************************************************************/
MainWindow::MainWindow(QWidget *parent) // IN - the parent of the widget
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    currentTripIndex = -1;
    currentStadiumToModify = -1;
    modifyProposed = false;
    ui->setupUi(this);
    ui->mapArea->setStyleSheet("background-image: url(mapImage.png);");
    ui->mapAreaGeneral->setStyleSheet("background-image: url(mapImage.png);");
    generalScene = new QGraphicsScene();
    scene = new QGraphicsScene();
    sceneForTrip = new QGraphicsScene();
    ui ->mapArea->setScene(scene);
    ui->mapAreaTrip->setStyleSheet("background-image: url(mapImage.png);");
    ui->mapAreaTrip->setScene(sceneForTrip);
    ui->mapAreaGeneral->setScene(generalScene);
    buildStadiumGraph();
    readProposedFile();
    readSouvenirFile();
    readReceiptFile();
    buildComboBoxes();
    buildSouvenirComboBox();
    buildFanComboBox();
    prePlannedTripIndex = 0;
    ui->mapArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapArea->setSceneRect(0,0,893,605);
    ui->mapAreaTrip->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapAreaTrip->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapAreaTrip->setSceneRect(0,0,893,605);
    ui->mapAreaGeneral->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapAreaGeneral->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapAreaGeneral->setSceneRect(0,0,893,605);
    userPlannedTrip = true;
    drawEdges();
    drawProposed();



}


/******************************************************************************
 *
 *  Destructor MainWindow
 *_____________________________________________________________________________
 *  Update members file and delete Ui
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    all files are updated and ui is deleted
 *****************************************************************************/
MainWindow::~MainWindow()
{
    writeSouvenirFile();
    makeProposedFile();
    writeReceiptFile();
    delete ui;
}


/******************************************************************************
 *
 *  Mutator getBasic: Class MainWindow
 *_____________________________________________________________________________
 *  This method draws the edges on the map
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    map has been updated
 *****************************************************************************/
void MainWindow::drawEdges()
{
    QPen pen;
    for (size_t i=0;i<graph.size();i++)
    {

        scene->addEllipse(graph[i].getX()-1,graph[i].getY()-1,3,3,pen,
                          QBrush(Qt::black));
        sceneForTrip->addEllipse(graph[i].getX()-1,graph[i].getY()-1,3,3,pen,
                                 QBrush(Qt::black));
        generalScene->addEllipse(graph[i].getX()-1,graph[i].getY()-1,3,3,pen,
                                 QBrush(Qt::black));
        set<size_t> neighbors = graph.neighbors(i);
        set<size_t>::iterator setIt = neighbors.begin();
        for (size_t j =0; j<neighbors.size();j++)
        {

            scene->addLine(graph[i].getX(),graph[i].getY(),
                           graph[*setIt].getX(),graph[*setIt].getY());
            sceneForTrip->addLine(graph[i].getX(),graph[i].getY(),
                                  graph[*setIt].getX(),graph[*setIt].getY());
            generalScene->addLine(graph[i].getX(),graph[i].getY(),
                                  graph[*setIt].getX(),graph[*setIt].getY());
            setIt++;

        }
    }
}


/******************************************************************************
 *
 *  Mutator buildComboBoxes: Class MainWindow
 *_____________________________________________________________________________
 *  This method builds the comboboxes in the gui
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Comboboxes have been build
 *****************************************************************************/
void MainWindow::buildComboBoxes()
{

    ui->stadiumToRemoveBox->clear();
    ui->stadiumComboBox->clear();
    ui->stadiumComboBox2->clear();
    ui->stadiumComboBox3->clear();
    ui->modifyStadiumBox->clear();
    ui->stadiumForAllBox->clear();

    ui->startingStadiumBox->clear();
    ui->selectedStadiumsList->clear();



    for (int i = plannedStadiums.size()-1;i>=0;i--)
    {
        ui->stadiumComboBox->insertItem(
                    0,QString::fromStdString(plannedStadiums[i].getName()));
        ui->modifyStadiumBox->insertItem(
                    0,QString::fromStdString(plannedStadiums[i].getName()));
        ui->stadiumToRemoveBox->insertItem(
                    0,QString::fromStdString(plannedStadiums[i].getName()));
    }
    for (size_t i=graph.size();i>0;i--)
    {
        ui->stadiumComboBox->insertItem(
                    0,QString::fromStdString(graph[i-1].getName()));
        ui->modifyStadiumBox->insertItem(
                    0,QString::fromStdString(graph[i-1].getName()));
        ui->stadiumComboBox2->insertItem(
                    0,QString::fromStdString(graph[i-1].getName()));
        ui->stadiumComboBox3->insertItem(
                    0,QString::fromStdString(graph[i-1].getName()));
        ui->startingStadiumBox->insertItem(
                    0,QString::fromStdString(graph[i-1].getName()));
        ui->stadiumForAllBox->insertItem(
                    0,QString::fromStdString(graph[i-1].getName()));
        ui->selectedStadiumsList->insertItem(
                    0,QString::fromStdString(graph[i-1].getName()));

    }
    buildModifyValueComboBox();



}

/******************************************************************************
 *
 *  Accessor buildComboBoxes: Class MainWindow
 *_____________________________________________________________________________
 *  This method returns a list of stadiums sorted by stadium name
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::stadium_list( )
{
    vector<Stadium> list = stadiums;


    list = sort_by_stadium_name(list);

    return list;
}


/******************************************************************************
 *
 *  Accessor major_league_list: Class MainWindow
 *_____________________________________________________________________________
 *  This method returns a list of stadiums sorted by team name
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::major_league_list( )
{
    vector<Stadium> list = stadiums;

    list = sort_by_team_name(list);

    return list;
}

/******************************************************************************
 *
 *  Accessor american_list: Class MainWindow
 *_____________________________________________________________________________
 *  This method returns a list of AL stadiums sorted by team name
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::american_list( )
{
    vector<Stadium> list = stadiums;
    vector<Stadium> new_list;

    for(size_t i = 0; i < list.size( ); i++)
        if(list.at(i).isAmerican( ))
            new_list.push_back(list.at(i));

    new_list = sort_by_team_name(new_list);

    return new_list;
}

/******************************************************************************
 *
 *  Accessor national_list: Class MainWindow
 *_____________________________________________________________________________
 *  This method returns a list of NL stadiums sorted by team name
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::national_list( )
{
    vector<Stadium> list = stadiums;
    vector<Stadium> new_list;

    for(size_t i = 0; i < list.size( ); i++)
        if(!list.at(i).isAmerican( ))
            new_list.push_back(list.at(i));

    new_list = sort_by_team_name(new_list);

    return new_list;
}

/******************************************************************************
 *
 *  Accessor grass_list: Class MainWindow
 *_____________________________________________________________________________
 *  This method returns a list of grass stadiums sorted by team name
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::grass_list( )
{
    vector<Stadium> list = stadiums;
    vector<Stadium> new_list;

    for(size_t i = 0; i < list.size( ); i++)
        if(list.at(i).isGrass( ))
            new_list.push_back(list.at(i));


    list = sort_by_team_name(new_list);

    return list;
}

/******************************************************************************
 *
 *  Accessor date_opened_list: Class MainWindow
 *_____________________________________________________________________________
 *  This method returns a list of stadiums sorted by date opened
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::date_opened_list( )
{
    vector<Stadium> list = stadiums;

    list = sort_by_date_opened(list);

    return list;
}

/******************************************************************************
 *
 *  Accessor sort_by_stadium_name: Class MainWindow
 *_____________________________________________________________________________
 *  This method sorts the inputted stadiums by stadium name
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::sort_by_stadium_name(vector<Stadium> stadiums)
//IN - the stadiums to sort
{
    for(size_t i = 0; i < stadiums.size( ); i++)
        for(size_t j = 0; j < stadiums.size( ); j++)
            if(stadiums.at(j) > stadiums.at(i))
                swap(stadiums[i], stadiums[j]);
    return stadiums;
}

/******************************************************************************
 *
 *  Accessor sort_by_team_name: Class MainWindow
 *_____________________________________________________________________________
 *  This method sorts the inputted stadiums by team name
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::sort_by_team_name(vector<Stadium> stadiums)
//IN - the stadiums to sort
{
    for(size_t i = 0; i < stadiums.size( ); i++)
        for(size_t j = 0; j < stadiums.size( ); j++)
            if(stadiums.at(j).greater_than_name(stadiums.at(i)))
                swap(stadiums[i], stadiums[j]);
    return stadiums;
}

/******************************************************************************
 *
 *  Accessor sort_by_date_opened: Class MainWindow
 *_____________________________________________________________________________
 *  This method sorts the inputted stadiums by date opened
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sorted list is returned
 *****************************************************************************/
vector<Stadium> MainWindow::sort_by_date_opened(vector<Stadium> stadiums)
//IN - the stadiums to sort
{
    for(size_t i = 0; i < stadiums.size( ); i++)
        for(size_t j = 0; j < stadiums.size( ); j++)
            if(stadiums.at(j).greater_than_date(stadiums.at(i)))
                swap(stadiums[i], stadiums[j]);
    return stadiums;
}


/******************************************************************************
 *
 *  Accessor print: Class MainWindow
 *_____________________________________________________________________________
 *  This method returns a display string for the inputted stadium list
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    display string is returned
 *****************************************************************************/
string MainWindow::print(vector<Stadium> in)
//Stadiums to print
{
    std::ostringstream ss;
    for(size_t i = 0; i < in.size( ); i++)
    {
        ss << i+1 << ") " << in.at(i) << ", " << in.at(i).getTeamName() <<
              ", ";
        ss << in.at(i).getMonth() << ", " << in.at(i).getDay() <<
              ", " << in.at(i).getYear();
        if (in.at(i).isGrass())
            ss << ", Grass" << endl;
        else
            ss << ", Non-Grass" << endl;

    }

    ss << endl << endl << endl;
    return ss.str();
}

/******************************************************************************
 *
 *  Mutator buildStadiumGraph: Class MainWindow
 *_____________________________________________________________________________
 *  This method builds the overall graph
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Graph has been build
 *****************************************************************************/
void MainWindow::buildStadiumGraph()
{
        /***************************
         ** American League Teams **
         ***************************/
        bool american = true;
        bool grass = true;
        bool no_grass = false;
        Stadium s0(american, grass, "Angels Stadium of Anaheim",
                   "Los Angeles Angels of Anaheim",
                   "2000 E Gene Autry Way", "Anaheim", "CA", "92806",
                   "(714)940-2000", "April", 19, 1966, 45483, 101, 331);
        Stadium s1(american, grass, "Comerica Park", "Detroit Tigers",
                   "2100 Woodward Ave",
                   "Detroit", "MI", "48201", "(313) 962-4000", "April", 11,
                   2000, 41681, 636, 199);
        Stadium s2(american, grass, "Fenway Park", "Boston Red Sox",
                   "4 Yawkey Way", "Boston",
                   "MA", "02215", "(877) 733-7699", "April", 20, 1912,
                   37499, 809, 166);
        Stadium s3(american, no_grass, "Globe Life Field", "Texas Rangers",
                   "1000 Ballpark Way",
                   "Arlington", "TX", "76011", "(817) 273-5222", "April",
                   1, 1994,
                   48114, 442, 400);
        Stadium s4(american, grass, "Kauffman Stadium",
                   "Kansas City Royals", "1 Royal Way",
                   "Kansas City", "MO", "64129", "(816) 921-8000", "April",
                   10, 1973,37903, 481, 274);
        Stadium s5(american, grass, "Minute Maid Park", "Houston Astros",
                   "501 Crawford St", "Houston",
                   "TX", "77002", "(713) 259-8000", "March", 30, 2000,
                   42060,
                   465, 461);
        Stadium s6(american, grass, "Oakland Coliseum",
                   "Oakland Athletics", "7000 Coliseum Way", "Oakland",
                   "CA", "94621", "(510) 569-2121", "September",
                   18, 1966, 37090,
                   58, 245);
        Stadium s7(american, grass, "Oriole Park at Camden Yards",
                   "Baltimore Orioles", "333 West Camden Street",
                   "Baltimore", "MD", "21201", "(410) 685-9800",
                   "April", 6, 1992,
                   48187, 742, 244);
        Stadium s8(american, grass, "Progressive Field",
                   "Cleveland Indians", "2401 Ontario Street",
                   "Cleveland", "OH", "44115", "(216) 420-4487",
                   "April", 2, 1994,
                   42404, 662, 216);
        Stadium s9(american, no_grass, "Rogers Centre",
                   "Toronto Blue Jays", "1 Blue Jays Way",
                    "Toronto, Ontario", "Canada", "M5V1J3",
                   "+1 416-341-1000",
                    "June", 3, 1989, 49282, 695, 157);
        Stadium s10(american, grass, "T-Mobile Park",
                    "Seattle Mariners", "1516 First Avenue South",
                    "Seattle", "WA", "98134", "(206) 346-4000",
                    "July", 15, 1999,
                    47476, 113, 65);
        Stadium s11(american, grass, "Target Field",
                    "Minnesota Twins", "353 N 5th St", "Minneapolis",
                    "MN", "55403", "(800) 338-9467",
                    "April", 12, 2010, 39021,
                    492, 159);
        Stadium s12(american, no_grass, "Tropicana Field",
                    "Tampa Bay Rays", "1 Tropicana Dr",
                    "St. Petersburg",
                    "FL", "33705", "(727) 825-3137", "March", 3,
                    1990, 31042,
                    694, 476);
        Stadium s13(american, grass, "Guaranteed Rate Field",
                    "Chicago White Sox", "333 West 35th Street",
                    "Chicago", "IL", "60616", "(312) 674-1000",
                    "April", 18, 1991,
                    40615, 574, 216);
        Stadium s14(american, grass, "Yankee Stadium",
                    "New York Yankees", "1 E 161st St", "South Bronx",
                    "NY", "10451", "(718) 293-4300", "April",
                    16, 2009, 50291,
                    783, 202);

        /***************************
         ** National League Teams **
         ***************************/
        american = false;
        Stadium s15(american, grass, "Oracle Park",
                    "San Francisco Giants", "24 Willie Mays Plaza",
                    "Sam Francisco", "CA", "94107", "(415) 972-2000",
                    "April", 11,
                    2000, 41915, 58, 245);
        Stadium s16(american, grass, "Busch Stadium",
                    "St. Louis Cardinals", "700 Clark Street",
                    "St. Louis", "MO", "63102", "(314) 345-9600",
                    "April", 10,
                    2006, 46861, 538, 282);
        Stadium s17(american, no_grass, "Chase Field",
                    "Arizona Diamondbacks", "401 East Jefferson Street",
                    "Phoenix", "AZ", "85004", "(602) 462-6500",
                    "March", 31, 1998,
                    48633, 197, 362);
        Stadium s18(american, grass, "Citi Field", "New York Mets",
                    "126th St. & Roosevelt Ave.", "Queens",
                    "NY", "11368", "(718) 507-6387", "April", 13,
                    2009, 41922,
                    783, 202);
        Stadium s19(american, grass, "Citizens Bank Park",
                    "Philadelphia Phillies", "1 Citizens Bank Way",
                    "Philadelphia", "PA", "19148", "(215) 463-1000",
                    "April", 3, 2004,
                    43651, 761, 221);
        Stadium s20(american, grass, "Coors Field", "Colorado Rockies",
                    "2001 Blake St", "Denver",
                    "CO", "80205", "(303) 292-0200", "April", 26, 1995, 50480,
                    319, 252);
        Stadium s21(american, grass, "Dodger Stadium", "Los Angeles Dodgers",
                    "1000 Elysian Park Avenue",
                    "Los Angeles", "CA", "90090", "(323) 224-1507",
                    "April", 10, 1962,
                    56000, 101, 331);
        Stadium s22(american, grass, "Great America Ball Park",
                    "Cincinnati Reds", "100 Joe Nuxhall Way",
                    "Cincinnati", "OH", "45202", "(513) 381-7337",
                    "March", 31, 2003, 42319,
                    633, 260);
        Stadium s23(american, no_grass, "Marlins Park", "Miami Marlins",
                    "501 Marlins Way", "Miami",
                    "FL", "33125", "(305)480-1300", "April", 4, 2012, 37442,
                   731, 515);
        Stadium s24(american, grass, "Miller Park", "Milwaukee Brewers",
                    "1 Brewers Way", "Milwaukee",
                    "WI", "53214", "(414) 902-4400", "April", 6, 2001, 41900,
                    569, 188);
        Stadium s25(american, grass, "Nationals Park", "Washington Nationals",
                    "1500 S Capitol St SE",
                    "Washington", "DC", "20003", "(202) 675-6287",
                    "March", 30, 2008,
                    41418, 742, 244);
        Stadium s26(american, grass, "Petco Park", "San Diego Padres",
                    "19 Tony Gwynn Drive", "Sam Diego",
                    "CA", "92101", "(619) 795-5000", "April", 8, 2004, 42524,
                    117, 357);
        Stadium s27(american, grass, "PNC Park", "Pittsburgh Pirates",
                    "115 Federal St", "Pittsburgh",
                    "PA", "15212", "(412) 321-2827", "March", 31, 2001, 38362,
                    697, 225);
        Stadium s28(american, grass, "Truist Park", "Atlanta Braves",
                    "755 Hank Aaron Drive", "Atlanta",
                    "GA", "30315", "(404) 522-7630", "March", 29, 1997, 49586,
                    645, 368);
        Stadium s29(american, grass, "Wrigley Field", "Chicago Cubs",
                    "1060 West Addison Street",
                    "Chicago", "IL", "60613", "(773) 404-2827", "April",
                    23, 1914,
                    42374, 574, 216);

        // *** Pushed all the stadiums into a vector ***
        stadiums.push_back(s0);
        stadiums.push_back(s1);
        stadiums.push_back(s2);
        stadiums.push_back(s3);
        stadiums.push_back(s4);
        stadiums.push_back(s5);
        stadiums.push_back(s6);
        stadiums.push_back(s7);
        stadiums.push_back(s8);
        stadiums.push_back(s9);
        stadiums.push_back(s10);
        stadiums.push_back(s11);
        stadiums.push_back(s12);
        stadiums.push_back(s13);
        stadiums.push_back(s14);
        stadiums.push_back(s15);
        stadiums.push_back(s16);
        stadiums.push_back(s17);
        stadiums.push_back(s18);
        stadiums.push_back(s19);
        stadiums.push_back(s20);
        stadiums.push_back(s21);
        stadiums.push_back(s22);
        stadiums.push_back(s23);
        stadiums.push_back(s24);
        stadiums.push_back(s25);
        stadiums.push_back(s26);
        stadiums.push_back(s27);
        stadiums.push_back(s28);
        stadiums.push_back(s29);

        graph.add_vertex(s0);
        graph.add_vertex(s1);
        graph.add_vertex(s2);
        graph.add_vertex(s3);
        graph.add_vertex(s4);
        graph.add_vertex(s5);
        graph.add_vertex(s6);
        graph.add_vertex(s7);
        graph.add_vertex(s8);
        graph.add_vertex(s9);
        graph.add_vertex(s10);
        graph.add_vertex(s11);
        graph.add_vertex(s12);
        graph.add_vertex(s13);
        graph.add_vertex(s14);
        graph.add_vertex(s15);
        graph.add_vertex(s16);
        graph.add_vertex(s17);
        graph.add_vertex(s18);
        graph.add_vertex(s19);
        graph.add_vertex(s20);
        graph.add_vertex(s21);
        graph.add_vertex(s22);
        graph.add_vertex(s23);
        graph.add_vertex(s24);
        graph.add_vertex(s25);
        graph.add_vertex(s26);
        graph.add_vertex(s27);
        graph.add_vertex(s28);
        graph.add_vertex(s29);

        // --- Safeco Field (10) ---
        graph.add_edge(10, 15, 680);
        graph.add_edge(10, 6, 680);
        graph.add_edge(10, 11, 1390);
        graph.add_edge(10, 9, 2070);

        // --- AT&T Park (15) & O.co Coliseum (6)
        graph.add_edge(15, 0, 340);
        graph.add_edge(15, 21, 340);
        graph.add_edge(15, 17, 650);
        graph.add_edge(6, 0, 340);
        graph.add_edge(6, 21, 340);
        graph.add_edge(6, 17, 650);
        graph.add_edge(6,15,10);

        // --- Angel (0) & Dodgers (21) ---
        graph.add_edge(0, 26, 110);
        graph.add_edge(0, 11, 1500);
        graph.add_edge(21, 26, 110);
        graph.add_edge(21, 11, 1500);
        graph.add_edge(0,21,10);

        // --- PETCO Park (26) ---
        graph.add_edge(26, 20, 830);
        graph.add_edge(26, 17, 300);

        // --- Chase Field (17) ---
        graph.add_edge(17, 20, 580);
        graph.add_edge(17, 3, 870);
        graph.add_edge(17, 5, 1115);

        // --- Coors Field (20) ---
        graph.add_edge(20, 4, 560);
        graph.add_edge(20, 3, 650);

        // --- Minute Maid Park (5) ---
        graph.add_edge(5, 3, 230);
        graph.add_edge(5, 16, 680);
        graph.add_edge(5, 12, 790);
        graph.add_edge(5, 23, 965);

        // --- Rangers Ballpark (3) ---
        graph.add_edge(3, 4, 460);
        graph.add_edge(3, 28, 740);

        // --- Kauffman Stadium (4) ---
        graph.add_edge(4, 29, 415);
        graph.add_edge(4, 13, 415);
        graph.add_edge(4, 16, 235);

        // --- Target Field (11) ---
        graph.add_edge(11, 24, 300);
        graph.add_edge(11, 16, 465);

        // --- Busch Stadium (16) ---
        graph.add_edge(16, 22, 310);

        // --- Miller Park (24) ---
        graph.add_edge(24, 9, 430);
        graph.add_edge(24, 29, 80);
        graph.add_edge(24, 13, 80);

        // --- Wrigley Field (29) & US Cellular Field (13) ---
        graph.add_edge(29, 1, 240);
        graph.add_edge(29, 22, 250);
        graph.add_edge(13, 1, 240);
        graph.add_edge(13, 22, 250);
        graph.add_edge(13,29,10);

        // --- Great America Ballpark (22) ---
        graph.add_edge(22, 8, 225);
        graph.add_edge(22, 27, 260);
        graph.add_edge(22, 12, 790);
        graph.add_edge(22, 28, 375);

        // --- Turner Field (28) ---
        graph.add_edge(28, 7, 560);
        graph.add_edge(28, 25, 560);
        graph.add_edge(28, 23, 600);

        // --- Tropicano Field (12) ---
        graph.add_edge(12, 23, 210);

        // --- Marlins Park (23) ---
        graph.add_edge(23, 7, 930);
        graph.add_edge(23, 25, 930);
        graph.add_edge(23, 2, 1255);

        // --- Comerica Park (1) ---
        graph.add_edge(1, 9, 210);
        graph.add_edge(1, 8, 90);

        // --- Progressive Field (8) ---
        graph.add_edge(8, 27, 115);

        // --- Rogers Center (9) ---
        graph.add_edge(9, 2, 430);
        graph.add_edge(9, 27, 225);

        // --- PNC Park (27) ---
        graph.add_edge(27, 14, 315);
        graph.add_edge(27, 18, 315);
        graph.add_edge(27, 7, 195);
        graph.add_edge(27, 25, 195);

        // --- Nationals Park (25) & Camden Yards (7) ---
        graph.add_edge(25, 19, 90);
        graph.add_edge(7, 19, 90);
        graph.add_edge(7,25,10);

        // --- Citizens Bank Park (19) ---
        graph.add_edge(19, 14, 80);
        graph.add_edge(19, 18, 80);

        // --- Yankee Stadium (14) & Citi Field (18) ---
        graph.add_edge(14, 2, 195);
        graph.add_edge(18, 2, 195);
        graph.add_edge(14,18,10);



}

/******************************************************************************
 *
 *  Mutator on_getInfoButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This slot displays the info for the selected stadium
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Info has been displayed
 *****************************************************************************/
void MainWindow::on_getInfoButton_clicked()
{
    QString display;
    int index = ui->stadiumComboBox->currentIndex();
    string text;
    if (index <= 29)
    {
        text = graph[index].print_info();
        display = QString::fromStdString(text);
        ui->stadiumInfo->setText(display);
        return;
    }
    text = plannedStadiums[index-graph.size()].print_info();
    display = QString::fromStdString(text);
    ui->stadiumInfo->setText(display);
}

/******************************************************************************
 *
 *  Mutator on_getDistanceButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This slot displays the distances for the selected stadiums
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Info has been displayed
 *****************************************************************************/
void MainWindow::on_getDistanceButton_clicked()
{
    generalScene->clear();
    drawEdges();
    drawProposed();

    int fromIndex = ui->stadiumComboBox2->currentIndex();
    int toIndex = ui -> stadiumComboBox3 ->currentIndex();

    if (fromIndex == toIndex)
    {

        ui->distanceEdit->setText("N/A");
        return;

    }

    if ((fromIndex == 14 && toIndex==18) || (fromIndex == 18 && toIndex==14))
    {
        ui->distanceEdit->setText("0");
        return;
    }
    if ((fromIndex == 25 && toIndex==7) || (fromIndex == 7 && toIndex==25))
    {
        ui->distanceEdit->setText("0");
        return;
    }
    if ((fromIndex == 29 && toIndex==13) || (fromIndex == 13 && toIndex==29))
    {
        ui->distanceEdit->setText("0");
        return;
    }
    if ((fromIndex == 21 && toIndex==0) || (fromIndex == 0 && toIndex==21))
    {
        ui->distanceEdit->setText("0");
        return;
    }
    if ((fromIndex == 15 && toIndex==6) || (fromIndex == 6 && toIndex==15))
    {
        ui->distanceEdit->setText("0");
        return;
    }


    vector<int> pathVector;


    pathVector =  graph.getVerticesJosh(fromIndex,toIndex);

    size_t totalDistance = 0;

    //min will be 2
    for (size_t i = 0; i < pathVector.size()-1;i++)
    {
        cout << graph[pathVector[i]].getName() << endl;
        totalDistance += graph.getWeight(pathVector[i],pathVector[i+1]);
    }

    ui->distanceEdit->setText(QString::number(totalDistance));

    QPen pen;
    pen.setColor(Qt::darkRed);
    pen.setWidth(3);
    generalScene->addEllipse(graph[fromIndex].getX()-4,
                             graph[fromIndex].getY()-4,11,11,
                             pen,QBrush(Qt::darkRed));
    generalScene->addEllipse(graph[toIndex].getX()-4,
                             graph[toIndex].getY()-4,
                             11,11,pen,QBrush(Qt::darkRed));
    pen.setWidth(3);
    for (size_t i = 0; i < pathVector.size()-1;i++)
    {
        generalScene->addLine(graph[pathVector[i]].getX(),
                graph[pathVector[i]].getY(),graph[pathVector[i+1]].getX(),
                graph[pathVector[i+1]].getY(),pen);
    }

}

/******************************************************************************
 *
 *  Mutator on_addNewStadiumButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This slot gathers all of the info and adds the new stadium
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Stadium has been added
 *****************************************************************************/
void MainWindow::on_addNewStadiumButton_clicked()
{
    bool american = false;
    if (ui->americanLeagueEntry->currentIndex() == 0)
        american = true;
    bool grass = true;
    string teamName = ui->teamNameEntry->text().toStdString();
    string city = ui->cityEntry->text().toStdString();
    string state = ui->stateEntry->text().toStdString();
    string zip = ui->zipEntry->text().toStdString();
    string stadiumName = ui->stadiumNameEntry->text().toStdString();
    string number = ui->phoneNumberEntry->text().toStdString();
    string address = ui->addressEntry->text().toStdString();
    string month = ui->dateEdit->date().toString("MMMM").toStdString();
    int day = ui->dateEdit->date().day();
    int year = ui->dateEdit->date().year();
    int capacity = ui->capacityEdit->value();
    if ((ui->xCoordEntry->text() == "") || (ui->yCoordEntry->text() == ""))
        return;
    int xCoord = ui->xCoordEntry->text().toInt();
    int yCoord = ui->yCoordEntry->text().toInt();

    if ((teamName == "") || (city == "") || (state =="") || (zip =="") ||
            (stadiumName=="") || (number == "") || (address == "") ||
            (month == ""))
        return;

    QMessageBox msgBox;
    Stadium team = Stadium(american,grass,stadiumName,teamName,
                           address,city,state,zip,number,month,
                           day,year,capacity,xCoord,yCoord);
    plannedStadiums.push_back(team);
    QPen pen;
    scene->addEllipse(team.getX()-3,team.getY()-3,8,8,pen, QBrush(Qt::black));
    generalScene->addEllipse(team.getX()-3,team.getY()-3,8,8,pen,
                             QBrush(Qt::black));
    QGraphicsTextItem *text = scene->addText(QString::fromStdString(
                                                 team.getName()));
    QGraphicsTextItem *text2 = generalScene->addText(QString::fromStdString(
                                                         team.getName()));

    text->setPos(team.getX(), team.getY()-10);
    text2->setPos(team.getX(), team.getY()-10);

    buildComboBoxes();


}

/******************************************************************************
 *
 *  Mutator on_addLocationButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This slot helps the user determine how to add a location
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    User knows how to add the location
 *****************************************************************************/
void MainWindow::on_addLocationButton_clicked()
{
    ui->mapArea->clearVectors();
    QMessageBox msgBox;
    msgBox.setText("After clicking okay, \n"
                   "click the point on the map where the proposed "
                   "stadium will be.\n"
                   "the coordinates will display in the box after "
                   "clicking update.");
    msgBox.exec();

}

/******************************************************************************
 *
 *  Mutator makeProposedFile: Class MainWindow
 *_____________________________________________________________________________
 *  This method makes the proposed stadium file
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Proposed stadium file has been made
 *****************************************************************************/
void MainWindow::makeProposedFile()
{
    if (plannedStadiums.size() == 0)
        return;
    std::ofstream outputFile("proposedStadiums.txt");
    for (int i = plannedStadiums.size()-1;i>=0;i--)
    {

        outputFile << plannedStadiums[i].getName() << endl;
        outputFile << plannedStadiums[i].getTeamName() << endl;
        outputFile << plannedStadiums[i].getStreetAddress() << endl;
        outputFile << plannedStadiums[i].getCity() << endl;
        outputFile << plannedStadiums[i].getState() << endl;
        outputFile << plannedStadiums[i].getZip() << endl;
        outputFile << plannedStadiums[i].getPhoneNumber() << endl;
        outputFile << plannedStadiums[i].getMonth() << endl;
        outputFile << plannedStadiums[i].getDay() << endl;
        outputFile << plannedStadiums[i].getYear() << endl;
        outputFile << plannedStadiums[i].getCapacity() << endl;
        outputFile << plannedStadiums[i].getX() << endl;
        outputFile << plannedStadiums[i].getY() << endl;
        if (plannedStadiums[i].isAmerican())
            outputFile<<"American";
        else
            outputFile << "National";
        if (i != 0)
            outputFile << endl;
    }
}

/******************************************************************************
 *
 *  Mutator readProposedFile: Class MainWindow
 *_____________________________________________________________________________
 *  This method reads the proposed stadium file
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Proposed stadium file has been read
 *****************************************************************************/
void MainWindow::readProposedFile()
{
    std::ifstream inputFile;
    inputFile.open("proposedStadiums.txt");
    if(inputFile.fail()){
        std::cout << "Proposed Stadiums File DNE yet" << std::endl;
    }
    else
    {
        std::string stadiumName;
        std::string teamName;
        std::string streetAddress;
        std::string city;
        std::string state;
        std::string zip;
        string phoneNumber;
        string month;
        string day, year, capacity, xCoord, yCoord;
        string leagueString;
        bool american, grass;
        grass = true;
        while(inputFile.good())
        {
            getline(inputFile, stadiumName, '\n');
            getline(inputFile, teamName, '\n');
            getline(inputFile, streetAddress, '\n');
            getline(inputFile, city, '\n');
            getline(inputFile, state, '\n');
            getline(inputFile, zip, '\n');
            getline(inputFile, phoneNumber, '\n');
            getline(inputFile, month, '\n');
            getline(inputFile, day, '\n');
            getline(inputFile, year, '\n');
            getline(inputFile, capacity, '\n');
            getline(inputFile, xCoord, '\n');
            getline(inputFile, yCoord, '\n');
            getline(inputFile, leagueString, '\n');
            if (leagueString == "American")
            {
                american = true;
            }
            else
                american = false;

            plannedStadiums.push_back(Stadium(american, grass, stadiumName,
                                              teamName,
                                              streetAddress,city,state,zip,
                                              phoneNumber,month,stoi(day),
                                              stoi(year),stoi(capacity),
                                              stoi(xCoord),stoi(yCoord)));
        }
        inputFile.close();
    }
}

/******************************************************************************
 *
 *  Mutator drawProposed: Class MainWindow
 *_____________________________________________________________________________
 *  This method draws the proposed stadiums
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Proposed stadiums have been drawn
 *****************************************************************************/
void MainWindow::drawProposed()
{
    for (int i = 0;i<plannedStadiums.size();i++)
    {

        QPen pen;
        scene->addEllipse(plannedStadiums[i].getX()-3,
                          plannedStadiums[i].getY()-3,8,8,
                          pen, QBrush(Qt::black));
        QGraphicsTextItem *text = scene->addText(
                    QString::fromStdString(
                        plannedStadiums[i].getName()));
        text->setPos(plannedStadiums[i].getX(),
                     plannedStadiums[i].getY()-10);
        generalScene->addEllipse(plannedStadiums[i].getX()-3,
                                 plannedStadiums[i].getY()-3,
                                 8,8,pen, QBrush(Qt::black));
        QGraphicsTextItem *text2 = generalScene->addText(
                    QString::fromStdString(plannedStadiums[i].getName()));
        text2->setPos(plannedStadiums[i].getX(), plannedStadiums[i].getY()-10);
    }
}

/******************************************************************************
 *
 *  Mutator updateNextStop: Class MainWindow
 *_____________________________________________________________________________
 *  This method updates the possible next stops
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Next stadiums have been updated
 *****************************************************************************/
void MainWindow::updateNextStop()
{
    ui->nextStopBox->clear();
    set<size_t> neighbors = graph.neighbors(currentTripIndex);
    set<size_t>::iterator setIt = neighbors.begin();
    for (size_t j =0; j<neighbors.size();j++)
    {
        ui->nextStopBox->addItem(QString::fromStdString(
                                     graph[*setIt].getName()));
        setIt++;
    }
}

/******************************************************************************
 *
 *  Mutator readSouvenirFile: Class MainWindow
 *_____________________________________________________________________________
 *  This method updates the souvenir vector
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Souvenir file has been read
 *****************************************************************************/
void MainWindow::readSouvenirFile()
{
    std::ifstream inputFile;
    inputFile.open("souvenirList.txt");
    if(inputFile.fail()){
        std::cout << "Failed to find souvenir file." << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::string souvenirName;
        std::string souvenirPrice;
        while(inputFile.good())
        {
            getline(inputFile, souvenirName, '\n');
            if (souvenirName == "")
            {
                return;
            }
            getline(inputFile, souvenirPrice, '\n');
            souvenirList.push_back(Product(souvenirName,stod(souvenirPrice)));
        }
        inputFile.close();
    }
}

/******************************************************************************
 *
 *  Mutator writeSouvenirFile: Class MainWindow
 *_____________________________________________________________________________
 *  This method updates the souvenir file
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Souvenir file has been written
 *****************************************************************************/
void MainWindow::writeSouvenirFile()
{
    std::ofstream outputFile("souvenirList.txt");
    for (int i = 0;i<souvenirList.size();i++)
    {

        outputFile << souvenirList[i]._name << endl;
        outputFile << souvenirList[i].priceString();
        if (i != souvenirList.size()-1)
            outputFile << endl;
    }
}

/******************************************************************************
 *
 *  Mutator readReceiptFile: Class MainWindow
 *_____________________________________________________________________________
 *  This method reads the receipt file
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Receipt file has been read
 *****************************************************************************/
void MainWindow::readReceiptFile()
{

    std::ifstream inputFile;
    inputFile.open("receipt.txt");
    if(inputFile.fail()){
        std::cout << "Receipt File DNE yet." << std::endl;
    }
    else
    {
        std::string fanName;
        std::string souvenirName;
        std::string souvenirPrice;
        while(inputFile.good())
        {
            getline(inputFile, fanName, '\n');
            getline(inputFile, souvenirName, '\n');
            getline(inputFile, souvenirPrice, '\n');
            Fan temp = Fan(fanName);
            int numOccurences = 0;
            numOccurences = count(fanList.begin(), fanList.end(), temp);
            if (numOccurences == 0)//Not in list yet
            {
                Fan newFan = Fan(fanName);
                Product newProduct = Product(souvenirName,stod(souvenirPrice));
                newFan.addProduct(newProduct);
                fanList.push_back(newFan);
            }
            else //already in the list
            {
                std::vector<Fan>::iterator it;
                it = std::find(fanList.begin(), fanList.end(), temp);
                Product newProduct = Product(souvenirName,stod(souvenirPrice));
                if (it != fanList.end())
                    (*it).addProduct(newProduct);
            }
        }
        inputFile.close();
    }
}

/******************************************************************************
 *
 *  Mutator writeReceiptFile: Class MainWindow
 *_____________________________________________________________________________
 *  This method writes the receipt file
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Receipt file has been written
 *****************************************************************************/
void MainWindow::writeReceiptFile()
{
    std::ofstream outputFile("receipt.txt");
    for (int i = 0;i<fanList.size();i++)
    {
        Fan tempFan = fanList[i];
        vector<Product> tempSouvList = tempFan.souvenir();
        if (tempSouvList.size() == 0)
            continue;
        for (int j = 0;j<tempSouvList.size();j++)
        {
            outputFile << tempFan.name() << endl;
            outputFile << tempSouvList[j]._name << endl;
            outputFile << tempSouvList[j].priceString();
            if ((i!=fanList.size()-1) || (j!=tempSouvList.size()-1))
                outputFile << endl;
        }
    }
}

/******************************************************************************
 *
 *  Mutator buildFanComboBox: Class MainWindow
 *_____________________________________________________________________________
 *  This method builds the fan combo box
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Fan combobox has been built
 *****************************************************************************/
void MainWindow::buildFanComboBox()
{
    ui->fanBox->clear();
    for (int i = 0;i<fanList.size();i++)
    {
        ui->fanBox->addItem(QString::fromStdString(fanList[i].name()));
    }

}

/******************************************************************************
 *
 *  Mutator forceLogin: Class MainWindow
 *_____________________________________________________________________________
 *  This method forces the user to log in
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    User has logged in
 *****************************************************************************/
void MainWindow::forceLogin()
{
    QString password = "password";
    QString input = "";
    while (input != password)
    {
        bool accept;
        QString name = QInputDialog::getText(this,
                tr("Login"),
                tr("Please Enter the Password Below:"),
                QLineEdit::Normal, tr("Pass"),&accept);
        if (accept && !name.isEmpty())
        {
            input = name;
        }
    }

}

/******************************************************************************
 *
 *  Mutator buildSouvenirComboBox: Class MainWindow
 *_____________________________________________________________________________
 *  This method builds the souvenir combobox
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Souvenir combobox has been built
 *****************************************************************************/
void MainWindow::buildSouvenirComboBox()
{
    ui->souvenirPurchaseBox->clear();
    ui->souvenirModifyBox->clear();
    ui->souvenirRemoveBox->clear();
    for (int i=0;i<souvenirList.size();i++)
    {
        QString name = QString::fromStdString(souvenirList[i]._name);
        QString price = QString::fromStdString(souvenirList[i].priceString());


        ui->souvenirPurchaseBox->addItem(name + " ($" + price + ")");
        ui->souvenirModifyBox->addItem(name + " ($" + price + ")");
        ui->souvenirRemoveBox->addItem(name + " ($" + price + ")");

    }
}

/******************************************************************************
 *
 *  Mutator buildModifyValueComboBox: Class MainWindow
 *_____________________________________________________________________________
 *  This method builds the modify souvenir combobox
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Souvenir combobox has been built
 *****************************************************************************/
void MainWindow::buildModifyValueComboBox()
{
    ui->modifiedValueBox->clear();
    //Changes to modified Stadiums follow notes in doc
    ui->modifiedValueBox->addItem("Team Name");//0
    ui->modifiedValueBox->addItem("Street Address");//1
    ui->modifiedValueBox->addItem("Phone Number");//2
    ui->modifiedValueBox->addItem("Capacity");//3

    if (modifyProposed)
    {
        ui->modifiedValueBox->addItem("Stadium Name");//4
        ui->modifiedValueBox->addItem("City");//5
        ui->modifiedValueBox->addItem("State");//6
        ui->modifiedValueBox->addItem("Zip");//7
        ui->modifiedValueBox->addItem("Month Opened");//8
        ui->modifiedValueBox->addItem("Day Opened");//9
        ui->modifiedValueBox->addItem("Year Opened");//10
        ui->modifiedValueBox->addItem("Change Map Location");//11
    }
}

/******************************************************************************
 *
 *  Mutator on_modifiedValueBox_currentIndexChanged: Class MainWindow
 *_____________________________________________________________________________
 *  This slot is called when the current index changes on the modify value.
 *    it changes the display of the gui
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The getlocation feature is properly set
 *****************************************************************************/
void MainWindow::on_modifiedValueBox_currentIndexChanged(int index)
//IN - the index of the combo box
{
    if (index == -1)
        return;
    ui->addLocationButtonModify->setEnabled(false);
    ui->xCoordEntryModify->setEnabled(false);
    ui->yCoordEntryModify->setEnabled(false);
    ui->updateCoordinateButtonModify->setEnabled(false);
    ui->modifyStadiumOldValueEntry->setText("");
    switch (index)
    {
    case 0:
    {
        if (modifyProposed)
        {
            QString display = QString::fromStdString(
                        plannedStadiums[currentStadiumToModify].getTeamName());
            ui->modifyStadiumOldValueEntry->setText(display);
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::fromStdString(
                        graph[currentStadiumToModify].getTeamName()));
        break;
    }
    case 1:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::fromStdString(
                            plannedStadiums[currentStadiumToModify].
                            getStreetAddress()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::fromStdString(
                        graph[currentStadiumToModify].getStreetAddress()));
        break;
    }
    case 2:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::fromStdString(
                            plannedStadiums[currentStadiumToModify].
                            getPhoneNumber()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::fromStdString(
                        graph[currentStadiumToModify].
                        getPhoneNumber()));
        break;
    }
    case 3:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::number(
                            plannedStadiums[currentStadiumToModify].
                            getCapacity()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::number(
                        graph[currentStadiumToModify].getCapacity()));
        break;
    }
    case 4:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::fromStdString(
                            plannedStadiums[currentStadiumToModify].
                            getName()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::fromStdString(
                        graph[currentStadiumToModify].
                        getName()));
        break;
    }
    case 5:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::fromStdString(
                            plannedStadiums[currentStadiumToModify].
                            getCity()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::fromStdString(
                        graph[currentStadiumToModify].
                        getCity()));
        break;
    }
    case 6:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::fromStdString(
                            plannedStadiums[currentStadiumToModify].
                            getState()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::fromStdString(
                        graph[currentStadiumToModify].getState()));
        break;
    }
    case 7:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::fromStdString(
                            plannedStadiums[currentStadiumToModify].getZip()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::fromStdString(
                        graph[currentStadiumToModify].getZip()));
        break;
    }
    case 8:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::fromStdString(
                            plannedStadiums[currentStadiumToModify].
                            getMonth()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::fromStdString(
                        graph[currentStadiumToModify].getMonth()));
        break;
    }
    case 9:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::number(
                            plannedStadiums[currentStadiumToModify].getDay()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::number(
                        graph[currentStadiumToModify].getDay()));
        break;
    }
    case 10:
    {
        if (modifyProposed)
        {
            ui->modifyStadiumOldValueEntry->setText(
                        QString::number(
                            plannedStadiums[currentStadiumToModify].
                            getYear()));
            break;
        }
        ui->modifyStadiumOldValueEntry->setText(
                    QString::number(
                        graph[currentStadiumToModify].getYear()));
        break;
    }
    case 11:
    {
        if (modifyProposed)
        {
            ui->addLocationButtonModify->setEnabled(true);
            ui->xCoordEntryModify->setEnabled(true);
            ui->yCoordEntryModify->setEnabled(true);
            ui->updateCoordinateButtonModify->setEnabled(true);
            break;
        }
        break;
    }
    default:
    {
        break;
    }
    }
}

/******************************************************************************
 *
 *  Mutator on_updateCoordinateButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This slot is called when the coordinates are set to update
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The coordinates have been updated
 *****************************************************************************/
void MainWindow::on_updateCoordinateButton_clicked()
{
    if (ui->mapArea->xCoords.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText(
                    "You must click a point on the map to add the stadium.\n"
                       "Please close this window and click on the map again.\n"
                       "Afterwards, try and update the coordinates again.");
        msgBox.exec();
        return;
    }
    int xCoord = ui->mapArea->xCoords[0];
    int yCoord = ui->mapArea->yCoords[0];
    ui->xCoordEntry->setText(QString::number(xCoord));
    ui->yCoordEntry->setText(QString::number(yCoord));

}

/******************************************************************************
 *
 *  Mutator on_startTripButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This triggers the starting trip mechanism
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The trip has been set as starteed
 *****************************************************************************/
void MainWindow::on_startTripButton_clicked()
{
    userPlannedTrip = true;
    ui->tripReportArea->clear();
    currentTrip.clear();
    sceneForTrip->clear();
    drawEdges();
    currentTripIndex = ui->startingStadiumBox->currentIndex();
    QModelIndexList indices = ui->selectedStadiumsList->
            selectionModel()->selectedIndexes();
    std::vector<int> indexList;
    foreach(QModelIndex index, indices)
    {
        indexList.push_back(index.row());
    }


    bool allowed[30];
    int tally = 0;
    for (int i=0;i<30;i++)
    {
        allowed[i] = false;
        if(count(indexList.begin(),indexList.end(),i)==1)
        {
            if (i==currentTripIndex)
                return;
            if (i!=currentTripIndex)
            {
                allowed[i] = true;
                tally++;
            }
        }
    }

    if (tally == 0)
        userPlannedTrip = true;
    else
        userPlannedTrip = false;

    if (userPlannedTrip)
        currentTrip.push_back(currentTripIndex);
    else
    {
        if (tally == 1)
           currentTrip = graph.getVerticesJosh(
                       currentTripIndex,
                       ui->selectedStadiumsList->currentRow());
        else
            currentTrip = graph.minPathV1(currentTripIndex,allowed);
        prePlannedTripIndex = 0;
    }

    if (userPlannedTrip)
    {
        Stadium startStadium = graph[currentTripIndex];
        QPen pen;
        pen.setColor(Qt::darkRed);
        pen.setWidth(3);
        sceneForTrip->addEllipse(startStadium.getX()-4,
                                 startStadium.getY()-4,11,11,pen);
        set<size_t> neighbors = graph.neighbors(currentTripIndex);
        set<size_t>::iterator setIt = neighbors.begin();
        pen.setWidth(3);
        for (size_t j =0; j<neighbors.size();j++)
        {
            sceneForTrip->addLine(graph[currentTripIndex].getX(),
                                  graph[currentTripIndex].getY(),
                                  graph[*setIt].getX(),graph[*setIt].getY(),
                    pen);
            setIt++;
        }
        updateNextStop();
    }
    else
    {
        Stadium startStadium = graph[currentTripIndex];
        QPen pen;
        pen.setColor(Qt::darkRed);
        pen.setWidth(3);
        sceneForTrip->addEllipse(startStadium.getX()-4,
                                 startStadium.getY()-4,
                                 11,11,pen,QBrush(Qt::darkRed));
    }

}

/******************************************************************************
 *
 *  Mutator on_moveButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This triggers the moving mechanism
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The next stop has been moved to.
 *****************************************************************************/
void MainWindow::on_moveButton_clicked()
{
    if (currentTripIndex==-1)
    {
        return;
    }

    if(userPlannedTrip)
    {
        int nextStopBoxIndex = ui->nextStopBox->currentIndex();
        int nextStopIndex;
        set<size_t> neighbors = graph.neighbors(currentTripIndex);
        set<size_t>::iterator setIt = neighbors.begin();
        for (size_t j =0; j<nextStopBoxIndex;j++)
        {
            setIt++;
        }
        nextStopIndex = *setIt;
        currentTrip.push_back(nextStopIndex);
        sceneForTrip->clear();
        drawEdges();
        Stadium currentStadium = graph[nextStopIndex];
        currentTripIndex = nextStopIndex;
        QPen pen;
        pen.setColor(Qt::darkRed);
        pen.setWidth(3);
        sceneForTrip->addEllipse(currentStadium.getX()-4,
                                 currentStadium.getY()-4,11,11,pen);
        set<size_t> newNeighbors = graph.neighbors(currentTripIndex);
        setIt = newNeighbors.begin();
        for (size_t j =0; j<newNeighbors.size();j++)
        {
            sceneForTrip->addLine(graph[currentTripIndex].getX(),
                                  graph[currentTripIndex].getY(),
                                  graph[*setIt].getX(),graph[*setIt].getY(),
                    pen);
            setIt++;
        }
        updateNextStop();
    }
    if (!userPlannedTrip)
    {
        if (prePlannedTripIndex == currentTrip.size()-1)
        {
            //they are ending the trip
            QPen pen;
            pen.setColor(Qt::darkRed);
            pen.setWidth(3);
            sceneForTrip->addEllipse(
                        graph[currentTrip[prePlannedTripIndex]].getX()-4,
                    graph[currentTrip[prePlannedTripIndex]].getY()-4,11,11,
                    pen,QBrush(Qt::darkRed));
            QString report;
            report += ui->fanBox->currentText();
            report += "\n";
            report += "------------------------------------------\n";

            report += "Stadiums Visited:\n";
            for (int i = 0; i<currentTrip.size();i++)
            {
                report += QString::fromStdString(
                            graph[currentTrip[i]].getName()) + "\n";

            }
            report += "Number of Stadiums Visited: " + QString::number(
                        currentTrip.size()) + "\n";
            report += "Total Distance Traveled: " + QString::number(
                        graph.getPathWeight(currentTrip)) + "\n";
            ui->tripReportArea->setText(report);
            prePlannedTripIndex = 0;
            userPlannedTrip = true;
            currentTripIndex = -1;
        }
        else
        {
            sceneForTrip->clear();
            drawEdges();
            QPen pen;
            pen.setColor(Qt::darkRed);
            pen.setWidth(3);
            sceneForTrip->addEllipse(
                        graph[ui->startingStadiumBox->currentIndex()].getX()-4,
                    graph[ui->startingStadiumBox->currentIndex()].getY()-4,
                    11,11,pen,QBrush(Qt::darkRed));
            prePlannedTripIndex++;
            for (int i=1;i<=prePlannedTripIndex;i++)
            {
                sceneForTrip->addLine(graph[currentTrip[i-1]].getX(),
                        graph[currentTrip[i-1]].getY(),
                        graph[currentTrip[i]].getX(),
                        graph[currentTrip[i]].getY(),pen);
            }

        }

    }


}


/******************************************************************************
 *
 *  Mutator on_finishTripButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This current trip has been finished
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The current trip is marked as finished and the report area is filled
 *****************************************************************************/
void MainWindow::on_finishTripButton_clicked()
{
    if (!userPlannedTrip)
        return;
    sceneForTrip->clear();
    ui->nextStopBox->clear();
    drawEdges();
    int totalDistance = 0;
    currentTripIndex = -1;
    if (currentTrip.size()<=1)
    {
        ui->tripReportArea->setText(
                    "N/A\n"
                    "Please traverse through multiple stadiums on your trip!");
        return;
    }
    QPen penForStadiums;
    penForStadiums.setColor(Qt::darkRed);
    penForStadiums.setWidth(3);
    QPen penForEdges;
    penForEdges.setColor(Qt::darkRed);
    penForEdges.setWidth(3);
    for (int i = 1; i<currentTrip.size();i++)
    {
        if (i==1)
        {
            sceneForTrip->addEllipse(
                        graph[currentTrip[0]].getX()-4,
                    graph[currentTrip[0]].getY()-4,11,11,
                    penForStadiums,QBrush(Qt::darkRed));
        }

        sceneForTrip->addEllipse(graph[currentTrip[i]].getX()-4,
                graph[currentTrip[i]].getY()-4,11,11,penForStadiums);
        sceneForTrip->addLine(graph[currentTrip[i-1]].getX(),
                              graph[currentTrip[i-1]].getY(),
                              graph[currentTrip[i]].getX(),
                              graph[currentTrip[i]].getY(),penForEdges);
        if (i == currentTrip.size()-1)
            sceneForTrip->addEllipse(graph[currentTrip[i]].getX()-4,
                    graph[currentTrip[i]].getY()-4,11,11,penForStadiums,
                    QBrush(Qt::darkRed));
        totalDistance += graph.getWeight(currentTrip[i],currentTrip[i-1]);
    }

    QString report;
    report += ui->fanBox->currentText();
    report += "\n";
    report += "------------------------------------------\n";

    report += "Stadiums Visited:\n";
    for (int i = 0; i<currentTrip.size();i++)
    {
        report += QString::fromStdString(
                    graph[currentTrip[i]].getName()) + "\n";

    }
    report += "Number of Stadiums Visited: " + QString::number(
                currentTrip.size()) + "\n";
    report += "Total Distance Traveled: " + QString::number(
                totalDistance) + "\n";
    ui->tripReportArea->setText(report);


}


/******************************************************************************
 *
 *  Mutator on_tabWidget_currentChanged: Class MainWindow
 *_____________________________________________________________________________
 *  This current tab has been changed, calls force login if desired
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The user has been forced to log in if needed
 *****************************************************************************/
void MainWindow::on_tabWidget_currentChanged(int index)
//IN - the current index
{
    if (index >=2)
        forceLogin();
}

/******************************************************************************
 *
 *  Mutator on_buySouvenirButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This selected souvenir is bought. Fan is updated.
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    This selected souvenir has been bought
 *****************************************************************************/
void MainWindow::on_buySouvenirButton_clicked()
{
    if (currentTripIndex == -1)
        return;
    int souvenirIndex = 0;
    souvenirIndex = ui->souvenirPurchaseBox->currentIndex();
    int fanIndex = 0;
    fanIndex = ui->fanBox->currentIndex();
    fanList[fanIndex].addProduct(souvenirList[souvenirIndex]);
}

/******************************************************************************
 *
 *  Mutator on_souvenirModifyBox_currentIndexChanged: Class MainWindow
 *_____________________________________________________________________________
 *  The old values are changed when this slot is called.
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    This selected souvenir causes an update in the guis view
 *****************************************************************************/
void MainWindow::on_souvenirModifyBox_currentIndexChanged(int index)
//IN - the current index of the box
{
    ui->newSouvenirNameEntry->setText(QString::fromStdString(
                                          souvenirList[index]._name));
    ui->newSouvenirPriceEntry->setValue(souvenirList[index]._price);
}

/******************************************************************************
 *
 *  Mutator on_modifySouvenirButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  The new values are commited to the souvenir
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    This selected souvenir has been updated
 *****************************************************************************/
void MainWindow::on_modifySouvenirButton_clicked()
{
    string newName = ui->newSouvenirNameEntry->text().toStdString();
    if (newName == "")
        return;
    bool isWord = false;
    QRegExp regX2("[a-zA-Z][a-zA-Z ]+");
    isWord = regX2.exactMatch(ui->newSouvenirNameEntry->text());
    if (!isWord)
    {
        return;
    }
    double newPrice = ui->newSouvenirPriceEntry->value();
    int index = ui->souvenirModifyBox->currentIndex();
    souvenirList[index]._name = newName;
    souvenirList[index]._price = newPrice;
    buildSouvenirComboBox();
}

/******************************************************************************
 *
 *  Mutator on_removeSouvenirButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  The selected souvenir has been removed
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    This selected souvenir has been removed
 *****************************************************************************/
void MainWindow::on_removeSouvenirButton_clicked()
{
    if (souvenirList.size() == 0)
        return;
    int index = ui->souvenirRemoveBox->currentIndex();
    souvenirList.erase(souvenirList.begin() + index);
    buildSouvenirComboBox();
}

/******************************************************************************
 *
 *  Mutator on_addSouvenirButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  The new souvenir has been added.
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    This new souvenir has been added to the vector.
 *****************************************************************************/
void MainWindow::on_addSouvenirButton_clicked()
{
    string newName = ui->newSouvenirNameEntryAdd->text().toStdString();
    if (newName == "")
        return;
    bool isWord = false;
    QRegExp regX2("[a-zA-Z][a-zA-Z ]+");
    isWord = regX2.exactMatch(ui->newSouvenirNameEntryAdd->text());
    if (!isWord)
    {
        return;
    }
    double newPrice = ui->newSouvenirPriceEntryAdd->value();
    souvenirList.push_back(Product(newName,newPrice));
    buildSouvenirComboBox();
    ui->newSouvenirNameEntryAdd->setText("");
    ui->newSouvenirPriceEntryAdd->setValue(0.00);
}


/******************************************************************************
 *
 *  Mutator on_addFanButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  The new fan is added
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The fan vector is updated
 *****************************************************************************/
void MainWindow::on_addFanButton_clicked()
{
    string newName = ui->fanNameEntry->text().toStdString();
    if (newName == "")
        return;
    bool isWord = false;
    QRegExp regX2("[a-zA-Z][a-zA-Z ]+");
    isWord = regX2.exactMatch(ui->fanNameEntry->text());
    if (!isWord)
    {
        return;
    }
    fanList.push_back(Fan(newName));
    ui->fanNameEntry->clear();
    buildFanComboBox();
}

/******************************************************************************
 *
 *  Mutator on_souvenirReportButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Slot causes the souvenir report to be displayed on the gui
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The souvenir report is displayed on the gui
 *****************************************************************************/
void MainWindow::on_souvenirReportButton_clicked()
{
    ui->sourvenirReportArea->clear();
    string display = "";
    for (int i=0;i<fanList.size();i++)
    {
        display += fanList[i].getPurchases() + "\n";
    }
    ui->sourvenirReportArea->setText(QString::fromStdString(display));
}

/******************************************************************************
 *
 *  Mutator on_commitModificationsButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This commits modifications to the stadium
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The stadium has been updated
 *****************************************************************************/
void MainWindow::on_commitModificationsButton_clicked()
{


    int index = ui->modifyStadiumBox->currentIndex();
    if (index > 29)
    {
        modifyProposed = true;
        index -= graph.size();
    }
    currentStadiumToModify = index;
    int valueIndex = ui->modifiedValueBox->currentIndex();

    bool isNum = false;
    QRegExp regX("\\d*");


    isNum = regX.exactMatch(ui->modifyStadiumNewValueEntry->text());

    switch (valueIndex)
    {
    case 0://team name
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        string newTeamName = ui->modifyStadiumNewValueEntry->text().
                toStdString();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setTeamName(newTeamName);
            break;
        }
        graph[currentStadiumToModify].setTeamName(newTeamName);
        break;
    }
    case 1:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        string newStreetAddress = ui->modifyStadiumNewValueEntry->
                text().toStdString();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].
                    setStreetAddress(newStreetAddress);
            break;
        }
        graph[currentStadiumToModify].setStreetAddress(newStreetAddress);
        break;
    }
    case 2:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        string newPhoneNumber = ui->modifyStadiumNewValueEntry->text().
                toStdString();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setPhoneNumber(
                        newPhoneNumber);
            break;
        }
        graph[currentStadiumToModify].setPhoneNumber(newPhoneNumber);
        break;
    }
    case 3:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        if (!isNum)
            break;
        int newCapacity = ui->modifyStadiumNewValueEntry->text().toInt();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setCapacity(newCapacity);
            break;
        }
        graph[currentStadiumToModify].setCapacity(newCapacity);
        break;
    }
    case 4:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        string newName = ui->modifyStadiumNewValueEntry->text().toStdString();
        if (modifyProposed)
        {
            cout << "Start";
            cout << currentStadiumToModify;
            plannedStadiums[currentStadiumToModify].setName(newName);
            cout << "Stop";
            break;
        }
        graph[currentStadiumToModify].setName(newName);
        break;
    }
    case 5:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        string newCity = ui->modifyStadiumNewValueEntry->text().toStdString();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setCity(newCity);
            break;
        }
        graph[currentStadiumToModify].setCity(newCity);
        break;
    }
    case 6:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        string newState = ui->modifyStadiumNewValueEntry->text().toStdString();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setState(newState);
            break;
        }
        graph[currentStadiumToModify].setState(newState);
        break;
    }
    case 7:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        string newZip = ui->modifyStadiumNewValueEntry->text().toStdString();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setZip(newZip);
            break;
        }
        graph[currentStadiumToModify].setZip(newZip);
        break;
    }
    case 8:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        string newMonth = ui->modifyStadiumNewValueEntry->text().toStdString();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setDate(newMonth,
                                                            plannedStadiums[currentStadiumToModify].getDay(),
                                                            plannedStadiums[currentStadiumToModify].getYear());
            break;
        }
        graph[currentStadiumToModify].setDate(newMonth,
                                              graph[currentStadiumToModify].
                                              getDay(),
                                              graph[currentStadiumToModify].
                                              getYear());
        break;
    }
    case 9:
    {

        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        if (!isNum)
            break;
        int newDay = ui->modifyStadiumNewValueEntry->text().toInt();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setDate(
                        plannedStadiums[currentStadiumToModify].getMonth(),
                        newDay,plannedStadiums[currentStadiumToModify].
                        getYear());
            break;
        }
        graph[currentStadiumToModify].setDate(graph[currentStadiumToModify].
                                              getMonth(),
                                              newDay,
                                              graph[currentStadiumToModify].
                                              getYear());
        break;
    }
    case 10:
    {
        if (ui->modifyStadiumNewValueEntry->text() == "")
            break;
        if (!isNum)
            break;
        int newYear = ui->modifyStadiumNewValueEntry->text().toInt();
        if (modifyProposed)
        {
            plannedStadiums[currentStadiumToModify].setDate(
                        plannedStadiums[currentStadiumToModify].getMonth(),
                        plannedStadiums[currentStadiumToModify].getDay(),
                                                            newYear);
            break;
        }
        graph[currentStadiumToModify].setDate(graph[currentStadiumToModify].
                                              getMonth(),
                                              graph[currentStadiumToModify].
                                              getDay(),
                                              newYear);
        break;
    }
    case 11:
    {
        if (ui->xCoordEntryModify->text() == "")
            break;
        if (modifyProposed)
        {
            int newXCoord = ui->xCoordEntryModify->text().toInt();
            int newYCoord = ui->yCoordEntryModify->text().toInt();
            plannedStadiums[currentStadiumToModify].setXCoord(newXCoord);
            plannedStadiums[currentStadiumToModify].setYCoord(newYCoord);
            break;
        }
        break;
    }
    default:
    {
        break;
    }
    }




    ui->addLocationButtonModify->setEnabled(false);
    ui->xCoordEntryModify->setEnabled(false);
    ui->yCoordEntryModify->setEnabled(false);
    ui->updateCoordinateButtonModify->setEnabled(false);
    ui->modifyStadiumNewValueEntry->setText("");
    ui->modifyStadiumOldValueEntry->setText("");
    ui->xCoordEntryModify->setText("");
    ui->yCoordEntryModify->setText("");
    scene->clear();
    generalScene->clear();
    buildComboBoxes();
    drawEdges();
    drawProposed();
    modifyProposed = false;
}

/******************************************************************************
 *
 *  Mutator on_modifyStadiumBox_currentIndexChanged: Class MainWindow
 *_____________________________________________________________________________
 *  This changes the possible options for modifying the stadium
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The stadium modification value box has been updated
 *****************************************************************************/
void MainWindow::on_modifyStadiumBox_currentIndexChanged(int index)
//IN - the current selected stadium
{
    if (index == -1)
        return;
    //Changes to modified Stadiums follow notes in doc

    modifyProposed = false;
    if (index > 29)
    {
        modifyProposed = true;
        index -= graph.size();
    }
    currentStadiumToModify = index;
    buildModifyValueComboBox();
}


/******************************************************************************
 *
 *  Mutator on_addLocationButtonModify_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This adds the desired stadium
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The desired stadium has been added
 *****************************************************************************/
void MainWindow::on_addLocationButtonModify_clicked()
{
    ui->mapArea->clearVectors();
    QMessageBox msgBox;
    msgBox.setText(
                "After clicking okay, click a point on the map.\n"
                "This point is where the proposed stadium will be.\n"
            "The coordinates will display in the box after clicking update.");
    msgBox.exec();
}

/******************************************************************************
 *
 *  Mutator on_updateCoordinateButtonModify_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This updates the coordinates
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The coordinates have been updated
 *****************************************************************************/
void MainWindow::on_updateCoordinateButtonModify_clicked()
{
    if (ui->mapArea->xCoords.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText(
                    "You must click a point on the map to add the stadium.\n"
                       "Please close this window and click on the map again.\n"
                       "Afterwards, try and update the coordinates again.");
        msgBox.exec();
        return;
    }
    int xCoord = ui->mapArea->xCoords[0];
    int yCoord = ui->mapArea->yCoords[0];
    ui->xCoordEntryModify->setText(QString::number(xCoord));
    ui->yCoordEntryModify->setText(QString::number(yCoord));
}

/******************************************************************************
 *
 *  Mutator on_removeStadiumButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This removes the selected stadium
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The selected stadium has been removed
 *****************************************************************************/
void MainWindow::on_removeStadiumButton_clicked()
{
    int index = ui->stadiumToRemoveBox->currentIndex();
    if (index <0)
        return;
    plannedStadiums.erase(plannedStadiums.begin() + index);
    buildComboBoxes();
    scene->clear();
    generalScene->clear();
    drawEdges();
    drawProposed();

}

/******************************************************************************
 *
 *  Mutator on_distanceThroughAllButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This calculates and displays the distance through all stadiums
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Map and display box have been updated
 *****************************************************************************/
void MainWindow::on_distanceThroughAllButton_clicked()
{
    int index = ui->stadiumForAllBox->currentIndex();
    bool americanLeague = ui->americanLeagueFilter->isChecked();
    bool nationalLeague = ui->nationalLeagueFilter->isChecked();
    bool all = ui->allStadiumsFilter->isChecked();

    vector<int> path;
    bool allowed[30];
    for (int i=0;i<30;i++)
        allowed[i]=false;
    if (all)
        path = graph.minPathV1(index);
    else
    {
        for (int i=0;i<graph.size();i++)
        {
            if (americanLeague)
            {
                allowed[i] = graph[i].isAmerican();
            }
            else if (nationalLeague)
            {
                allowed[i] = !graph[i].isAmerican();
            }
        }
        path = graph.minPathV2(index,allowed);
    }

    int totalDistance = graph.getPathWeight(path);
    generalScene->clear();
    drawEdges();
    drawProposed();
    QPen pen;
    pen.setColor(Qt::darkRed);
    pen.setWidth(3);
    generalScene->addEllipse(graph[index].getX()-4,
                             graph[index].getY()-4,11,11,
                             pen,QBrush(Qt::darkRed));
    string display;
    display += "Distance: " + to_string(totalDistance) +
            ", Number of Stadiums: " + to_string(path.size()) + "\n\nOrder:\n";

    for (size_t i = 0; i < path.size()-1;i++)
    {
        generalScene->addLine(graph[path[i]].getX(),
                graph[path[i]].getY(),graph[path[i+1]].getX(),
                graph[path[i+1]].getY(),pen);
        display += graph[path[i]].getName() + "-->";
    }
    generalScene->addEllipse(graph[path.back()].getX()-4,
            graph[path.back()].getY()-4,11,11,pen,QBrush(Qt::darkRed));
    display += graph[path.back()].getName() + "\n";


    ui->distanceThroughAllArea->setText(QString::fromStdString(display));
}

/******************************************************************************
 *
 *  Mutator on_getStadiumList_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  This displays the selected list in the above text area
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Text area has been updated
 *****************************************************************************/
void MainWindow::on_getStadiumList_clicked()
{

    int currentIndex = ui->listOptionsBox->currentIndex() + 1;
    ui->sourvenirReportArea->clear();
    switch(currentIndex)
    {
    case 1:
    {
        ui->sourvenirReportArea->setText(
                    QString::fromStdString(print(stadium_list())));
        break;
    }
    case 2:
    {
        ui->sourvenirReportArea->setText(
                    QString::fromStdString(print(major_league_list())));
        break;
    }
    case 3:
    {
        ui->sourvenirReportArea->setText(
                    QString::fromStdString(print(american_list())));
        break;
    }
    case 4:
    {
        ui->sourvenirReportArea->setText(
                    QString::fromStdString(print(national_list())));
        break;
    }
    case 5:
    {
        ui->sourvenirReportArea->setText(
                    QString::fromStdString(print(grass_list())));
        break;
    }
    case 6:
    {
        ui->sourvenirReportArea->setText(
                    QString::fromStdString(print(date_opened_list())));
        break;
    }
    default:
        break;
    }
}
