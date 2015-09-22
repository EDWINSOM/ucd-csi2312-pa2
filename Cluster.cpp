//
// Created by marisa on 9/19/15.
//

#include "Cluster.h"
#include <iostream>;
#include <iomanip>

using namespace std;
using namespace Clustering;




// Copy Constructor
// Cluster c2(c1)
Cluster::Cluster(const Cluster &cluster): size(cluster.size)
{
    node.p = new Point[size];               // PointPtr p now points to a dynamic Point array

    for(int i = 0; i < size ; i++)
    {
        node.p[i] = cluster.node.p[i];     // copy all of clusters Point array elements (Point objects) into new
                                            // cluster's dynamic Point array , data is independent and seperate
    }

    selectionSort(*this);

}


// Assignment Operator
Cluster& Cluster::operator=(const Cluster &cluster)
{
    if(this == &cluster)                    // Prevents self-assignment
    {
        selectionSort(*this);
        return *this;
    }

    else
    {
        for(int j = 0; j < size; j++)
            delete node.p[j];             // delete dynamic Point array elements
        delete[] node.p;                  // if calling cluster already exists, clear pointer to dynamic point array
    }
    size = cluster.size;
    node.p = new Point[size];               // PointPtr p now points to a dynamic Point array

    for (int i = 0; i < size ; i++)
    {
        node.p[i] = cluster.node.p[i];
    }

    selectionSort(*this);
    return *this;

}

// Destructor
Cluster::~Cluster()
{
    for(int j = 0; j < size; j++)
        delete node.p[j];             // delete dynamic Point array elements
    delete[] node.p;                  // if calling cluster already exists, clear pointer to dynamic point array
}


// selection sort to sort Points within cluster dynamic array in
// lexicographic order
void Cluster::selectionSort(Cluster & cluster)
{
    int startScan,minIndex;
    Point minValue;

    for(startScan = 0; startScan < (size - 1) ; startScan++)
    {
        minIndex = startScan;
        minValue = node.p[startScan];

        for(int index = startScan+1; index < size ; index++)
        {
            if (node.p[index] < minValue)                   // uses overloaded < Point operator with polymorphism
            {
                minValue = node.p[index];
                minIndex = index;
            }
        }
        node.p[minIndex] = node.p[startScan];
        node.p[startScan] = minValue;
    }
        return;
}


// Set functions: They allow calling c1.add(c2.remove(p));
void Cluster::add(const PointPtr & point)                      // add a point
{
    // Performs a selection sort to keep Points in lexicographic order
    ++size;
    node.p[size-1] = *point;

    selectionSort(*this);

}


// remove a point and return it so we can add it to another cluster
const PointPtr& Cluster::remove(const PointPtr& unwantedPoint)
{
    PointPtr temp;
    Point tempArray[size];
    temp = tempArray;               // on the stack
    for(int i = 0 ; i < size ; i++)
    {
        if(node.p[i] == (*unwantedPoint))
        {
            temp = unwantedPoint;
            delete node.p[i];
            return temp;
        }
    }

    return(unwantedPoint);
}


std::ostream &operator<<(std::ostream &os, const Cluster &cluster)
{
    os << endl << "Point in this cluster: " << endl << endl;

    for(int i = 0; i < size ; i++)
        os << setw(7) << node.p[i];


    return os;
}


friend bool operator==(const Cluster &lhs,const Cluster &rhs)
{
    if (lhs.size != rhs.size) {
        return false;
    }
    else if (lhs.size == rhs.size)
    {
        for (int i = 0; i < lhs.size ; i++)
        {
            if(lhs.node.p[i] != rhs.node.p[i])
            {
                return false;
            }
        }

    }
    return true;
}

// union
// increases size of calling object to fit both its previous set and the addition of all the Points in the set of rhs
// appends all of rhs's Points to the calling objects set
Cluster& Cluster::operator+=(const Cluster &rhs)
{
    int i = size-1;
    size += rhs.size;
    int counter = 0;

    for (int z = i; z < size; z++)
    {
        node.p[z] = rhs.node.p[counter];
        ++counter;
    }
}

//union
friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
{
    int tempSize = ((lhs.size)+(rhs.size));

    Cluster temp(tempSize);
    Point tempArray[tempSize];
    temp.node.p = tempArray;            // on the stack

    for(int i = 0; i < lhs.size; i++ )
    {
        temp.node.p[i] = lhs.node.p[i];
    }

    for (int j = (lhs.size); j < (tempSize - lhs.size) ; j++)
    {
        temp.node.p[j] = rhs.node.p[j];
    }

    return temp;

}

// returns temporary cluster value
// asymmetric difference
friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
{

    Cluster temp;
    Point tempArray[lhs.size];
    temp.node.p = tempArray;        // on the stack

    // searches for a specific value
    int index = 0;
    bool found = false;

    for (int i =0; i < lhs.size ; i++)
    {
        while ((index < rhs.size) && (!found))
        {
            if (rhs.node.p[index] == lhs.node.p[i])
            {
                found = true;
            }
            else
            {
                temp.node.p[i]= lhs.node.p[i];
            }
            index++;
        }
    }


    return temp;
}

Cluster & Cluster::operator-=(const Cluster &rhs)
{
    int index = 0;
    int position = -1;



}


