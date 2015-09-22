//
// Created by marisa on 9/12/15.
//

#include "Point.h"
#include <cmath>

using namespace std;
using namespace Clustering;

/*
 * Constructors
 */

// Default
// Constructors are initializing newly constructed objects
Point::Point() {

    m_Dims = 2;
    m_values = new double [2];
}

// sends in n dimensions, creates array of doubles of size dimensions
Point::Point(int dimensions) {
    if (dimensions == 0)
            dimensions = 2;

    m_Dims = dimensions;
    m_values = new double [m_Dims];
}

// takes in n dimensions
// double * coordinates is an array of doubles
Point::Point(int dimensions, double * coordinates)
{
    if (dimensions == 0)
            dimensions=2;

    m_Dims=dimensions;
    m_values = new double [m_Dims];

    // copy double * coordinates into m_values
    for (int i = 0; i < m_Dims ; i++)
    {
        m_values[i] = coordinates[i];
    }
}



/*
 * The Big Three
 */

// Destructor
Point::~Point() {
   delete [] m_values;
}


// Copy constructor works on something that has already been created (exists already)
Point::Point(const Point& existingPoint)
{

    m_Dims = existingPoint.m_Dims;                // want same number of dimensions
    m_values = new double [m_Dims];

    for(int i=0; i < m_Dims ; i++)      // want to copy the values
    {
        m_values[i] = existingPoint.m_values[i];
    }
}


// Overloaded assignment operator
// const argument so you don't modify what is being passed in
Point& Point::operator=(const Point &rhs)
{
    if(this == &rhs)                    // Prevents self-assignment
        return *this;

    else
        delete [] m_values;             // if calling Point already exists, clear member data

    m_Dims=rhs.m_Dims;
    m_values = new double [m_Dims];     // new set of member data, equal to member data of rhs

    for(int i=0; i < m_Dims ; i++)
    {
        m_values[i] = rhs.m_values[i];
    }

    return *this;                       // return calling Point
}



/*
 * Accessor Member Functions
 */


// gets coordinate of dimension of interest
double Point::getValue(int dimension) const
{
    if(dimension >= 1 && dimension <= m_Dims)
        return m_values[dimension-1];


    return 0;
}

// gets number of dimensions of a Point object
int Point::getDimension() const
{
    return m_Dims;
}


// Overloaded [] index operator
// returns coordinate at index
double& Point::operator[] (int index)
{
    return m_values[index - 1];
}


/*
 * Mutator Member Functions
 */

// set coordinate of dimension passed in
void Point::setValue(int dimension, double value)
{
    if(dimension >= 1 && dimension <= m_Dims)
        m_values[dimension-1]= value;

}


/*
 * Functions
 */

/* Calculates distance between 2 points (the point calling the member function and the point passed in by reference)
   sqrt() is square root function defined in <cmath>
*/
double Point::distanceTo(const Point & point2)
{
    if( point2.m_Dims == m_Dims)                // both Points must have same number of dimensions
    {
        double sum = 0;

        for (int i = 0; i < m_Dims; i++)
        {
            double diff = m_values[i] - point2.m_values[i];     // coordinate-wise subtraction
            sum += (diff * diff);
        }

        return sqrt(sum);
    }

    return 0;
}



/*
 * Overloaded Operators
 */

// modifies Point on the left
Point & Point:: operator*= (double rhs)
{
    for (int i = 0; i << m_Dims ; i++)
    {
        m_values[i] *= rhs;
    }

    return *this;
}

// modifies Point on the left
Point &Point::operator/= (double rhs)
{
    if(rhs == 0)
        return *this;

    else
    {
        for (int i = 0; i < m_Dims ; i++)
        {
            m_values[i] /= rhs;
        }
    }
    return *this;
}

// prevent (p1 * 2) = p2, returns a temporary point
const Point Point::operator*(double d) const
{
    return Point(m_Dims) *= d;
}

// returns a temporary point
const Point Point::operator/(double d) const
{
    return Point(m_Dims) /= d;
}




/*
 * Friends
 */

