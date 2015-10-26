#include <iostream>
#include "Point.h"
#include "Cluster.h"

#include <fstream>
#include <sstream>

using namespace std;
using namespace Clustering;


int main() {


    ifstream myFile("/home/marisa/Projects/interm program/pa2/points.txt");


    if (myFile.is_open())
    {
        Cluster c(5);
        myFile >> c;

        std::cout << "c: " << std::endl << c << std::endl;

        cout << c.getCentroid();
    }
    else if (myFile.fail())
    {
        cout << "File didn't open";
    }

    Cluster c1;

    Point p(3);
    PointPtr ptr = &p;
    p.setValue(1,3.4);
    p.setValue(2,5.5);
    p.setValue(3,2.4);

    c1.add(ptr);
    cout << c1;



    myFile.close();





    return 0;
}