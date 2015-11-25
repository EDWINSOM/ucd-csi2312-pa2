//
// Created by marisa on 9/12/15.
//

#include "Point.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>


// iostream
using std::cout;
using std::endl;

// fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;

using namespace std;



namespace Clustering {


/*
 * Constructors
 */

// Default
// Constructors are initializing newly constructed objects
    Point::Point() {

        m_Dims = 2;
        m_values = new double[2];
    }

    Point::Point(unsigned d)
    {
        if (d == 0)
            d = 2;

        m_Dims = d;
        m_values = new double[m_Dims];
    }

// takes in n dimensions
// double * coordinates is an array of doubles
    Point::Point(unsigned dimensions, double *coordinates) {
        if (dimensions == 0)
            dimensions = 2;

        m_Dims = dimensions;
        m_values = new double[m_Dims];

        // copy double * coordinates into m_values
        for (int i = 0; i < m_Dims; i++) {
            m_values[i] = coordinates[i];
        }
    }



/*
 * The Big Three
 */

// Destructor
    Point::~Point() {

        delete[] m_values;
    }


// Copy constructor works on something that has already been created (exists already)
    Point::Point(const Point &existingPoint) {

        m_Dims = existingPoint.m_Dims;                // want same number of dimensions
        m_values = new double[m_Dims];

        for (int i = 0; i < m_Dims; i++)      // want to copy the values
        {
            m_values[i] = existingPoint.m_values[i];
        }
    }


// Overloaded assignment operator
// const argument so you don't modify what is being passed in
    Point &Point::operator=(const Point &rhs) {
        if (this == &rhs)                    // Prevents self-assignment
            return *this;

        else
            delete[] m_values;             // if calling Point already exists, clear member data

        m_Dims = rhs.m_Dims;
        m_values = new double[m_Dims];     // new set of member data, equal to member data of rhs

        for (int i = 0; i < m_Dims; i++) {
            m_values[i] = rhs.m_values[i];
        }

        return *this;                       // return calling Point
    }



/*
 * Accessor Member Functions
 */


// gets coordinate of dimension of interest
    double Point::getValue(unsigned dimension) const {

        if (dimension >= 1 && dimension <= m_Dims)
            return m_values[dimension - 1];

        else
        {
            cout << endl << "Invalid dimension for this Point. Terminating Program" << endl;
            exit(1);
        }

    }

// gets number of dimensions of a Point object
    unsigned Point::getDimension() const {

        if (this == nullptr)
            return 0;

        return m_Dims;
    }


// Overloaded [] index operator
// returns coordinate at index
    double &Point::operator[](unsigned index) {

        if (index < m_Dims)
           return m_values[index - 1];

        else
        {
            cout << endl << "This coordinate does not exist. Terminating Program." << endl;
            exit(1);
        }
    }


/*
 * Mutator Member Functions
 */

// set coordinate of dimension passed in
    void Point::setValue(unsigned dimension, double value) {

        if ((dimension >= 1) && (dimension <= m_Dims))
        {
            m_values[dimension-1] = value;
            return;
        }

        else
        {
            cout << endl << "Not a valid dimension" << endl;
            return;
        }

    }


/*
 * Functions
 */

/* Calculates distance between 2 points (the point calling the member function and the point passed in by reference)
   sqrt() is square root function defined in <cmath>
*/
    double Point::distanceTo(const Point &point2) {
        if (point2.m_Dims == m_Dims)                // both Points must have same number of dimensions
        {
            double sum = 0;

            for (int i = 0; i < m_Dims; i++) {
                double diff = m_values[i] - point2.m_values[i];     // coordinate-wise subtraction
                sum += (diff * diff);
            }

            return sqrt(sum);
        }

        else
        {
            cout << endl << "Points must have same number of dimensions. Returning 0." << endl;
            return 0.0;
        }


    }



/*
 * Overloaded Operators
 */

// modifies Point on the left
   Point & Point::operator*=(double rhs) {

        for (int i = 0; i < m_Dims; i++) {
            m_values[i] *= rhs;
        }

        return *this;
    }

// modifies Point on the left
    Point &Point::operator/=(double rhs) {
        if (rhs == 0) {
            cout << "Undefined. Can't divide by 0 " << endl;
            return *this;
        }

        else {
            for (int i = 0; i < m_Dims; i++) {
                m_values[i] /= rhs;
            }
        }
        return *this;
    }


// prevent (p1 * 2) = p2, returns a temporary point
    const Point Point::operator*(double d) const
    {
        Point copy(*this);

        for (int i = 0; i < m_Dims; i++) {
            copy.m_values[i] *= d;
        }

        return copy;
    }


// returns a temporary point
    const Point Point::operator/(double d) const {

        Point copy(*this);

        if (d == 0)
        {
            cout << endl << "Division by 0 not allowed. First Point object is returned." << endl;
            return (copy);
        }


        for (int i = 0; i < m_Dims; i++) {
            copy.m_values[i] /= d;
        }

        return copy;

    }




/*
 * Friends
 */

// modifies Point on the left
    Point &operator+=(Point &lhs, const Point &rhs) {
        if (&lhs == &rhs)                // adding Point to itself
            return lhs *= 2;

        else if (lhs.m_Dims == rhs.m_Dims) {
            for (int i = 0; i < lhs.m_Dims; i++) {
                lhs.m_values[i] += rhs.m_values[i];
            }
        }
        else
            cout << endl << "Points need to have same number of dimensions. No change to either point." << endl;

        return lhs;
    }

// modifies Point on the left
    Point &operator-=(Point &lhs, const Point &rhs) {
        if (&lhs == &rhs)
            return lhs *= 0;

        else if (lhs.m_Dims == rhs.m_Dims) {
            for (int i = 0; i < lhs.m_Dims; i++) {
                lhs.m_values[i] -= rhs.m_values[i];
            }
        }
        else
            cout << endl << "Points need to have same number of dimensions. No change to either point." << endl;

        return lhs;
    }


// returns temporary Point
    const Point operator+(const Point &lhs, const Point &rhs) {

        if (lhs.m_Dims == rhs.m_Dims) {
            Point p(lhs.m_Dims);

            for (int i = 0; i < lhs.m_Dims; i++) {
                p.m_values[i] = (lhs.m_values[i] + rhs.m_values[i]);
            }

            return p;
        }
        else
            cout << endl << "Undefined. Points don't have same number of dimensions. No change to any point." << endl;

        return lhs;

    }


// returns temporary Point
    const Point operator-(const Point &lhs, const Point &rhs) {
        if (lhs.m_Dims == rhs.m_Dims) {
            Point p(lhs.m_Dims);

            for (int i = 0; i < lhs.m_Dims; i++) {
                p.m_values[i] = (lhs.m_values[i] - rhs.m_values[i]);
            }

            return p;
        }

        else
            cout << endl << "Undefined. Points don't have same number of dimensions. No change to any point" << endl;

        return lhs;
    }




// returns true if both points contain same coordinates
// Overloaded == operator
    bool operator==(const Point &lhs, const Point &rhs) {
        bool equal = false;

        if (lhs.m_Dims == rhs.m_Dims) {
            equal = true;
               for (int i = 0; i < lhs.m_Dims; i++) {

                if (lhs.m_values[i] != rhs.m_values[i]) {
                    equal = false;
                    break;
                }
            }
        }

        else
            cout << endl << "Can only compare points with same number of dimensions" << endl;

        return equal;
    }


// returns true if the coordinates of the two points are different
// Overloaded != operator
    bool operator!=(const Point &lhs, const Point &rhs) {
        bool equalCatch = (lhs == rhs);

        return !equalCatch;
    }

// return true is left side Point is less than Point on right hand side
// Overloaded < operator
    bool operator<(const Point &lhs, const Point &rhs) {
        bool lessThen = true;

        if (lhs == rhs)
        {
            lessThen = false;
            return lessThen;
        }

        if (lhs.m_Dims == rhs.m_Dims)
        {
            int i = lhs.m_Dims;
            int index = 0;

            while( i > 0)
            {
                if (lhs.m_values[index] < rhs.m_values[index])
                {
                   return lessThen;
                }
                else if(lhs.m_values[index] > rhs.m_values[index])
                {
                    lessThen = false;
                    return lessThen;
                }

                ++index;
                --i;
            }

            lessThen = false;
            return lessThen;
        }

        else {
            cout << endl << "Points must have equal number of dimensions. " << endl;
            return 0;
        }



    }

// return true is left side Point is greater than Point on right hand side
// Overloaded > operator
    bool operator>(const Point &lhs, const Point &rhs) {
        bool greaterThen = true;

        if (lhs == rhs)
        {
            greaterThen = false;
            return greaterThen;
        }

        if (lhs.m_Dims == rhs.m_Dims)
        {
            int i = lhs.m_Dims;
            int index = 0;

            while( i > 0)
            {
                if (lhs.m_values[index] > rhs.m_values[index])
                {
                    return greaterThen;
                }
                else if (lhs.m_values[index] < rhs.m_values[index])
                {
                    greaterThen = false;
                    return greaterThen;
                }

                ++index;
                --i;
            }

            greaterThen = false;
            return greaterThen;
        }

        else {
            cout << endl << "Points must have equal number of dimensions." << endl;
            return 0;
        }

    }


