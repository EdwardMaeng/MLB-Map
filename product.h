#ifndef PRODUCT_H
#define PRODUCT_H

/******************************************************************************
 *  AUTHOR         : Jousha McDermott, Seongkyoo Maeng, Chak Hei Tin
 *  Project #2     : I Love Baseball
 *  CLASS          : CS 008
 *  DUE DATE       : 06/02/2020
 ******************************************************************************/

#include <string>
#include <iostream>
#include <iomanip>
#include "stadium.h"
#include <sstream>

using namespace std;

/*******************************************
 * struct Product
 * - This struct creates an product object which
 * represents a souvenir bought by abaseball fan.
 * It has two attributes:
 * the product name and price
 ******************************************/
struct Product
{
    //CONSTRUCTOR
    /*******************************************
     * Product();
     * Constructor: Constructs Product object
     * Parameters : none
     * Return     : none
     ******************************************/
    Product():_name(""),_price(0.0){}

    /*******************************************
     * Product(string n, double p);
     * Constructor: Constructs Product object
     * Parameters : n (string) //IN- name of the product
     *              p (double) //IN - price of the product
     * Return     : none
     ******************************************/
    Product(string n, double p):_name(n),_price(p){}

    //OVERLOADED OPERATOR

    /*******************************************
     * friend ostream& operator <<(ostream& outs, const Product& i)
     * Operator: return ostream to output the product name and price
     * Parameters : ostream& outs //IN - the ostream
     *              i (Product&) //IN - the product
     * Return     : none
     ******************************************/
    friend ostream& operator <<(ostream& outs, const Product& i)
    {
        int size = i._name.length();
        int width = abs(25- size);
        outs << i._name << setw(width) << "$" <<setprecision(2)<<fixed
             << i._price  <<" \n";
        return outs;
    }

    /*******************************************
     * friend instream& operator <<(instream& ins, const Product& i)
     * Operator: return istream to take input from a text file
     *
     * Parameters : istream& ins //IN - the instream
     *              i (Product&) //IN - the product
     * Return     : none
     ******************************************/
    friend istream& operator >>(istream& ins, Product &i)
    {
        string name;
        double price;
        ins >> name;
        ins >> price;
        i= Product(name,price);
        return ins;
    }

    /*******************************************
     * operator == (const Product & p) const
     * Operator: check if two products are the same
     * Parameters : p (Prodcut) //IN- the product
     * Return     : true if the two products are the same
     ******************************************/
    bool operator == (const Product & p) const
    {
        return ((_name == p._name) && (_price == p._price));
    }

    //ACCESSOR

    /*******************************************
     * priceString()
     * Accessor: get the string of the price of the product
     * Parameters : none
     * Return     : a string of the price of the product
     ******************************************/
    string priceString()
    {
        std::ostringstream out;
        out.precision(2);
        out << std::fixed << _price;
        return out.str();
    }

    //VARIABLES
    string _name;
    double _price;

};



#endif // PRODUCT_H
