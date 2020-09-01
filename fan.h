#ifndef FAN_H
#define FAN_H

#include "product.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "stadium.h"
#include <vector>

/******************************************************************************
 *  AUTHOR         : Jousha McDermott, Seongkyoo Maeng, Chak Hei Tin
 *  Project #2     : I Love Baseball
 *  CLASS          : CS 008
 *  DUE DATE       : 06/02/2020
 ******************************************************************************/

/*******************************************
 * class Fan
 * - This class creates an Fan object which
 * represents a baseball fan. It has two attributes
 * the fan name and the vector of products bought
 ******************************************/

class Fan
{
public:
    //CONSTRUCTOR
    Fan();
    Fan(string name);

    //MUTATOR
    void addProduct(Product& p);

    //OVERLOADED OPERATOR
    friend istream& operator >>(istream& ins, Fan& i)
    {
        string fanName;
        string firstName;
        string lastName;
        string productName;
        string p1;
        string p2;
        double price;
        ins >> firstName >> lastName;
        ins >> p1>> p2;
        ins >> price;

        fanName = firstName + ' ' + lastName;
        productName = p1 + ' ' + p2;
        i= Fan(fanName);
        Product p = Product(productName, price);
        i.addProduct(p);
        return ins;
    }

    bool operator ==(const Fan& f);
    bool operator ==(Fan& f);
    bool operator !=(Fan& f);

    //ACCESSOR
    double total();
    string totalString();
    string name(){return _name;}
    vector <Product> souvenir(){return _souvenir;}
    string getPurchases();

private:
    string _name;
    vector <Product> _souvenir;
};

/*******************************************
 * Fan();
 * Constructor: Constructs Fan object
 * Parameters : none
 * Return     : none
 ******************************************/

/*******************************************
 * Fan(string name);
 * Constructor: Constructs Fan object
 * Parameters : name //IN - the string of name
 * Return     : none
 ******************************************/

/*******************************************
 * addProduct (Product& p)
 * Mutator: add product to the vector of the fan object
 * Parameters : p (Product&) //IN- the product
 * Return     : none
 ******************************************/

/*******************************************
 * operator ==(const Fan& f);
 * Operator: Check if two fans are the same object
 * Parameters : f (const Fan&) //IN - another fan object
 * Return     : true if two fan objects names are the same
 ******************************************/

/*******************************************
 * operator !=(Fan& f);
 * Operator: Check if two fans are not the same object
 * Parameters : f (const Fan&) //IN - another fan object
 * Return     : true if two fan objects names are not the same
 ******************************************/

/*******************************************
 * total();
 * Accessor: return to the total cost a fan object spent on souvenirs
 * Parameters : none
 * Return     : a value of total cost of a fan object spent
 ******************************************/

/*******************************************
 * totalString();
 * Accessor: return to a string of the total amount spent
 * Parameters : none
 * Return     : the outstream where output the string of total amoount spent
 ******************************************/

/*******************************************
 * getPurchase();
 * Accessor: return to a string of product name and price
 * Parameters : none
 * Return     : a string of products name and price
 *              which the fan object bought
 ******************************************/

#endif // FAN_H
