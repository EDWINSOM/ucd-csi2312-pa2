// DO NOT:      1. dereference head pointer         2. dereference nullptr!

#include "Cluster.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;


namespace Clustering {


// Copy Constructor
// Cluster c2(c1)

    Cluster::Cluster(const Cluster &cluster) : size(cluster.size) {
        if (size ==
            0)                             // if cluster is empty, set new cluster's head to null pointer and size 0;
        {
            head = nullptr;
            return;
        }

        NodePtr node1 = new Node;                    // if cluster is not of size 0, create 1 new node for new cluster
        head = node1;                                // let head point to this new node (1st node in our list)


        NodePtr current = cluster.head;
        NodePtr copy = head;                        // points to 1st node in our new cluster

        for (int i = 0; i < size - 1; i++)           // creates however many nodes we need
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
    Cluster &Cluster::operator=(const Cluster &cluster) {
        if (this == &cluster)                    // does not let self assignment occur
        {
            return *this;
        }

        NodePtr current = head;

        for (current; current != nullptr; current = current->nextNode) {
            current->pointPointer = nullptr;                // deletes each pointPointer from lhs Cluster

        }

        while (head != nullptr)                            // deletes linked list starting from the front
        {
            if (head != nullptr) {
                NodePtr delPtr = head;
                head = head->nextNode;
                delete delPtr;
            }                                           // head will end up pointing to nullptr (is an empty cluster now)
        }

        (this)->size = cluster.size;                    // set size equal to cluster's size

        if (size == 0)                                    // if cluster is empty, set new cluster's head to null pointer
        {
            head = nullptr;
            return (*this);
        }

        NodePtr node1 = new Node;                    // create 1 new node for new cluster
        head = node1;                                // let head point to this new node (1st node in our list)


        NodePtr original = cluster.head;
        NodePtr newList = head;                               // points to 1st node in our new cluster

        for (int i = 0; i < size - 1; i++)                // creates however many nodes we need
        {
            NodePtr node = new Node;
            newList->nextNode = node;                           // connect previous node to our new node
            newList = newList->nextNode;
        }

        newList->nextNode = nullptr;                           // set last node's nextNode to null pointer to terminate list
        newList = head;                                        // make copy point to head of our new linked list again

        while (original != nullptr) {
            newList->pointPointer = original->pointPointer;         //copies every pointer in cluster into our new cluster
            original = original->nextNode;
            newList = newList->nextNode;
        }


        return (*this);

    }


    // Destructor
    Cluster::~Cluster() {
        NodePtr current = head;


        while (head != nullptr)                            // deletes linked list starting from the front
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
    const PointPtr &Cluster::remove(const PointPtr &unwantedPoint) {
        assert(this->size != 0);                                     // if empty cluster, exit program


        if (size == 1) {
            if ((*(head->pointPointer)) == (*unwantedPoint)) {
                head->pointPointer = nullptr;
                head = nullptr;
                --size;
                return unwantedPoint;
            }
            else {
                cout << endl << "Such a point isn't contained in this cluster. Returning unwanted point" << endl;
                return unwantedPoint;
            }
        }

        if (size == 2) {
            if ((*(head->pointPointer)) == (*unwantedPoint)) {
                head->pointPointer = nullptr;
                NodePtr p = head->nextNode;
                head->nextNode = nullptr;
                head = p;
                --size;
                return unwantedPoint;
            }
            else if ((*(head->nextNode->pointPointer)) == (*unwantedPoint)) {
                head->nextNode->pointPointer = nullptr;
                head->nextNode = nullptr;
                --size;
                return unwantedPoint;
            }
            else {
                cout << endl << "Such a point isn't contained in this cluster. Returning unwanted point" << endl;
                return unwantedPoint;
            }
        }

        NodePtr current = head;

        Cluster copy;

        for (current; current != nullptr; current = current->nextNode) {
            if ((*(current->pointPointer)) != (*unwantedPoint)) {
                copy.add(current->pointPointer);
            }
        }

        (*this) = copy;

        return unwantedPoint;


    }


    void Cluster::add(const PointPtr &point)                      // add a point
    {
        NodePtr newNode = new Node;

        if (size == 0)                                            // if this is an empty cluster
        {
            head = newNode;
            newNode->nextNode = nullptr;
            newNode->pointPointer = point;
            ++size;
            return;
        }

        NodePtr current = head;
        NodePtr previous = head;

        if (size == 1) {
            if ((*(head->pointPointer)) < (*point)) {
                head->nextNode = newNode;
                newNode->nextNode = nullptr;
                newNode->pointPointer = point;
                ++size;
                return;
            }
            else {
                head = newNode;
                newNode->pointPointer = point;
                newNode->nextNode = current;
                ++size;

                return;

            }

        }


        for (current; current !=
                      nullptr; current = current->nextNode)        // find lexicographic appropriate place to place new Node with Point passed in
        {
            // if perfect place found


            if (((*(current->pointPointer)) <= (*point))) {
                if ((((current->nextNode) == nullptr))) {
                    current->nextNode = newNode;
                    newNode->nextNode = nullptr;
                    newNode->pointPointer = point;
                    ++size;
                    return;
                }


                else if ((*(current->nextNode->pointPointer)) >= (*point)) {
                    previous = current;                                             // keeps track of node before "perfect place"
                    current = current->nextNode;                                    // keeps track of node after "perfect place"

                    previous->nextNode = newNode;                                   // set node before place's nextNode pointer to point at our newNode
                    newNode->nextNode = current;                                    // let new node's nextNode pointer point to node after "perfect place"
                    newNode->pointPointer = point;                                  // set newNode's PointPtr to point to Point object to add
                    ++size;
                    return;
                }
            }


            else if ((*(current->pointPointer)) >= (*point)) {
                if (current == head) {
                    head = newNode;
                    newNode->pointPointer = point;
                    newNode->nextNode = current;
                    ++size;
                    return;
                }


            }


            previous = current;
        }

        // if we have reached nullptr (end of list), add our new node as last node in list
        previous->nextNode = newNode;
        newNode->nextNode = nullptr;
        newNode->pointPointer = point;
        ++size;

        return;

    }


    ostream &operator<<(std::ostream &os, const Cluster &cluster) {
        // Print contents of each node (their Points) contained within cluster

        os << endl << "This cluster is of size  " << cluster.size << endl;

        if (cluster.size == 0) {
            return os;
        }
        os << "Each point has " << cluster.head->pointPointer->getDimension() << " dimensions." << endl;
        os << "The points contained are as follows:" << endl << endl;

        NodePtr current = cluster.head;
        Point temp;

        for (current; current != nullptr; current = current->nextNode) {
            temp = (*(current->pointPointer));
            os << temp;
        }

        return os;


    }

    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        bool result = true;

        if (lhs.size != rhs.size) {
            cout << endl << "Clusters are not the same size, and therefore are not equal" << endl;
            return false;
        }

        NodePtr left = lhs.head;
        NodePtr right = rhs.head;

        for (left; left != nullptr; left = left->nextNode) {
            if ((*(left->pointPointer)) != (*(right->pointPointer))) {
                result = false;
            }
            right = right->nextNode;
        }

        return result;


    }

// union
// increases size of calling object to fit both its previous set and the addition of all the Points in the set of rhs
    Cluster &Cluster::operator+=(const Cluster &rhs) {
        if (rhs.size == 0) {
            return (*this);
        }


        NodePtr current = rhs.head;

        for (current; current != nullptr; current = current->nextNode) {
            (*this).add(current->pointPointer);
        }

        return (*this);

    }


// union of sets lhs and rhs
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster sendBack(lhs);

        sendBack += rhs;

        return sendBack;

    }


// (asymmetric) difference
    Cluster &Cluster::operator-=(const Cluster &rhs) {
        NodePtr q = rhs.head;

        while (q != nullptr) {
            (*this).remove(q->pointPointer);
            q = q->nextNode;
        }

        return (*this);

    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster m(lhs);

        m -= rhs;

        return m;

    }

    // add point
    Cluster &Cluster::operator+=(const Point &rhs) {

        PointPtr copy = new Point(rhs);


          this->add(copy);

        return (*this);
    }

    // remove point
    Cluster &Cluster::operator-=(const Point &rhs) {

        PointPtr copy = new Point(rhs);


        this->remove(copy);

        return (*this);


    }


const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
{
    Cluster funcCluster(lhs);

    PointPtr copy = new Point(*rhs);

    funcCluster.add(copy);

    return funcCluster;

}
    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster funcCluster(lhs);

        PointPtr copy = new Point(*rhs);

        funcCluster.remove(copy);

        return funcCluster;
    }




}




