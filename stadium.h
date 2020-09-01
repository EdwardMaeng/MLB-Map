#ifndef STADIUM_H
#define STADIUM_H

/******************************************************************************
 *  AUTHOR         : Jousha McDermott, Seongkyoo Maeng, Chak Hei Tin
 *  Project #2     : I Love Baseball
 *  CLASS          : CS 008
 *  DUE DATE       : 06/02/2020
 ******************************************************************************/

#include <iostream>
#include <string>

using namespace  std;

/*******************************************
 * class Stadium
 * - This class creates an Stadium object which
 * represents a stadium on the map.
 ******************************************/

class Stadium
{
public:
    /******************
     ** CONSTRUCTORS **
    *******************/
    Stadium( );
    Stadium(bool americanLeagueTeam, bool grass, string name, string team,
            string street,
            string city,string state, string zip, string number, string m,
            int d,int y, int cap, int xCoord, int yCoord);

    /**************
     ** MUTATOR **
    ***************/
    void setName(string name);
    void setTeamName(string team);
    void setStreetAddress(string street);
    void setCity(string city);
    void setState(string state);
    void setZip(string zip);
    void setPhoneNumber(string number);
    void setDate(string m, int d, int y);
    void setCapacity(int capacity);
    void setXCoord(int xCoord);
    void setYCoord(int yCoord);
    void setAmericanLeague(bool americanLeagueTeam);
    void setGrass(bool grass);


    /***************
     ** ACCESSOR **
    ****************/
    string getName( ) const;
    string getTeamName( ) const;
    string getStreetAddress( ) const;
    string getCity( ) const;
    string getState( ) const;
    string getZip( ) const;
    string getPhoneNumber( ) const;
    void getDate(string &m, int& d, int& y) const;
    int getCapacity( ) const;
    int getX( ) const;
    int getY( ) const;
    bool isAmerican() const;
    bool isGrass( ) const;
    string getMonth(){return _month;}
    int getDay(){return _day;}
    int getYear(){return _year;}

    /****************
     ** OPERATORS **
    *****************/
    bool operator == (const Stadium& RHS);
    bool operator != (const Stadium& RHS);
    bool operator > (const Stadium& RHS);
    bool greater_than_name(const Stadium& RHS);
    bool greater_than_date(const Stadium& RHS);

    /**********************
     ** FRIEND OPERATORS **
    ***********************/
    friend ostream& operator << (ostream& outs, const Stadium& print);
    friend istream& operator >> (istream& ins, Stadium& input);

    /*********************
     ** PRINT FUNCTION **
    **********************/
    string print_info( );


private:
    string _name;             // Stadium's name
    string _team_name;        // Stadium's team
    string _street_address;   // Stadium's stree address
    string _city, _state;     // Stadium's city + state
    string _zip;              // Stadium's zip code
    string _phone_number;     // Stadium's number #
    string _month;            // Stadium's opened date
    int _day, _year;          // Stadium's opened date
    int _capacity;            // Stadium's capacity
    int _xCoord;              // Stadium's X Coord from top left of map
    int _yCoord;              // Stadium's X Coord from top left of map
    bool _americanLeagueTeam; // True iff stadium is American
    bool _grass;              // True iff stadium has grass surface

};

/******************
 ** CONSTRUCTORS **
*******************/

/*******************************************
 * Stadium();
 * Constructor: Constructs Stadium object
 * Parameters : none
 * Return     : none
 ******************************************/

/*******************************************
 * Stadium(bool americanLeagueTeam, string name, string team, string street,
            string city,string state, string zip, string number, string m,
            int d,int y, int cap, int xCoord, int yCoord);
 * Constructor: Constructs Stadium object with given attributes
 * Parameters : americanLeagueTeam (bool)
 *              name (string)
 *              team (string)
 *              street (string)
 *              city (string)
 *              state (string)
 *              zip (string)
 *              number (stirng)
 *              m (string)
 *              d (int)
 * \            y (int)
 *              cap (int)
 *              xCoord (int)
 *              yCoord (int)
 * Return     : none
 ******************************************/

/**************
 ** MUTATOR **
***************/

/*******************************************
 * setName(string name);
 * Mutator; set the stadium name with the given string
 * Parameters : name (string) //IN - the stadium name
 * Return     : none
 ******************************************/

/*******************************************
 * setTeam(string team);
 * Mutator; set the stadium team with the given string
 * Parameters : team (string) //IN - the stadium team
 * Return     : none
 ******************************************/

/*******************************************
 * setName(string name);
 * Mutator; set the stadium name with the given string
 * Parameters : name (string) //IN - the stadium name
 * Return     : none
 ******************************************/

/*******************************************
 * setStreetAddress(string street);
 * Mutator; set the stadium street address with the given string
 * Parameters : stress (string) //IN - the stadium address
 * Return     : none
 ******************************************/

/*******************************************
 * setCity(string city);
 * Mutator; set the stadium city with the given string
 * Parameters : city (string) //IN - the stadium city
 * Return     : none
 ******************************************/

