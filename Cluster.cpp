// DO NOT:      1. dereference head pointer         2. dereference nullptr!

#include "Cluster.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

static unsigned int idtracker = 0;

namespace Clustering {

// Copy Constructor
// Cluster c2(c1)


    Cluster::Cluster(Cluster &cluster) : size(cluster.size), dimension(cluster.dimension) {
        if (size == 0)                             // if cluster is empty, set new cluster's head to null pointer and size 0;
        {
            head = nullptr;
            (this->__id) = (this->idGenerate());
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

        cluster.size = 0;
        cluster.validCentroid = false;
        current = cluster.head;

        while (current != nullptr)
        {
            current->pointPointer = nullptr;
            current = current->nextNode;
        }

        (this->validCentroid) = false;

        (this->__centroid) = (this->computeCentroid());
        (this->__id) = (this->idGenerate());
        return;
    }


    // Assignment Operator
    Cluster &Cluster::operator=(Cluster &cluster) {
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

        (this->validCentroid)=false;
        (this)->size = cluster.size;                    // set size equal to cluster's size
        (this)->dimension = cluster.dimension;


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

        cluster.size = 0;
        cluster.validCentroid = false;
        original = cluster.head;

        while (original != nullptr)
        {
            original->pointPointer = nullptr;
            original = original->nextNode;
        }

        (this->__centroid) = (this->computeCentroid());
        (this->__id) = (this->idGenerate());
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
        this->validCentroid = false;

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
                (this->__centroid) = this->computeCentroid();
                return unwantedPoint;
            }
            else if ((*(head->nextNode->pointPointer)) == (*unwantedPoint)) {
                head->nextNode->pointPointer = nullptr;
                head->nextNode = nullptr;
                --size;
                (this->__centroid) = this->computeCentroid();
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
        (this->__centroid) = this->computeCentroid();
        return unwantedPoint;


    }


    void Cluster::add(const PointPtr &point)                      // add a point
    {
        NodePtr newNode = new Node;
        (this->validCentroid) = false;

        if (size == 0)                                            // if this is an empty cluster
        {
            head = newNode;
            newNode->nextNode = nullptr;
            newNode->pointPointer = point;
            ++size;
            (this->dimension) = newNode->pointPointer->getDimension();
     //       this->setCentroid(*point);
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
                (this->dimension) = newNode->pointPointer->getDimension();
                (this->__centroid) = this->computeCentroid();
                return;
            }
            else {
                head = newNode;
                newNode->pointPointer = point;
                newNode->nextNode = current;
                ++size;
                (this->dimension) = newNode->pointPointer->getDimension();
                (this->__centroid) = this->computeCentroid();
                return;

            }

        }


        for (current; current != nullptr; current = current->nextNode)        // find lexicographic appropriate place to place new Node with Point passed in
        {
            // if perfect place found


            if (((*(current->pointPointer)) <= (*point))) {
                if ((((current->nextNode) == nullptr))) {
                    current->nextNode = newNode;
                    newNode->nextNode = nullptr;
                    newNode->pointPointer = point;
                    ++size;
                    (this->dimension) = newNode->pointPointer->getDimension();
                    (this->__centroid) = this->computeCentroid();
                    return;
                }


                else if ((*(current->nextNode->pointPointer)) >= (*point)) {
                    previous = current;                                             // keeps track of node before "perfect place"
                    current = current->nextNode;                                    // keeps track of node after "perfect place"

                    previous->nextNode = newNode;                                   // set node before place's nextNode pointer to point at our newNode
                    newNode->nextNode = current;                                    // let new node's nextNode pointer point to node after "perfect place"
                    newNode->pointPointer = point;                                  // set newNode's PointPtr to point to Point object to add
                    ++size;
                    (this->dimension) = newNode->pointPointer->getDimension();
                    (this->__centroid) = this->computeCentroid();
                    return;
                }
            }


            else if ((*(current->pointPointer)) >= (*point)) {
                if (current == head) {
                    head = newNode;
                    newNode->pointPointer = point;
                    newNode->nextNode = current;
                    ++size;
                    (this->dimension) = newNode->pointPointer->getDimension();
                    (this->__centroid) = this->computeCentroid();
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
        (this->dimension) = newNode->pointPointer->getDimension();
        (this->__centroid) = this->computeCentroid();
        return;

    }


    ostream &operator<<(std::ostream &os, const Cluster &cluster) {
        // Print contents of each node (their Points) contained within cluster

        os << endl << "This cluster is of size  " << cluster.size << endl;

        if (cluster.size == 0) {
            return os;
        }
        os << "Each point has " << cluster.dimension << " dimensions." << endl;
        os << "The points contained are as follows:" << endl << endl;

        NodePtr current = cluster.head;
        Point temp;

        for (current; current != nullptr; current = current->nextNode) {
            temp = (*(current->pointPointer));
            os  << temp << "\t\t" << (Cluster::POINT_CLUSTER_ID_DELIM) << cluster.__id << endl;

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

        this->validCentroid = false;
        (this->__centroid) = this->computeCentroid();
        return (*this);

    }


// union of sets lhs and rhs
    const Cluster operator+(Cluster &lhs, Cluster &rhs) {
        Cluster sendBack(lhs);

        sendBack += rhs;

        sendBack.validCentroid = false;
        (sendBack.__centroid) = sendBack.computeCentroid();
        return sendBack;

    }


// (asymmetric) difference
    Cluster &Cluster::operator-=(const Cluster &rhs) {
        NodePtr q = rhs.head;

        while (q != nullptr) {
            (*this).remove(q->pointPointer);
            q = q->nextNode;
        }

        (this->validCentroid) = false;
        (this->__centroid) = this->computeCentroid();
        return (*this);

    }

    const Cluster operator-(Cluster &lhs, Cluster &rhs) {
        Cluster m(lhs);

        m -= rhs;

        m.validCentroid = false;
        m.__centroid = m.computeCentroid();
        return m;

    }

    // add point
    Cluster &Cluster::operator+=(const Point &rhs) {

        PointPtr copy = new Point(rhs);


          this->add(copy);
        (this->validCentroid) = false;
        (this->__centroid) = this->computeCentroid();
        return (*this);
    }

    // remove point
    Cluster &Cluster::operator-=(const Point &rhs) {

        PointPtr copy = new Point(rhs);


        this->remove(copy);

        (this->validCentroid) = false;
        (this->__centroid) = this->computeCentroid();
        return (*this);
    }


const Cluster operator+(Cluster &lhs, PointPtr &rhs)
{
    Cluster funcCluster(lhs);

    PointPtr copy = new Point(*rhs);

    funcCluster.add(copy);

    funcCluster.validCentroid = false;
    funcCluster.__centroid = funcCluster.computeCentroid();
    return funcCluster;

}
    const Cluster operator-(Cluster &lhs, PointPtr &rhs)
    {
        Cluster funcCluster(lhs);

        PointPtr copy = new Point(*rhs);

        funcCluster.remove(copy);

        funcCluster.validCentroid = false;
        funcCluster.__centroid = funcCluster.computeCentroid();
        return funcCluster;
    }

    istream &operator>>(std::istream &os, Cluster & cluster)
    {
        string line;

        while(getline(os,line))
        {
            int d = (int) std::count(line.begin(), line.end(),  ',');

            PointPtr ptr = new Point(d+1);

            std::stringstream lineStream(line);

            lineStream >> (*ptr);

            cluster.add(ptr);

        }

        (cluster.validCentroid) = false;
        cluster.__centroid = cluster.computeCentroid();
        return os;
    }

    const Point& Cluster::setCentroid(const Point & point)
    {
        if ((point.getDimension()) == (this->dimension))
        {
            this->__centroid = point;
            (this->validCentroid) = true;
            return this->__centroid;
        }
        else
        {
            cout << "Setting of centroid failed. Dimensionality error. " << endl;
            (this->validCentroid) = false;
            return this->__centroid;
        }
    }

    const Point Cluster::getCentroid() const
    {
        return this->__centroid;
    }

    const Point& Cluster::computeCentroid()
    {
        int divider = 0;
        NodePtr tracker = (this->head);

        while(tracker != nullptr)
        {

            if (divider >= 5)
            {
                (this->__centroid) /= divider;
                divider = 0;
            }

            (this->__centroid) += (*(tracker->pointPointer));
            tracker = (tracker->nextNode);
            ++divider;
        }

        if(divider != 0)
        {
            (this->__centroid) /= divider;
        }

        (this->validCentroid) = true;
        return (this->__centroid);
    }


    unsigned int Cluster::idGenerate()
    {

        ++idtracker;

        return idtracker;
    }


    Cluster::Move::Move(const PointPtr & ptr, Cluster* from, Cluster*to)
    {
        (this->toMove) = ptr;
        (this->destination) = (to);
        (this->origin) = (from);

        perform();
    }

    void Cluster::Move::perform()
    {
        (*destination).add((*origin).remove(this->toMove));
    }

    void Cluster::pickPoints(int k, PointPtr *pointArray)
    {

    }

}



