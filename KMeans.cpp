//
// Created by marisa on 11/8/15.
//

#include "KMeans.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;



namespace Clustering {

    KMeans::KMeans() {

         point_space = new Cluster;

        cout << endl << "point_space assigned a cluster" << endl;

    }

    KMeans::KMeans(unsigned kValue, unsigned dim): k(kValue) , dimension(dim)
    {
        point_space = new Cluster(dimension);

        cout << endl << "point space assigned cluster with dimension: " << dim << "    k value: " << k << endl;

    }

    // will implement the so called Beta-CV criterion (stands for coefficient of variation).
    // This is an internal criterion, that is, it only uses the data in the clustering, and
    // no external data. Beta-CV is a ratio of the mean intra-cluster (inside the cluster)
    // distance to the mean inter-cluster (between cluster) distance. The smaller it is, the better.

    double KMeans::computeClusteringScore(Cluster myClusters []) {

        double dIn(0) , dOut(0) , pIn(0) , pOut(0) , betaCV(0);
        double denomenator(0) , numerator(0);

        cout << endl << "Entering computeClusteringScore" << endl;

        for (int i = 0; i < k ; i++)
        {
            dIn += ( myClusters[i].intraClusterDistance() );
        }

        cout << endl << " dIn: " << dIn << endl;


        for (int j = 0 ; j < k; j++)
        {
            for (int m = 0 ; m < k; m++)
            {
                dOut += ( interClusterDistance( (myClusters[j] ) , myClusters[m] ) );
            }
        }

        cout << endl << "dOut: " << dOut << endl;

        for (int n = 0; n < k; n++)
        {
            pIn += ( myClusters[n].getClusterEdges() );
        }

        cout << endl << "pIn: " << pIn << endl;

        for (int p = 0 ; p < k; p++)
        {
            for (int q = 0 ; q < k; q++)
            {
                pOut += ( interClusterEdges( myClusters[p],myClusters[q] ) );
            }
        }

        cout << endl << "pOut: " << pOut << endl;


        denomenator = dOut/pOut;
        numerator = dIn / pIn;


        betaCV = numerator/denomenator;

        cout << endl << "score = " << betaCV << endl;

        return betaCV;
    }


    std::istream &operator>>(istream &istream1, KMeans & means) {

        istream1 >> (*(means.point_space));

        cout << endl << "File done transferring points. Our KMeans cluster is of ";

        means.dimension = (*(means.point_space)).getDimension();

        cout << means.dimension << " dimensions. " << endl;


        cout << endl << "Point Space:" << *means.point_space << endl;
        return istream1;
    }

    double KMeans::clusteringAlgor(KMeans & means) {


        if (k == 0)
        {
            unsigned getK;

            cout << "Please set k ( the number of clusters to seperate data into) : ";
            cin >> getK;
            k = getK;
        }

        else
            cout << endl << "k equals " << k << endl;


        Point fillCentroid[k];

        Point *pointer = fillCentroid;

        for (int e = 0; e < k ; e++)
        {
            fillCentroid[e] = Point(means.dimension);
        }


        means.point_space->pickPoints(k ,pointer);

        cout << endl << "Pick points result: ";

        for (int counter = 0; counter < k ; counter++)
        {
            cout << endl << fillCentroid[counter] << endl;
        }

        Cluster emptyClusters[k];

        for (int f = 0; f < k ; f++)
        {
            emptyClusters[f].dimension = means.dimension;
        }

        for (int i = 0; i < k; i++)
        {
            emptyClusters[i].setCentroid(fillCentroid[i]);
            cout << endl << "Empty Cluster " << i+1 << " has centroid: " << emptyClusters[i].__centroid << endl;
        }


        double score=0;
        double scoreDiff = SCORE_DIFF_THRESHOLD + 1;

        double minDistance = 10000;
        double readDistance = 0;

        PointPtr pointToMove = nullptr;
        ClusterPtr toCluster = nullptr;
        NodePtr current;


        for (scoreDiff ; scoreDiff > SCORE_DIFF_THRESHOLD ; scoreDiff = (abs(scoreDiff-score)) )
        {
            for (current=means.point_space->head; current!= nullptr ; current = current->nextNode)
            {
                for ( int j = 0 ; j < k ; j++)
                {
                       readDistance = (*(current->pointPointer)).distanceTo(emptyClusters[j].__centroid);
                        cout << endl << " Distance between " << (*(current->pointPointer)) << " and " << emptyClusters[j].__centroid << " = " << readDistance << endl;

                       if (readDistance < minDistance)
                       {
                           pointToMove = current->pointPointer;
                           toCluster = &emptyClusters[j];
                           minDistance = readDistance;
                           cout << endl << " new minDistance = " << minDistance << endl;
                       }

                }

                Cluster::Move(pointToMove, means.point_space , toCluster);
                minDistance = 10000;
            }

            score = computeClusteringScore(emptyClusters);
        }

        ofstream outStream;
        outStream.open("/home/marisa/Projects/interm program/pa2/ClusterData.txt") ;

        if (outStream.fail() )
        {
            cout << "Output file opening failed.\n" ;
        }
        else
        {
            cout << "Output file opened";
            for (int z = 0; z < k; z++)
            {
                outStream << emptyClusters[z] << endl;
            }
        }

        outStream.close();


        return scoreDiff;

    }
}
