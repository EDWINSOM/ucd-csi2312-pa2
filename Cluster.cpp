// DO NOT:      1. dereference head pointer         2. dereference nullptr!

#include "Cluster.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;


namespace Clustering {


// Copy Constructor
// Cluster c2(c1)

    Cluster::Cluster(const Cluster &cluster): size(cluster.size)
    {
       if(size == 0)                             // if cluster is empty, set new cluster's head to null pointer and size 0;
       {
           head = nullptr;
           return;
       }

        NodePtr node1 = new Node;                    // if cluster is not of size 0, create 1 new node for new cluster
        head = node1;                                // let head point to this new node (1st node in our list)


        NodePtr current = cluster.head;
        NodePtr copy = head;                        // points to 1st node in our new cluster

        for(int i = 0;  i < size-1 ; i++)           // creates however many nodes we need
        {
            NodePtr node = new Node;
            copy->nextNode = node;                           // connect previous node to our new node
            copy = copy->nextNode;
        }

        copy->nextNode = nullptr;                           // set last node's nextNode to null pointer to terminate list
        copy = head;                                        // make copy point to head of our new linked list again

        while (current != nullptr)                                 // will not run if cluster is an empty cluster
        {
            copy->pointPointer = current->pointPointer;         // copies every pointer in cluster into our new cluster
            current = current->nextNode;
            copy = copy->nextNode;
        }

        return;
    }



    // Assignment Operator
    Cluster& Cluster::operator=(const Cluster &cluster)
    {
        if( this == &cluster)                    // does not let self assignment occur
        {
            return *this;
        }

        NodePtr current = head;

        for (current; current != nullptr ; current = current->nextNode )
        {
            delete current->pointPointer;                // deletes each pointPointer from lhs Cluster

        }

        while(head != nullptr)                            // deletes linked list starting from the front
        {
            if (head != nullptr) {
                NodePtr delPtr = head;
                head = head->nextNode;
                delete delPtr;
            }                                           // head will end up pointing to nullptr (is an empty cluster now)
        }

        (this)->size = cluster.size;                    // set size equal to cluster's size

        if(size == 0)                                    // if cluster is empty, set new cluster's head to null pointer
        {
            head = nullptr;
            return (*this);
        }

        NodePtr node1 = new Node;                    // create 1 new node for new cluster
        head = node1;                                // let head point to this new node (1st node in our list)


        NodePtr original = cluster.head;
        NodePtr newList = head;                               // points to 1st node in our new cluster

        for(int i = 0;  i < size-1 ; i++)                // creates however many nodes we need
        {
            NodePtr node = new Node;
            newList->nextNode = node;                           // connect previous node to our new node
            newList = newList->nextNode;
        }

        newList->nextNode = nullptr;                           // set last node's nextNode to null pointer to terminate list
        newList = head;                                        // make copy point to head of our new linked list again

        while (original != nullptr)
        {
            newList->pointPointer = original->pointPointer;         //copies every pointer in cluster into our new cluster
            original = original->nextNode;
            newList = newList->nextNode;
        }


        return (*this);

    }


    // Destructor
    Cluster::~Cluster()
    {
        NodePtr current = head;

        for (current; current != nullptr ; current = current->nextNode )
        {
            delete current->pointPointer;                // deletes each pointPointer

        }

      while(head != nullptr)                            // deletes linked list starting from the front
        {
            if (head != nullptr) {
                NodePtr delPtr = head;
                head = head->nextNode;
                delete delPtr;
            }                                           // head will end up pointing to nullptr (is an empty cluster now)
        }
    }



    // Set functions: They allow calling c1.add(c2.remove(p));


    // remove a point and return it so we can add it to another cluster
    const PointPtr& Cluster::remove(const PointPtr& unwantedPoint)
    {
            assert(this->size != 0);                                     // if empty cluster, exit program

        NodePtr current = head;
        NodePtr previous = head;

        for (current; current != nullptr ; current = current->nextNode )        // find node w/ matching Point object
        {
            if( (*(current->pointPointer)) == (*unwantedPoint) )
            {
                PointPtr returnPoint = unwantedPoint;                          // copy address of Point object so we can return it
                delete current->pointPointer;                                  // delete pointer to matching point
                previous = current;
                current = current->nextNode;                                    // now nothing points to node that had Point object

                previous->nextNode = current;                                   // makes previous node's (1 before node w/ matching point object) nextNode point to node
                                                                                // following the one that held matching Point object
                --size;

                return returnPoint;                                             // return address of unwanted Point address
            }

            previous = current;

        }

        cout << endl << "Such point does not reside in this cluster. Program terminating." << endl;
        exit(1);                                                // terminates program is such point does not reside in the cluster


    }


    void Cluster::add(const PointPtr & point)                      // add a point
    {
       NodePtr newNode = new Node;

        if (size == 0)                                            // if this is an empty cluster
        {
            head = newNode;
            newNode->nextNode = nullptr;
            newNode->pointPointer = point;
            return;
        }

        NodePtr current = head;
        NodePtr previous = head;

        for (current; current != nullptr ; current = current->nextNode )        // find lexicographic appropriate place to place new Node with Point passed in
        {
            // if perfect place found
            if(( (*(current->pointPointer)) <= (*point) ) && ((*(current->nextNode->pointPointer)) >= (*point)))
            {
                previous = current;                                             // keeps track of node before "perfect place"
                current = current->nextNode;                                    // keeps track of node after "perfect place"

                previous->nextNode = newNode;                                   // set node before place's nextNode pointer to point at our newNode
                newNode->nextNode = current;                                    // let new node's nextNode pointer point to node after "perfect place"
                newNode->pointPointer = point;                                  // set newNode's PointPtr to point to Point object to add
                ++size;
                return;
            }

            previous = current;
        }

        // if we have reached nullptr (end of list), add our new node as last node in list
        current->nextNode = newNode;
        newNode->nextNode = nullptr;
        newNode->pointPointer = point;
        ++size;

        return;

    }


    std::ostream &operator<<(std::ostream &os, const Cluster &cluster)
    {
        // Print contents of each node (their Points) contained within cluster
    }

bool operator==(const Cluster &lhs,const Cluster &rhs)
    {

    }

// union
// increases size of calling object to fit both its previous set and the addition of all the Points in the set of rhs
    Cluster& Cluster::operator+=(const Cluster &rhs)
    {

    }


// union of sets lhs and rhs
 const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {


    }



// (asymmetric) difference
    Cluster& Cluster::operator-=(const Cluster &rhs)
    {

    }

//!NOT IMPLEMENTING YET!
 const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {

    }

    // add point
    Cluster& Cluster::operator+=(const Point &rhs)
    {

    }

    // remove point
    Cluster& Cluster::operator-=(const Point &rhs)
    {

    }


    // passing in a pointer by reference
const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {

    }







}

