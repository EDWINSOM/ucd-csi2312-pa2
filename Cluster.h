// Can have arbitrary number of Nodes that hold one Point each



#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"

namespace Clustering {

    typedef Point *PointPtr;
    typedef struct Node *NodePtr;



    struct Node {
        PointPtr pointPointer;         // Pointer to each Node's Point object
        NodePtr nextNode;             // Pointer to next node in the list
    };

    class Cluster {
        unsigned size;               // number of nodes in cluster (# of Point objects)
        NodePtr head;           // pointer to first node
        unsigned dimension;
        Point __centroid;
        bool validCentroid = false;
        unsigned int __id;


    public:
        friend class KMeans;

        static const char POINT_CLUSTER_ID_DELIM = ':';

        Cluster() : size(0), head(nullptr), dimension(0), __centroid(dimension), __id(idGenerate()) {}
        Cluster(unsigned dim) : size(0), head(nullptr), dimension(dim), __centroid(dim), __id(idGenerate()) {}

        static unsigned int idGenerate();

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(Cluster &);
        Cluster &operator=(Cluster &);
        ~Cluster();

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);

        const Point& setCentroid(const Point &);
        const Point getCentroid() const;
        const Point& computeCentroid();

        // Overloaded operators


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

        void pickPoints(int k, Point []);

        unsigned getSize();
        unsigned getDimension();

        double intraClusterDistance() const;

        friend double interClusterDistance(const Cluster &c1, const Cluster &c2);

        int getClusterEdges();

        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);


        class Move
        {
        public:
            Move(){}

            Move(const PointPtr &ptr, Cluster *from, Cluster *to);

        private:
            void perform();                                     // helper functions
            Point* toMove;
            Cluster* origin;
            Cluster* destination;

        };

    } ;

}
#endif //CLUSTERING_CLUSTER_H