    bool operator<=(const Point &lhs, const Point &rhs) {

        bool lessEqual = true;

        if (lhs == rhs)                  // checks if they are equal.
        {
            return lessEqual;
        }

        if (lhs.m_Dims == rhs.m_Dims)
        {
            lessEqual = (lhs < rhs);
            return lessEqual;
        }

        else {
            cout << endl << "Points must have equal number of dimensions." << endl;
            return 0;
        }

    }


    bool operator>=(const Point &lhs, const Point &rhs) {

        bool greaterEqual = false;

        if (lhs == rhs)                  // checks if they are equal.
        {
            greaterEqual = true;
            return greaterEqual;
        }
        greaterEqual = (lhs > rhs);      //uses overloaded > to check if lhs is greater than rhs

        return greaterEqual;
    }


    ostream &operator<<(std::ostream &os, const Point &point) {

        int i = 0;


        for ( i ; i < (point.m_Dims - 1); i++) {
            os << std::fixed << std::setprecision(1) << point.m_values[i] << Point::POINT_VALUE_DELIM << ' ';
        }

        os << point.m_values[i];

        return os;
    }

    istream &operator>>(std::istream &os,  Point &point)
    {

        string line;

            while (getline(os,line))
            {

                stringstream lineStream(line);
                string value;
                double d;


                int i =1;
                while(getline(lineStream, value, Point::POINT_VALUE_DELIM))
                {
                    d = stod(value);

                    point.setValue(i++,d);
                }


            }





    }


}
