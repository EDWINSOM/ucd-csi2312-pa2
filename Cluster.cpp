// DO NOT:      1. dereference head pointer         2. dereference nullptr!

#include "Cluster.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

static unsigned int idtracker = 0;

namespace Clustering {

// Copy Constructor
// Cluster c2(c1)


    Cluster::Cluster(Cluster &cluster) : size(cluster.size), dimension(cluster.dimension), __centroid(cluster.dimension) {

        this->validCentroid = false;

        if (size == 0)                             // if cluster is empty, set new cluster's head to null pointer and size 0;
        {
            head = nullptr;
            (this->__id) = (this->idGenerate());
            cout << endl << "new cluster created: " << this->__id << endl;
            return;
        }

        NodePtr node1 = new Node;                    // if cluster is not of size 0, create 1 new node for new cluster
        head = node1;                                // let head point to this new node (1st node in our list)


        NodePtr current = cluster.head;
        NodePtr copy = head;                        // points to 1st node in our new cluster
        this->__centroid = (*(cluster.head->pointPointer));

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

        current = cluster.head;

        while (current != nullptr)
        {
            current->pointPointer = nullptr;
            current = current->nextNode;
        }

        (this->__centroid) = (this->computeCentroid());
        (this->__id) = (this->idGenerate());

        cout << endl << "new cluster created: " << (this->__id) << endl;
        return;
    }


    // Assignment Operator
    Cluster &Cluster::operator=(  Cluster &cluster) {

        if (this == &cluster)                    // does not let self assignment occur
        {
            return *this;
        }

        this->validCentroid = false;

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


        (this->size) = cluster.size;                    // set size equal to cluster's size
        (this->dimension) = cluster.dimension;


        if (size == 0)                                    // if cluster is empty, set new cluster's head to null pointer
        {
            head = nullptr;
            return (*this);
        }

        NodePtr node1 = new Node;                    // create 1 new node for new cluster
        head = node1;                                // let head point to this new node (1st node in our list)


        NodePtr original = cluster.head;
        this->__centroid = (*(original->pointPointer));
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
        original = cluster.head;

        while (original != nullptr)
        {
            original->pointPointer = nullptr;
            original = original->nextNode;
        }

        (this->__centroid) = (this->computeCentroid());
        (this->__id) = (this->idGenerate());
        cout << endl << "new cluster created: " << (this->__id) << endl;
        return (*this);

    }


