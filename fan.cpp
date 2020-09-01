#include "fan.h"
#include <sstream>

Fan::Fan()
{

}

/**************************************************************
* Fan::Fan(string n):_name(n)
* ____________________________________________________________
* Constructor
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* n (string) //IN -- the name of the fan object
* POST-CONDITIONS
* -a fan object is constructed with the given name
***************************************************************/
Fan::Fan(string n):_name(n)
{

}

/**************************************************************
* addProduct(Product &p)
* ____________________________________________________________
* Mutator; add product to the vector of the fan object
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* p (Product&) //IN -- the product object to be added
* POST-CONDITIONS
* -The product is added to the fan object's vector.
***************************************************************/
void Fan::addProduct(Product &p)
{
    _souvenir.push_back(p);
}

/**************************************************************
* operator==(const Fan &f)
* ____________________________________________________________
* Operator; Check if two fan objects are the same
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* f (const Fan&) //IN -- the other fan object
* POST-CONDITIONS
* -Return true if two fan objects' names are the same,
* false otherwise.
***************************************************************/
bool Fan::operator==(const Fan &f)
{
    return (this->_name == f._name);
}

/**************************************************************
* operator==(Fan &f)
* ____________________________________________________________
* Operator; Check if two fan objects are the same
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* f (const Fan&) //IN -- the other fan object
* POST-CONDITIONS
* -Return true if two fan objects' names are the same,
* false otherwise.
***************************************************************/
bool Fan::operator==(Fan &f)
{
    return (this->_name == f._name);
}

/**************************************************************
* operator==(Fan &f)
* ____________________________________________________________
* Operator; Check if two fan objects are not the same
* ___________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* f (const Fan&) //IN -- the other fan object
* POST-CONDITIONS
* -Return false if two fan objects' names are the same,
* true otherwise.
***************************************************************/
bool Fan::operator!=(Fan &f)
{
    return (this->_name != f._name);
}

/**************************************************************
* total()
* ____________________________________________________________
* Accessor; return to the total cost a fan object spent on souvenirs
* ___________________________________________________________
* PRE-CONDITIONS
* none
* POST-CONDITIONS
* -return to a value of total amount spent by the fan object
* on souvenirs
***************************************************************/
double Fan::total()
{
    double total = 0.0;
    for (int i=0; i<_souvenir.size(); i++)
    {
        total += _souvenir[i]._price;
    }
    return total;
}

/**************************************************************
* totalString()
* ____________________________________________________________
* Accessor; return to a string of the total amount spent
* ___________________________________________________________
* PRE-CONDITIONS
* none
* POST-CONDITIONS
* - the outstream where outputs the string of total amount spent
***************************************************************/
string Fan::totalString()
{
    double doubleTotal = total();
    std::ostringstream out;
    out.precision(2);
    out << std::fixed << doubleTotal;
    return out.str();
}

/**************************************************************
* getPurchase()
* ____________________________________________________________
* Accessor;  return to a string of product name and price
* ___________________________________________________________
* PRE-CONDITIONS
* none
* POST-CONDITIONS
* -a string of products name and price
*  which the fan object bought
***************************************************************/
string Fan::getPurchases()
{
    string retVal;
    if (_souvenir.size() == 0)
        return "";
    retVal += "---------------------------------------------";
    retVal += "------------------------------------------\n";
    retVal += _name + "\n";

    for (int i =0;i<_souvenir.size();i++)
    {
        retVal+= "Item Name: " + _souvenir[i]._name;
        retVal += ", Item Price: " + _souvenir[i].priceString() + "\n";
    }
    retVal += "Total: " + totalString();
    retVal += "\n";
    retVal += "------------------------------------------";
    retVal += "---------------------------------------------\n";
    return retVal;
}
