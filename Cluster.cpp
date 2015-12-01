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

        if (cluster.size == 0)                        // if cluster is empty, set new cluster's head to null pointer and size 0;
        {
            head.clear();
            (this->__id) = (this->idGenerate());
            return;
        }

        this->head = cluster.head;

        this->__centroid = head.front();


        (this->__centroid) = (this->computeCentroid());
        return;
    }


    // Assignment Operator
    Cluster &Cluster::operator=( Cluster &cluster) {

        if (this == &cluster)                    // does not let self assignment occur
        {
            return *this;
        }


        head.clear();

        (this->size) = cluster.size;                    // set size equal to cluster's size
        (this->dimension) = cluster.dimension;

        if (size == 0)                                    // if cluster is empty, set new cluster's head to null pointer
        {
            head.clear();
            return (*this);
        }

        head = cluster.head;

        this->__centroid = cluster.head.front();


        (this->__centroid) = (this->computeCentroid());
        return (*this);

    }


    // Destructor
    Cluster::~Cluster() {

        head.clear();
    }



    // Set functions: They allow calling c1.add(c2.remove(p));


    // remove a point and return it so we can add it to another cluster
    void Cluster::remove(const Point &unwantedPoint) throw (RemoveFromEmptyEx)
    {

        this->validCentroid = false;

        try {

            if(this->size == 0)
                throw RemoveFromEmptyEx("remove");

            std::forward_list<Point>::iterator it = this->head.begin();

            if (size == 1) {
                Point test = *it;
                if ( (test) == (unwantedPoint) ) {
                    head.clear();
                    --size;
                }
                else {
                    cout << endl << "Such a point isn't contained in this cluster. Returning unwanted point" << endl;
                }
            }

            if (size == 2)
            {
                Point test2 = *it;
                if ((test2) == (unwantedPoint))
                {
                    head.pop_front();
                    --size;
                    (this->__centroid) = this->computeCentroid();
                }

                ++it;
                Point test3 = *it;
                if ((test3) == (unwantedPoint))
                {
                    head.remove(*it);
                    --size;
                    (this->__centroid) = this->computeCentroid();
                }

                else {
                    cout << endl << "Such a point isn't contained in this cluster. Returning unwanted point" << endl;
                }
            }

            it = head.begin();

            Cluster copy;

            for (it; it!= head.end(); ++it)
            {
                Point test4 = *it;
                if ((test4) != (unwantedPoint)) {
                    copy.add(*it);
                }
            }

            (*this) = copy;
            (this->__centroid) = this->computeCentroid();
        }

        catch(RemoveFromEmptyEx stringName)
        {
            cout << stringName;
            cout << endl << "Cluster is already empty. No points to remove" << endl << endl;
        }

    }


    void Cluster::add(const Point &point)                      // add a point
    {
        NodePtr newNode = new Node;
        this->validCentroid = false;

        if (size == 0)                                            // if this is an empty cluster
        {
            head.push_front(point);
            ++size;
            (this->dimension) = point.getDimension();
            this->__centroid = head.front();
            return;
        }

        std::forward_list<Point>::iterator it = head.begin();
        Point test = (*it);

        if (size == 1)
        {
            if (test < (point) )
            {
                head.insert_after(it ,point);
                ++size;
                (this->__centroid) = (this->computeCentroid());
                return;
            }
            else
            {   head.push_front(point);
                ++size;
                (this->__centroid) = this->computeCentroid();
                return;

            }
        }

        std::forward_list<Point>::iterator it2 = head.begin();

        // find lexicographic appropriate place to place new Node with Point passed in

        for (std::forward_list<Point>::iterator it3 = head.begin(); it3 != head.end(); it3++)
        {
            Point test2 = *it2;
            Point test3 = *it3;

            if ( (test3) == (point) )
            {
                    head.insert_after(it3, point);
                    ++size;
                    (this->__centroid) = this->computeCentroid();
                    return;
            }


            else if ( (test3) > (point) )
            {
                    head.insert_after(it2,point);
                    ++size;
                    (this->__centroid) = this->computeCentroid();
                    return;
            }

            it2 = it3;
        }

        // if we have reached (end of list), add our new node as last node in list
        head.insert_after(it2,point);
        ++size;
        (this->__centroid) = this->computeCentroid();
        return;

    }


    ostream &operator<<(std::ostream &os, const Cluster &cluster)
    {
        // Print contents of each node (their Points) contained within cluster

        os << endl << "This cluster is of size  " << cluster.size << endl;

        if (cluster.size == 0)
        {
            return os;
        }
        os << "Each point has " << cluster.dimension << " dimensions." << endl;
        os << "The points contained are as follows:" << endl << endl;


        for (auto it = cluster.head.begin(); it != cluster.head.end() ; ++it)
        {
            os   << *it  << (Cluster::POINT_CLUSTER_ID_DELIM) << "   " << cluster.__id << endl;
        }

        return os;
    }

    Point &Cluster::operator[](unsigned index) throw (OutOfBoundsEx)
    {
        auto it = head.begin();
        try
        {
            if (index < (this->size) )
            {
                if (index == 0)
                {
                    return head.front();
                }
                else
                {
                    for(int counter = 0; (it != head.end()) && (counter < index) ; counter++)
                    {
                        ++it;
                    }

                    return (*it);
                }
            }
            else
            {
                throw OutOfBoundsEx("[] operator");
            }
        }
        catch (OutOfBoundsEx stringName)
        {
            cout << stringName;
            cout << endl << "Index is invalid. No such index available in this cluster." << endl << endl;
            exit(1);
        }
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        bool result = false;

        if (lhs.size != rhs.size)
        {
            cout << endl << "Clusters are not the same size, and therefore are not equal" << endl;
            return false;
        }

        if( lhs.head == rhs.head)
        {
            result = true;
        }
        return result;
    }

