/******************************************************************************
 *  AUTHOR         : Seongkyoo Maeng,
 *  Project #2     : I Love Baseball
 *  CLASS          : CS 008
 *  DUE DATE       : 06/02/2020
 ******************************************************************************/

#include "stadium.h"
#include <sstream>

Stadium::Stadium( ) : _name(""), _team_name(""), _street_address(""), _city(""),
                      _state(""), _phone_number("") {}

/**************************************************************
*  * Stadium(bool americanLeagueTeam, string name, string team, string street,
            string city,string state, string zip, string number, string m,
            int d,int y, int cap, int xCoord, int yCoord);
* ____________________________________________________________
* Constructor
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
*              americanLeagueTeam (bool)
*              name (string)
*              team (string)
*              street (string)
*              city (string)
*              state (string)
*              zip (string)
*              number (stirng)
*              m (string)
*              d (int)
*              y (int)
*              cap (int)
*              xCoord (int)
*              yCoord (int)
* POST-CONDITIONS
* -a stadium object is constructed with the given values
***************************************************************/
Stadium::Stadium(bool americanLeagueTeam, bool grass, string name,
                 string team, string street, string city,
        string state, string zip, string number, string m, int d,
        int y, int cap, int xCoord, int yCoord)
{
    _name = name, _team_name = team, _street_address = street, _city = city;
    _state = state, _zip = zip, _phone_number = number, _month = m, _day = d;
    _year = y, _capacity = cap,  _xCoord = xCoord, _yCoord = yCoord;
    _americanLeagueTeam = americanLeagueTeam, _grass = grass;
}

/**************
 ** MUTATOR **
***************/

/**************************************************************
* setName(string name);
* ____________________________________________________________
* Mutator; set the stadium name with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* name (string) //IN - the stadium name
* POST-CONDITIONS
* -the stadium name is set with given value
***************************************************************/
void Stadium::setName(string name) { _name = name; }

/**************************************************************
* setTeamName(string team);
* ____________________________________________________________
* Mutator; set the stadium team name with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* team (string) //IN - the stadium team name
* POST-CONDITIONS
* -the stadium team name is set with given value
***************************************************************/
void Stadium::setTeamName(string team) { _team_name = team; }

/**************************************************************
* setStreetAddress(string street);
* ____________________________________________________________
* Mutator; set the stadium street name with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* street (string) //IN - the stadium street name
* POST-CONDITIONS
* -the stadium street name is set with given value
***************************************************************/
void Stadium::setStreetAddress(string street) { _street_address = street; }

/**************************************************************
* setCity(string city);
* ____________________________________________________________
* Mutator; set the stadium city with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* city (string) //IN - the stadium city
* POST-CONDITIONS
* -the stadium city is set with given value
***************************************************************/
void Stadium::setCity(string city) { _city = city; }

/**************************************************************
* setState(string state);
* ____________________________________________________________
* Mutator; set the stadium state with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* state (string) //IN - the stadium state
* POST-CONDITIONS
* -the stadium state is set with given value
***************************************************************/
void Stadium::setState(string state) { _state = state; }

/**************************************************************
* setZip(string zip);
* ____________________________________________________________
* Mutator; set the stadium zip with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* zip (string) //IN - the stadium zip
* POST-CONDITIONS
* -the stadium zip is set with given value
***************************************************************/
void Stadium::setZip(string zip) { _zip = zip; }

/**************************************************************
* setPhoneNumber(string number);
* ____________________________________________________________
* Mutator; set the stadium number with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* number (string) //IN - the stadium number
* POST-CONDITIONS
* -the stadium number is set with given value
***************************************************************/
void Stadium::setPhoneNumber(string number) { _phone_number = number; }

/**************************************************************
* setDate(string m , int d , int y);
* ____________________________________________________________
* Mutator; set the stadium date with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* m(int) //IN - the month of the date
* d(int) //IN - the day of the date
* y(int) //IN - the year of the date
* POST-CONDITIONS
* -the stadium date is set with given value
***************************************************************/
void Stadium::setDate(string m, int d, int y) { _month = m, _day = d, _year = y; }

/**************************************************************
* setCapacity(int capacity);
* ____________________________________________________________
* Mutator; set the stadium capacity with the given string
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* capacity(string) //IN - the stadium capacity
* POST-CONDITIONS
* -the stadium capacity is set with given value
***************************************************************/
void Stadium::setCapacity(int capacity) { _capacity = capacity; }