    // Destructor
    Cluster::~Cluster() {



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

        this->validCentroid = false;

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
        this->validCentroid = false;

        if (size == 0)                                            // if this is an empty cluster
        {
            head = newNode;
            newNode->nextNode = nullptr;
            newNode->pointPointer = point;
            ++size;
            (this->dimension) = newNode->pointPointer->getDimension();
            this->__centroid = (*point);
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
                (this->__centroid) = (this->computeCentroid());
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

        NodePtr current = nullptr;
        Point temp;

        for (current = cluster.head; current != nullptr; current = current->nextNode) {
            temp = (*(current->pointPointer));
            os   << temp  << (Cluster::POINT_CLUSTER_ID_DELIM) << "   " << cluster.__id << endl;

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

        this->validCentroid = false;
        NodePtr current = rhs.head;

        for (current; current != nullptr; current = current->nextNode) {
            (*this).add(current->pointPointer);
        }


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

        this->validCentroid = false;

        NodePtr q = rhs.head;

        while (q != nullptr) {
            (*this).remove(q->pointPointer);
            q = q->nextNode;
        }


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

        this->validCentroid = false;

        PointPtr copy = new Point(rhs);

          this->add(copy);
        (this->__centroid) = this->computeCentroid();
        return (*this);
    }

    // remove point
    Cluster &Cluster::operator-=(const Point &rhs) {

        this->validCentroid = false;
        PointPtr copy = new Point(rhs);

        this->remove(copy);

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
            unsigned d = (unsigned) std::count(line.begin(), line.end(),  ',');

            PointPtr ptr = new Point(d+1);

            std::stringstream lineStream(line);

            lineStream >> (*ptr);


            cluster.add(ptr);
            cluster.dimension = (d+1);
        }

        cluster.validCentroid = false;
        cluster.__centroid = (*(cluster.head->pointPointer));
        cluster.__centroid = cluster.computeCentroid();         // CENTROID

        return os;
    }

    const Point& Cluster::setCentroid(const Point & point)
    {
        this->validCentroid = true;

        if ((point.getDimension()) == (this->dimension))
        {
            this->__centroid = point;
            return this->__centroid;
        }
        else
        {
            cout << "Setting of centroid failed. Dimensionality error. " << endl;
            return this->__centroid;
        }
    }


    const Point Cluster::getCentroid() const
    {

        return this->__centroid;
    }

    const Point& Cluster::computeCentroid()
    {
        this->validCentroid = true;

        (this->__centroid) /= (this->size);
        NodePtr tracker = (this->head->nextNode);

        while(tracker != nullptr)
        {
            (this->__centroid) += ( (*(tracker->pointPointer))/ (this->size));
            tracker = (tracker->nextNode);
        }

        this->setCentroid(this->__centroid);
        return (this->__centroid);
    }


    unsigned int Cluster::idGenerate()
    {

        ++idtracker;

        return idtracker;
    }


    Cluster::Move::Move(const PointPtr & ptr, Cluster* &from, Cluster* &to)
    {
        from->validCentroid = false;
        to->validCentroid = false;

        (this->toMove) = ptr;
        (this->destination) = (to);
        (this->origin) = (from);

        cout << endl << endl << "Moving point " << *ptr << " from point space to cluster number " << to->__id << endl << endl;

        perform();
    }

    void Cluster::Move::perform()
    {
        (*destination).add((*origin).remove(this->toMove));
    }

    void Cluster::pickPoints(int k, Point pointArray [])
    {
            cout << endl << "Entering pickPoints " << endl;

            NodePtr current = head;
            unsigned arrayTracker = 0;
            unsigned count = 1;

            // Checks to see if k is greater than the number of points in the cluster
            if(k > size)
            {
                k = size;
                cout << endl << "k is greater than size of cluster, setting k to size of cluster" << endl;
            }

            else if (k < size)
            {
                cout << endl << "k is less than size of cluster" << endl;
            }

            else
                cout << endl << "k is equal to size of cluster" << endl;

    if (k != size)
    {
        unsigned interval = (size)/k;

        if (interval % 2)
        {
            ++interval;
        }

            pointArray[arrayTracker] = (*(head->pointPointer));
            current = current->nextNode;
            ++arrayTracker;


            while ((current != nullptr) && (arrayTracker != k))
            {
                if (count == interval)
                {
                    pointArray[arrayTracker] = (*(current->pointPointer));
                    count = 0;
                    ++arrayTracker;
                }
                    ++count;

                    current = current->nextNode;
            }

    }
        else
    {
        while (current != nullptr)
        {
            pointArray[arrayTracker] = (*(current->pointPointer));
            ++arrayTracker;
            current = current->nextNode;
        }
    }
    }


    unsigned Cluster::getSize()
    {
        return this->size;
    }


    // sum of the distances between every two points in the cluster. Hint: This
    // can be done in a double loop through the points of the cluster. However,
    // this will count every distance twice, so you need to divide the sum by 2 before returning it.

    double Cluster::intraClusterDistance() const
    {
        double sum = 0;
        NodePtr current = head;
if ( head == nullptr)
{
    return sum;
}
        NodePtr next = head->nextNode;

if (next != nullptr) {
    for (current; current != nullptr; current = current->nextNode) {

        for (next; next != nullptr; next = next->nextNode) {
            sum += (*(current->pointPointer)).distanceTo(*(next->pointPointer));

        }

        next = head;
    }
}

        return sum/2.0;

    }

// sum of the distances between every point in two clusters

  double interClusterDistance(const Cluster &c1, const Cluster &c2)
   {
       double sum = 0;
       NodePtr first = c1.head;
       NodePtr second = c2.head;

       for (first; first != nullptr ; first = first->nextNode)
       {
           for (second ; second != nullptr ; second = second->nextNode)
           {
               sum += (*(first->pointPointer)).distanceTo(*(second->pointPointer));
           }

           second = c2.head;
       }

        return sum/2.0;
   }

    // returns the number of distinct point pairs, or edges, in a cluster. (That is,
    // every two distinct points have an imaginary edge between them. Its length is
    // the distance between the two points.) This is simply size * (size - 1) / 2,
    // where size is the size of the cluster.

    int Cluster::getClusterEdges()
    {
       return size * (size - 1) / 2;

    }

    double interClusterEdges(const Cluster &c1, const Cluster &c2)
    {
        return (c1.size * c2.size / 2);
    }


    unsigned Cluster::getDimension() {
        return dimension;
    }
}