/*******************************************
 * setState(string name);
 * Mutator; set the stadium state with the given string
 * Parameters : state (string) //IN - the stadium state
 * Return     : none
 ******************************************/

/*******************************************
 * setZip(string zip);
 * Mutator; set the stadium zip with the given string
 * Parameters : zip (string) //IN - the stadium zip
 * Return     : none
 ******************************************/

/*******************************************
 * setPhoneNumber(string number);
 * Mutator; set the stadium phone number with the given string
 * Parameters : number (string) //IN - the stadium phone number
 * Return     : none
 ******************************************/

/*******************************************
 * setDate(int m, int d, int y);
 * Mutator; set the stadium built date with the given string
 * Parameters : m(int) //IN - the month of the date
 *              d(int) //IN - the day of the date
 *              y(int) //IN - the year of the date
 * Return     : none
 ******************************************/

/*******************************************
 * setCapacity(int capacity);
 * Mutator; set the stadium capacity with the given string
 * Parameters : capacity (string) //IN - the stadium capacity
 * Return     : none
 ******************************************/

/*******************************************
 * setxCoord(int xCoord);
 * Mutator; set the stadium x coordinate with the given string
 * Parameters : xCoord (string) //IN - the xCoord
 * Return     : none
 ******************************************/

/*******************************************
 * setyCoord(int yCoord);
 * Mutator; set the stadium y coordinate with the given string
 * Parameters : yCoord (string) //IN - the yCoord
 * Return     : none
 ******************************************/

/*******************************************
 * setAmericanLeague(bool americanLeagueTeam);
 * Mutator; set the stadium to an American League Team
 * Parameters : ameicanLeagueTeam (bool) //IN - the bool to indicate ALT
 * Return     : none
 ******************************************/

/***************
 ** ACCESSOR **
****************/

/*******************************************
 * getName();
 * Accessor; get the stadium name
 * Parameters : none
 * Return     : return to the string of name
 ******************************************/

/*******************************************
 * getTeam();
 * Accessor; get the stadium team
 * Parameters : none
 * Return     : return to the string of team
 ******************************************/

/*******************************************
 * getStreetAddress();
 * Accessor; get the stadium street address
 * Parameters : none
 * Return     : return to the string of the street address
 ******************************************/

/*******************************************
 * getCity();
 * Accessor; get the stadium city
 * Parameters : none
 * Return     : return to the string of the city
 ******************************************/

/*******************************************
 * getState();
 * Accessor; get the stadium state
 * Parameters : none
 * Return     : string of the state
 ******************************************/

/*******************************************
 * getZip();
 * Accessor; get the stadium zip
 * Parameters : none
 * Return     : string of the zip
 ******************************************/

/*******************************************
 * getPhoneNumber();
 * Accessor; get the stadium phone number
 * Parameters : none
 * Return     : string of phone number
 ******************************************/

/*******************************************
 * getDate(string m, int d, int y);
 * Accessor; get the stadium built date
 * Parameters : m(int) //IN - the month of the date
 *              d(int) //IN - the day of the date
 *              y(int) //IN - the year of the date
 * Return     : none
 ******************************************/

/*******************************************
 * getCapacity();
 * Accessor; get the stadium capacity
 * Parameters : none
 * Return     : int of capacity
 ******************************************/

/*******************************************
 * getX();
 * Accessor; get the stadium x coordinate
 * Parameters : none
 * Return     : int of the x coordinate
 ******************************************/

/*******************************************
 * getY();
 * Accessor; get the stadium y coordinate
 * Parameters :  none
 * Return     : int of the y coordinate
 ******************************************/

/*******************************************
 * isAmerican()
 * Accessor; check if the stadium is an American League Team
 * Parameters :  none
 * Return     : true if the stadium is an American League Team
 ******************************************/

/****************
 ** OPERATORS **
*****************/

/*******************************************
 * operator == (const Stadium& RHS)
 * Operator; Check if two stadiums are the same
 * Parameters :  RHS (Stadium&) //IN - another stadium
 * Return     : true if they are the same
 ******************************************/

/*******************************************
 * operator != (const Stadium& RHS)
 * Operator; Check if two stadiums are differnet
 * Parameters :  RHS (Stadium&) //IN - another stadium
 * Return     : true if they are different
 ******************************************/

/*******************************************
 * friend ostream& operator <<(ostream& outs, const Stadium& print)
 * Operator: return ostream to output the product name and price
 * Parameters : ostream& outs //IN - the ostream
 *              print (Stadium&) //IN - the stadium
 * Return     : ostream
 ******************************************/

/*******************************************
 * friend instream& operator <<(instream& ins, const Stadium& input)
 * Operator: return istream to take input from a text file
 *
 * Parameters : istream& ins //IN - the instream
 *              input (Stadium&) //IN - the input
 * Return     : istream
 ******************************************/

/*******************************************
 * print info();
 * Output function; print the infomation of the stadium
 * Parameters :  none
 * Return     : none
 ******************************************/
#endif // STADIUM_H