/**************************************************************
* setXCoord(int xCoord);
* ____________________________________________________________
* Mutator; set the stadium x cooridinate with the given value
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* xCoord (string) //IN - the x coordinate
* POST-CONDITIONS
* -the stadium x coordinate is set with given value
***************************************************************/
void Stadium::setXCoord(int xCoord) { _xCoord = xCoord; }

/**************************************************************
* setYCoord(int yCoord);
* ____________________________________________________________
* Mutator; set the stadium y cooridinate with the given value
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* yCoord (string) //IN - the y coordinate
* POST-CONDITIONS
* -the stadium y coordinate is set with given value
***************************************************************/
void Stadium::setYCoord(int yCoord) { _yCoord = yCoord; }

/**************************************************************
* setAmericanLeague(bool americanLeagueTeam);
* ____________________________________________________________
* Mutator; set the bool americanLeagueTeam with the given value
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* americanLeagueTeam (bool) //IN - the bool
* POST-CONDITIONS
* -the status is set with given value
***************************************************************/
void Stadium::setAmericanLeague(bool americanLeagueTeam) {
    _americanLeagueTeam = americanLeagueTeam;}

/**************************************************************
* setGrass(bool grass);
* ____________________________________________________________
* Mutator; set the bool grass with the given value
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* grass (bool) //IN - the bool
* POST-CONDITIONS
* -the status is set with given value
***************************************************************/
void Stadium::setGrass(bool grass) { _grass = grass; }


/***************
 ** ACCESSOR **
****************/

/*******************************************
 * getName();
 * Accessor; get the stadium name
 * Pre-Condition : none
 * Post-Condition: return to the string of name
 ******************************************/
string Stadium::getName( ) const { return _name; }

/*******************************************
 * getTeam();
 * Accessor; get the stadium team
 * Pre-Condition : none
 * Post-Condition: return to the string of team
 ******************************************/
string Stadium::getTeamName( ) const { return _team_name; }

/*******************************************
 * getStreetAddress();
 * Accessor; get the stadium street address
 * Pre-Condition : none
 * Post-Condition: return to the string of the street address
 ******************************************/
string Stadium::getStreetAddress( ) const { return _street_address; }

/*******************************************
 * getCity();
 * Accessor; get the stadium city
 * Pre-Condition : none
 * Post-Condition: return to the string of the city
 ******************************************/
string Stadium::getCity( ) const { return _city; }

/*******************************************
 * getState();
 * Accessor; get the stadium state
 * Pre-Condition : none
 * Post-Condition: return to the  string of the state
 ******************************************/
string Stadium::getState( ) const { return _state; }

/*******************************************
 * getZip();
 * Accessor; get the stadium zip
 * Pre-Condition : none
 * Post-Condition: return to the  string of the zip
 ******************************************/
string Stadium::getZip( ) const { return _zip; }

/*******************************************
 * getPhoneNumber();
 * Accessor; get the stadium phone number
 * Pre-Condition : none
 * Post-Condition: return to the  string of phone number
 ******************************************/
string Stadium::getPhoneNumber( ) const { return _phone_number; }

/*******************************************
 * getDate(string m, int d, int y);
 * Accessor; get the stadium built date
 * Pre-Condition : m(int) //IN - the month of the date
 *              d(int) //IN - the day of the date
 *              y(int) //IN - the year of the date
 * Post-Condition none
 ******************************************/
void Stadium::getDate(string &m, int& d, int& y) const {
    m = _month, d = _day, y = _year; }

/*******************************************
 * getCapacity();
 * Accessor; get the stadium capacity
 * Pre-Condition : none
 * Post-Condition return to the int of capacity
 ******************************************/
int Stadium::getCapacity( ) const { return _capacity; }

/*******************************************
 * getX();
 * Accessor; get the stadium x coordinate
 * Pre-Condition : none
 * Post-Condition return to the int of the x coordinate
 ******************************************/
int Stadium::getX( ) const { return _xCoord; }

/*******************************************
 * getY();
 * Accessor; get the stadium y coordinate
 * Pre-Condition :  none
 * Post-Condition return to the int of the y coordinate
 ******************************************/
int Stadium::getY( ) const { return _yCoord; }

/*******************************************
 * isAmerican()
 * Accessor; check if the stadium is an American League Team
 * Pre-Condition :  none
 * Post-Condition return to true if the stadium is an American League Team
 ******************************************/
bool Stadium::isAmerican() const { return _americanLeagueTeam;}

/*******************************************
 * isGrass()
 * Accessor; check if the stadium has grass surface
 * Pre-Condition :  none
 * Post-Condition return to true if the stadium has grass surface
 ******************************************/
