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
    LNodePtr newNode = new LNode;
    newNode->p = new Point[size];            // PointPtr p now points to a dynamic Point array

    for(int i = 0; i < size ; i++)
    {
        newNode->p[i] = cluster.points->p[i];     // copy all of clusters Point array elements (Point objects) into new
                                                // cluster's dynamic Point array , data is independent and seperate
    }

    cluster.points->next = points;             // cluster passed in now points to head of our new cluster

    newNode->next = nullptr;                    // marks end of linked list

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
            delete points->p[j];             // delete dynamic Point array elements

        delete [] points->p;                  // if calling cluster already exists, clear pointer to dynamic point array
        delete [] points;                   // essentially deleting the node by deleting pointer to node
    }
    size = cluster.size;

    LNodePtr newNode = new LNode;
    newNode->p = new Point[size];            // PointPtr p now points to a dynamic Point array

    for (int i = 0; i < size ; i++)
    {
        newNode->p[i] = cluster.points->p[i];   // fill our new Point array with points of cluster passed in
    }

    cluster.points->next = points;             // cluster passed in now points to head of our new cluster
    newNode->next = nullptr;                    // marks end of linked list

    selectionSort(*this);
    return *this;

}

// Destructor
Cluster::~Cluster()
{
    for(int j = 0; j < size; j++)
        delete points->p[j];                 // delete dynamic Point array elements

    delete [] points->p;                     // if calling cluster already exists, clear pointer to dynamic point array
    delete [] points;                        // essentially deleting the node by deleting pointer to node
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
        minValue = cluster.points->p[startScan];

        for(int index = startScan+1; index < size ; index++)
        {
            if (cluster.points->p[index] < minValue)                   // uses overloaded < Point operator with polymorphism
            {
                minValue = cluster.points->p[index];
                minIndex = index;
            }
        }
        cluster.points->p[minIndex] = cluster.points->p[startScan];
        cluster.points->p[startScan] = minValue;
    }
        return;
}


// Set functions: They allow calling c1.add(c2.remove(p));
void Cluster::add(const PointPtr & point)                      // add a point
{
    // temp Node
    LNodePtr newNode = new LNode;
    newNode->p = new Point[size];

    for (int i = 0; i < size ; i++)
    {
        newNode->p[i] = points->p[i];           // copy everything in calling cluster's Point array into our temp Node Point array
    }

    for (int j = 0; j < size ; j++)
    {
        delete points->p[j];                // deallocate every Point in calling cluster's Point array
    }
    delete points->p;                       // delete pointer's address

    size += 1;
    points->p = new Point[size];            // create new Point array large enough to house previous Point objects plus 1

    this->points->p[size-1] = (*point);     // adds this point to our Point array
    selectionSort(*this);

    delete newNode->p;                  // deletes tempNode's pointer
    delete newNode;                     // deletes tempNode

    return;
}


// remove a point and return it so we can add it to another cluster
const PointPtr& Cluster::remove(const PointPtr& unwantedPoint)
{
    // temp Node
    LNodePtr newNode = new LNode;
    newNode->p = unwantedPoint;     // our newNode pointer points to address of unwanted point



    for(int i = 0 ; i < size ; i++)
    {
        if(this->points->p[i] == (*unwantedPoint))   // uses Point's overloaded ==
        {
            delete (this->points->p[i]);            // deallocated memory for that point
            selectionSort(*this);                   // reorder Point-s in array

            delete newNode->p;                      // delete tempNode's pointer
            delete newNode;                         // delete tempNode

            return newNode->p;
        }
    }

    delete newNode->p;                      // delete tempNode's pointer
    delete newNode;                         // delete tempNode

    return(newNode->p);
}


friend std::ostream &operator<<(std::ostream &os, const Cluster &cluster)
{
    os << endl << "Point in this cluster: " << endl << endl;

    for(int i = 0; i < cluster.size ; i++)
        os << setw(7) << cluster.points->p[i];          // Prints out each Point,calls Point overloaded << operator


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
            if(lhs.points->p[i] != rhs.points->p[i])
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
    int s = size;               // hold size value of calling cluster

    // temp Node
    LNodePtr newNode = new LNode;
    newNode->p = new Point[size];

    for (int i = 0; i < size ; i++)
    {
        newNode->p[i] = points->p[i];           // copy everything in calling cluster's Point array into our temp Node Point array
    }

    for (int j = 0; j < size ; j++)
    {
        delete points->p[j];                // deallocate every Point in calling cluster's Point array
    }
    delete points->p;                       // delete pointer's address

    size += rhs.size;
    points->p = new Point[size];            // create new Point array large enough to house previous Point objects plus those in rhs

    for (int k = 0; k < s ; k++)
    {
        points->p[k] = newNode->p[k];       // copy in previous Point array of calling function
    }

    for (int l = s ; l < size ; l++)
    {
        points->p[l] = rhs.points->p[l];    // copy in rhs Point array
    }

    for (int m = 0; m < s ; m++)
    {
        delete newNode->p[m];               // delete all Point objects in temp Node's Point array
    }
    delete newNode->p;                      // delete temp Node's pointer
    delete newNode;                         // delete temp Node;

    return (*this);
}

// union of sets lhs and rhs
friend const Cluster Cluster::operator+(const Cluster &lhs, const Cluster &rhs)
{
    int unionSize = (lhs.size + rhs.size);
    Cluster unionCluster(unionSize);

    unionCluster += lhs;            // adds all Points from lhs to unionCluster
    unionCluster += rhs;            // adds all Points from rhs to unionCluster

    return unionCluster;

}



