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
        int size;               // number of nodes in cluster (# of Point objects)
        NodePtr head;           // pointer to first node
        int dimension;
        Point __centroid;
        bool validCentroid = true;
        unsigned int __id;


    public:



        class Move
        {
        public:
            Move(){}

            Move(const PointPtr &ptr, Cluster *from, Cluster *to);

            void perform();

        private:
            Point* toMove;
            Cluster* origin;
            Cluster* destination;

        };
        static const char POINT_CLUSTER_ID_DELIM = ':';

        Cluster() : size(0), head(nullptr), dimension(0), __centroid(dimension), __id(idGenerate()) {}
        Cluster(int dim) : size(0), head(nullptr), dimension(dim), __centroid(dim), __id(idGenerate()) {}

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

        // IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);

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

        void pickPoints(int k, PointPtr *pointArray);

    } ;

}
#endif //CLUSTERING_CLUSTER_H