// union
// increases size of calling object to fit both its previous set and the addition of all the Points in the set of rhs
    Cluster &Cluster::operator+=(const Cluster &rhs)
    {

        if (rhs.size == 0) {
            return (*this);
        }

        this->validCentroid = false;
        auto it = rhs.head.begin();

        for (it; it != rhs.head.end(); it++)
        {
            (*this).add(*it);
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

        auto it = rhs.head.begin();

        while (it != rhs.head.end()) {
            (*this).remove(*it);
            ++it;
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

          this->add(*copy);
        (this->__centroid) = this->computeCentroid();
        return (*this);
    }

    // remove point
    Cluster &Cluster::operator-=(const Point &rhs) {

        this->validCentroid = false;
        PointPtr copy = new Point(rhs);

        this->remove(*copy);

        (this->__centroid) = this->computeCentroid();
        return (*this);
    }


const Cluster operator+(Cluster &lhs, PointPtr &rhs)
{


    Cluster funcCluster(lhs);

    PointPtr copy = new Point(*rhs);

    funcCluster.add(*copy);

    funcCluster.validCentroid = false;
    funcCluster.__centroid = funcCluster.computeCentroid();
    return funcCluster;

}


    const Cluster operator-(Cluster &lhs, PointPtr &rhs)
    {

        Cluster funcCluster(lhs);

        PointPtr copy = new Point(*rhs);

        funcCluster.remove(*copy);

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


            cluster.add(*ptr);
            cluster.dimension = (d+1);
        }

        cluster.validCentroid = false;
        cluster.__centroid = (cluster.head.front());
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

    const Point& Cluster::computeCentroid() throw (RemoveFromEmptyEx)
    {
       try {

           if(this->size == 0)
               throw RemoveFromEmptyEx("computeCentroid");

           this->validCentroid = true;

           if (this->size == 1)
           {
               return this->__centroid;
           }

           (this->__centroid) /= (this->size);
           auto it = head.begin();

           while (it != head.end())
           {
               (this->__centroid) += ((*it) / (this->size));
               ++it;
           }

           this->setCentroid(this->__centroid);
           return (this->__centroid);
       }
        catch (RemoveFromEmptyEx stringName)
        {
            cout << stringName;
            cout << endl << "Cluster is empty. No centroid available" << endl << endl;
            return this->__centroid;
        }
    }


    unsigned int Cluster::idGenerate()
    {

        ++idtracker;

        return idtracker;
    }


    Cluster::Move::Move(const Point & ptr, Cluster* &from, Cluster* &to)
    {
        from->validCentroid = false;
        to->validCentroid = false;

        (this->toMove) = ptr;
        (this->destination) = (to);
        (this->origin) = (from);

        cout << endl << endl << "Moving point " << ptr << " from point space to cluster number " << to->__id << endl << endl;

        perform();
    }

    void Cluster::Move::perform()
    {
        (*destination).add( (this->toMove) );
        (*origin).remove( (this->toMove) );
    }

    void Cluster::pickPoints(int k , Point pointArray [])
    {
                cout << endl << "Entering pickPoints " << endl;

                auto it = head.begin();
                unsigned arrayTracker = 0;
                unsigned count = 1;

                // Checks to see if k is greater than the number of points in the cluster
                if(k > size)
                {
                    k = size;
                    cout << endl << "k is greater than size of cluster, setting k to size of cluster" << endl << endl;
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

                pointArray[arrayTracker] = (head.front());
                ++it;
                ++arrayTracker;


                while ((it != head.end()) && (arrayTracker != k))
                {
                    if (count == interval)
                    {
                        pointArray[arrayTracker] = (*(it));
                        count = 0;
                        ++arrayTracker;
                    }
                        ++count;

                        ++it;
                }

        }
        else
        {
            while (it != head.end())
            {
                pointArray[arrayTracker] = (*(it));
                ++arrayTracker;
                ++it;
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

    double Cluster::intraClusterDistance()
    {
        double sum = 0;
        auto it = this->head.begin();

        if (it == head.end())
        {
            return sum;
        }
                auto next = it;
                ++next;

        if (next != head.end())
        {
            for (it; it != head.end(); ++it)
            {
                for (next; next != head.end(); ++next)
                {
                    sum += ((*it)).distanceTo((*next));
                }
                next = this->head.begin();
            }
        }

        return sum/2.0;
    }

// sum of the distances between every point in two clusters

  double interClusterDistance(Cluster &c1, Cluster &c2)
   {
       double sum = 0;
       auto it_first = c1.head.begin();
       auto it_second = c2.head.begin();

       for (it_first; it_first != c1.head.end() ; ++it_first)
       {
           for (it_second ; it_second != c2.head.end() ; ++it_second)
           {
               sum += (*(it_first)).distanceTo(*(it_second));
           }

           it_second = c2.head.begin();
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

    bool Cluster::contains(const Point &point) {

        if (this->size == 0)
        {
            cout << endl << "Cluster is empty. Contains no points." << endl << endl;
            return false;
        }

        auto it = this->head.begin();

        for (it ; it != head.end() ; ++it)
        {
            if ((*(it)) == point)
            {
                return true;
            }
        }
        return false;
    }
}