// modifies Point on the left
friend Point &Point::operator+=(Point &lhs, const Point &rhs)
{
    if(&lhs == &rhs)                // adding Point to itself
            return lhs *= 2;

    else if (lhs.m_Dims == rhs.m_Dims)
    {
        for (int i = 0; i < lhs.m_Dims ; i++)
        {
            lhs.m_values[i] += rhs.m_values[i];
        }
    }

    return lhs;
}

// modifies Point on the left
friend Point &Point::operator-=(Point &lhs, const Point &rhs)
{
    if(&lhs == &rhs)
        return lhs *= 0;

    else if(lhs.m_Dims == rhs.m_Dims)
    {
        for(int i =0; i < lhs.m_Dims ; i++)
        {
            lhs.m_values[i] -= rhs.m_values[i];
        }
    }

    return lhs;
}

// returns temporary Point
friend const Point Point::operator+(const Point &lhs, const Point &rhs)
{
    if(lhs.m_Dims == rhs.m_Dims)
    {
        Point p(lhs.m_Dims);

        for(int i = 0; i < lhs.m_Dims ; i++)
        {
            p.m_values[i] = (lhs.m_values[i] + rhs.m_values[i]);
        }

        return p;
    }
    else
        cout << "Undefined. Point don't have same number of dimensions." << endl;

    return lhs;

}

// returns temporary Point
friend const Point Point::operator-(const Point &lhs, const Point &rhs)
{
    if(lhs.m_Dims == rhs.m_Dims)
    {
        Point p(lhs.m_Dims);

        for (int i =0; i < lhs.m_Dims ; i++)
        {
            p.m_values[i] = (lhs.m_values[i] - rhs.m_values[i]);
        }

        return p;
    }

    else
        cout << "Undefined. Point don't have same number of dimensions." << endl;

    return lhs;
}


// returns true if both points contain same coordinates
// Overloaded == operator
friend bool operator==(const Point &lhs, const Point &rhs)
{
    bool equal = false;

    if (lhs.m_Dims == rhs.m_Dims)
    {
        bool equal = true;
        for (int i =0; i < lhs.m_Dims ; i++)
        {
            if (lhs.m_values[i] != rhs.m_values[i])
            {
                equal = false;
                break;
            }
        }
    }

    return equal;
}


// returns true if the coordinates of the two points are different
// Overloaded != operator
friend bool operator!=(const Point &lhs, const Point &rhs)
{
    bool equalCatch = (lhs == rhs);

    return !equalCatch;
}

// return true is left side Point is less than Point on right hand side
// Overloaded < operator
friend bool operator<(const Point &lhs, const Point &rhs)
{
    bool lessThen = false;

    if(lhs.m_Dims == rhs.m_Dims)
    {
        for(int i = 0; i < lhs.m_Dims ; i++)
        {
            if(lhs.m_values[i] < rhs.m_values[i])
            {
                lessThen= true;
                return lessThen;
            }
        }
    }

    return lessThen;
}

// return true is left side Point is greater than Point on right hand side
// Overloaded > operator
friend bool operator>(const Point &lhs, const Point &rhs)
{
    bool greater = false;

    if(lhs.m_Dims == rhs.m_Dims)
    {
        for(int i = 0; i < lhs.m_Dims ; i++)
        {
            if(rhs.m_values[i] < lhs.m_values[i])
            {
                greater= true;
                return greater;
            }
        }
    }

    return greater;

}


friend bool operator<=(const Point &lhs, const Point &rhs)
{
    bool lessEqual = false;

    if(lhs == rhs)                  // checks if they are equal.
    {
        lessEqual = true;
    }
   lessEqual = (lhs < rhs);      //uses overloaded < to check if lhs is less than rhs

    return lessEqual;

}


friend bool operator>=(const Point &lhs, const Point &rhs)
{
    bool greaterEqual = false;

    if(lhs == rhs)                  // checks if they are equal.
    {
        greaterEqual = true;
    }
    greaterEqual = (lhs > rhs);      //uses overloaded > to check if lhs is greater than rhs

    return greaterEqual;
}

ostream &operator<<(std::ostream &os, const Point& point)
{
    os << endl << "This point has " << point.m_Dims << " dimensions with coordinate values : " << endl << "(";

    for (int i =0; i < point.m_Dims ; i++)
    {
        os << point.m_values[i] << ",";
    }

    os << ")" << endl << endl;

    return os;
}

