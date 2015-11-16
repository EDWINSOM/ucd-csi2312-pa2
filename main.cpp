#include <iostream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"

#include <fstream>
#include <sstream>

using namespace std;
using namespace Clustering;

const double KMeans::SCORE_DIFF_THRESHOLD = 10;

int main() {

    KMeans instance;

    ifstream myFile("/home/marisa/Projects/interm program/pa2/points.txt");


    if (myFile.is_open())
    {
        myFile >> instance;

    }
    else if (myFile.fail())
    {
        cout << "File didn't open";
    }

    instance.clusteringAlgor(instance);

    myFile.close();



    return 0;
}
