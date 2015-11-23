//
// Created by marisa on 11/8/15.
//

#ifndef PA2_KMEANS_H
#define PA2_KMEANS_H

#include "Cluster.h"


namespace Clustering {

    typedef Cluster* ClusterPtr;

    class KMeans {

        ClusterPtr point_space = nullptr;
        PointPtr centroidSelection = nullptr;
        unsigned k = 0;
        unsigned dimension = 0;

    public:

        // used in a termination condition
        static const double SCORE_DIFF_THRESHOLD;

        KMeans();

        KMeans(unsigned kValue, unsigned dim);


        double computeClusteringScore(Cluster  []);

        friend std::istream &operator>>(std::istream &, KMeans &);

        double clusteringAlgor(KMeans & means);

    };
}


#endif //PA2_KMEANS_H
