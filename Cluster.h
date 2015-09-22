//
// Created by marisa on 9/19/15.
//

#ifndef PA2_CLUSTER_H
#define PA2_CLUSTER_H

#include "Point.h"

/*  Cluster Skeleton:
 *  2 Private Members:      1. dynamic array of Point objects       2. an array size
 */

namespace Clustering {

    // Pointer type aliases
    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;

    struct LNode
    {
        PointPtr p;             // points to dynamic array of Point objects
        LNodePtr next;          // points to next node in list
    };


    class Cluster {


    public:
        Cluster() : size(0), points(nullptr) {};
        Cluster(int sizePass) : size(sizePass), points(nullptr) {};

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster (const Cluster &);                      // object initialized with another object
        Cluster &operator=(const Cluster &);            // objected assigned to another object
                                                        // allocate a new Node for 2nd object and fill it up
                                                        // like the Node of the 1st object
        ~Cluster();

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);                      // add a point
        const PointPtr& remove(const PointPtr &);       // remove a point and return it so we can add it to another cluster
        void selectionSort(Cluster &);                 // sorts Point's in lexicographic order


        // Overloaded Operators

        //IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);

        // Set-preserving operators (do not duplicate points in the space)
        // -Friends
        friend bool operator==(const Cluster &lhs,const Cluster &rhs);

        // Members
        Cluster &operator+=(const Cluster &rhs);    // union
        Cluster &operator-=(const Cluster &rhs);    // (asymmetric) difference

        Cluster &operator+=(const Point &rhs);      // add point
        Cluster &operator-=(const Point &rhs);      // remove point

        // Set-destructive operators (duplicate points in the space)
        // -Friends
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);    // passing in a pointer by reference
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);    // passing in a pointer by reference

        friend std::ostream &operator<<(std::ostream &os, const Cluster &cluster);

    private:

        int size;           // number of Point objects held in cluster (size of dynamically allocated array of Point objects)
        LNodePtr points;    // head of each node
    };
}


#endif //PA2_CLUSTER_H