bool Stadium::isGrass( ) const { return _grass; }

/***************
 ** OPERATORS **
****************/

/*******************************************
 * operator == (const Stadium& RHS)
 * Operator; Check if two stadiums are the same
 * Pre-Condition :  RHS (Stadium&) //IN - another stadium
 * Post-Condition return to true if they are the same
 ******************************************/
bool Stadium::operator == (const Stadium& RHS) {
    return(_name.compare(RHS.getName()) == 0); }

/*******************************************
 * operator != (const Stadium& RHS)
 * Operator; Check if two stadiums are differnet
 * Pre-Condition :  RHS (Stadium&) //IN - another stadium
 * Post-Condition return to true if they are different
 ******************************************/
bool Stadium::operator != (const Stadium& RHS) {
    return(_name.compare(RHS.getName()) != 0); }

/*******************************************
 * operator > (const Stadium& RHS)
 * Operator; Check if LHS is greater than RHS
 * Pre-Condition :  RHS (Stadium&) //IN - another stadium
 * Post-Condition return to true if this stadium's name is greater than RHS
 ******************************************/
bool Stadium::operator > (const Stadium& RHS) {
    return(_name.compare(RHS.getName()) > 0); }

/*******************************************
 * bool Stadium::greater_than_name(const Stadium& RHS)
 * Operator; Check if LHS is greater than RHS
 * Pre-Condition :  RHS (Stadium&) //IN - another stadium
 * Post-Condition return to true if this stadium's name is greater than RHS
 ******************************************/
bool Stadium::greater_than_name(const Stadium& RHS) {
    return(_team_name.compare(RHS.getTeamName()) > 0); }

/*******************************************
 * bool Stadium::greater_than_date(const Stadium& RHS)
 * Operator; Check if LHS's date is greater than RHS's date
 * Pre-Condition :  RHS (Stadium&) //IN - another stadium
 * Post-Condition return to true if this stadium's date is greater than RHS
 ******************************************/
bool Stadium::greater_than_date(const Stadium& RHS)
{
    if(_year > RHS._year)
        return true;
    else if(_year == RHS._year)
    {
        if(_month > RHS._month)
            return true;
        else if(_month == RHS._month)
        {
            if(_day > RHS._day)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;

}

/*******************************************
 * friend ostream& operator <<(ostream& outs, const Stadium& print)
 * Operator: return ostream to output the product name and price
 * Pre-Condition : ostream& outs //IN - the ostream
 *              print (Stadium&) //IN - the stadium
 * Post-Condition return to the ostream
 ******************************************/
ostream& operator << (ostream& outs, const Stadium& print)
{
    outs << print.getName( );
    return outs;
}

/*******************************************
 * friend instream& operator >>(instream& ins, const Stadium& input)
 * Operator: return istream to take input from a text file
 *
 * Pre-Condition : istream& ins //IN - the instream
 *              input (Stadium&) //IN - the input
 * Post-Condition return to the istream
 ******************************************/
istream& operator >> (istream& ins, Stadium& input)
{
    string name, team, address, city, state, zip, number, month,
            league, grass_surface;
    int day, year, capacity, x, y;
    bool americanLeague, grass;

    ins >> league;
    if (league == "American")
        americanLeague = true;
    else
        americanLeague = false;

    ins >> grass_surface;
    if(grass_surface == "Grass Surface")
        grass = true;
    else
        grass = false;

    ins >> name;
    ins >> team;
    ins >> address;
    ins >> city >> state >> zip;
    ins >> number;
    ins >> month >> day >> year;
    ins >> capacity;
    ins >> x >> y;


    input = Stadium(americanLeague, grass, name, team, address,
                    city, state, zip, number, month, day, year, capacity, x,
                    y);

    return ins;
}

/*******************************************
 * print info();
 * Output function; print the infomation of the stadium
 * Pre-Condition :  none
 * Post-Condition The info is printed
 ******************************************/
string Stadium::print_info( )
{
    string text;
    if (isAmerican())
        text += "American League\n";
    else
        text += "National League\n";

    if(isGrass( ))
        text += "Grass Surface\n";

    text+= _name + "\n";
    text+= _team_name + "\n";
    text+= _street_address + "," + "\n";
    text+= _city + ", " + _state + " " + _zip + "\n";
    text+=  _phone_number + "\n";
    text+= "Opened - " + _month + " " + to_string(_day) + ", " +
            to_string(_year) + "\n";
    text += "Capacity - " + to_string(_capacity) + "\n";
    return text;
}
