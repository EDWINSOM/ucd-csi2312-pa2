// Can have arbitrary number of Nodes that hold one Point each



#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include <forward_list>

#include "Point.h"
#include "Exceptions.h"

using namespace std;

namespace Clustering {

    typedef Point *PointPtr;
    typedef struct Node *NodePtr;



    struct Node {
        PointPtr pointPointer;         // Pointer to each Node's Point object
        NodePtr nextNode;             // Pointer to next node in the list
    };

    class Cluster {
        unsigned size;                       // number of nodes in cluster (# of Point objects)
        std::forward_list<Point> head;       // pointer to first node
        unsigned dimension;
        Point __centroid;
        bool validCentroid = false;
        unsigned int __id;


    public:
        friend class KMeans;

        static const char POINT_CLUSTER_ID_DELIM = ':';

        Cluster() : size(0), dimension(0), __centroid(dimension), __id(idGenerate()) { head.clear(); }
        Cluster(unsigned dim) : size(0), dimension(dim), __centroid(dim), __id(idGenerate()) { head.clear(); }

        static unsigned int idGenerate();

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(Cluster &);
        Cluster &operator=(Cluster &);
        ~Cluster();

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const Point &);
        void remove(const Point &) throw (RemoveFromEmptyEx);

        const Point& setCentroid(const Point &);
        const Point getCentroid() const;
        const Point& computeCentroid() throw (RemoveFromEmptyEx);

        // Overloaded operators

        Point &operator[](unsigned) throw (OutOfBoundsEx);      // Overloaded [] index operator
        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        // - Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point

        // Set-destructive operators (duplicate points in the space)
        // - Friends
        friend const Cluster operator+(Cluster &lhs, Cluster &rhs);
        friend const Cluster operator-(Cluster &lhs, Cluster &rhs);

        friend const Cluster operator+(Cluster &lhs, PointPtr &rhs);
        friend const Cluster operator-(Cluster &lhs, PointPtr &rhs);

        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        void pickPoints(int k, Point [] );

        unsigned getSize();
        unsigned getDimension();

        double intraClusterDistance();

        friend double interClusterDistance(Cluster &c1, Cluster &c2);

        int getClusterEdges();

        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);

        bool contains(const Point &);

        class Move
        {
        public:
            Move(){}

            Move(const Point &ptr, Cluster* &from, Cluster* &to);

        private:
            void perform();                                     // helper functions
            Point toMove;
            Cluster* origin;
            Cluster* destination;

        };

    } ;

}
#endif //CLUSTERING_CLUSTER_H


