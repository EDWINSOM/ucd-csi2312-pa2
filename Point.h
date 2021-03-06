/*
        Since the dimension could be potentially very large, you have to allocate it dynamically, and take care of all cleanup.
        Memory leaks will be penalized.

*/

#ifndef PA2_POINT_H
#define PA2_POINT_H

// A 3-dimensional point class!
// Coordinates are double-precision floating point.

#include <iostream>
#include <vector>
#include "Exceptions.h"

using namespace std;

namespace Clustering {



    class Point {

        unsigned m_Dims;                                           // number of dimensions of the point
        vector<double> m_values;                                 // values of the point's dimensions
        unsigned int __id;

    public:

        static unsigned int idGenerate();
        static void rewindIdGen();

        static const char POINT_VALUE_DELIM = ',' ;
        // Constructors
        Point();                                                // default constructor
        Point(unsigned d);                                      // custom constructor, takes 1 argument
        Point(unsigned, double *);                              // custom constructor, takes 2 arguments

        // Big three: cpy ctor, overloaded operator=, dtor
        ~Point();
        Point(const Point &);                                                               // object initialized with another object
        Point &operator=(const Point &) throw (DimensionalityMismatchEx);                   // object assigned to another object

        // Accessor Functions
        double getValue(unsigned) const;                         // gets coordinate of dimension of interest
        unsigned getDimension() const;                           // gets number of dimensions of a Point object
        double &operator[](unsigned) throw (OutOfBoundsEx);      // Overloaded [] index operator

        // Mutator Functions
        void setValue(unsigned, double) throw (DimensionalityMismatchEx);                   // sets value of dimension passed in

        // Functions
        double distanceTo(Point &) throw (DimensionalityMismatchEx);             // function calculates the distance between two points

        // Overloaded Operators
        Point &operator*= (double);                     // modifies Point on the left
        Point &operator/= (double);                     // modifies Point on the left
        const Point operator*(double) const;           // prevent (p1 * 2) = p2, returns a temporary point
        const Point operator/(double) const;            // returns a temporary point


        //Friends
        friend Point &operator+=(Point &, const Point &) throw (DimensionalityMismatchEx);   // modifies Point on the left
        friend Point &operator-=(Point &, const Point &) throw (DimensionalityMismatchEx);   // modifies Point on the left
        friend const Point operator+(const Point &, const Point &) throw (DimensionalityMismatchEx);     // returns temporary Point
        friend const Point operator-(const Point &, const Point &) throw (DimensionalityMismatchEx);     // returns temporary Point

        friend bool operator==(const Point &, const Point &) throw (DimensionalityMismatchEx);
        friend bool operator!=(const Point &, const Point &) throw (DimensionalityMismatchEx);

        friend bool operator<(const Point &, const Point &) throw (DimensionalityMismatchEx);
        friend bool operator>(const Point &, const Point &) throw (DimensionalityMismatchEx);
        friend bool operator<=(const Point &, const Point &) throw (DimensionalityMismatchEx);
        friend bool operator>=(const Point &, const Point &) throw (DimensionalityMismatchEx);

        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &) throw (DimensionalityMismatchEx);


    };

}


#endif //PA2_POINT_H

