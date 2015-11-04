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

        std::cout << std::endl << c << std::endl;

        cout << c.getCentroid();
    }
    else if (myFile.fail())
    {
        cout << "File didn't open";
    }

    Cluster c1;

    double points[3] = {1,2,3};
    double * sendIn = points;
    Point p(3, points);
    PointPtr pointer1 = &p;

    double points2[3] = {2,3,4};
    double * sendIn2 = points2;
    Point p2(3, points2);
    PointPtr pointer2 = &p2;

    double points3[3] = {3,4,5};
    double * sendIn3 = points3;
    Point p3(3, points3);
    PointPtr pointer3 = &p3;

    double points4[3] = {4,5,6};
    double * sendIn4 = points4;
    Point p4(3, points4);
    PointPtr pointer4 = &p4;

    double points5[3] = {5,6,7};
    double * sendIn5 = points5;
    Point p5(3, points5);
    PointPtr pointer5 = &p5;

    double points6[3] = {6,7,8};
    double * sendIn6 = points6;
    Point p6(3, points6);
    PointPtr pointer6 = &p6;

    double points7[3] = {7,8,9};
    double * sendIn7 = points7;
    Point p7(3, points7);
    PointPtr pointer7 = &p7;

    double points8[3] = {8,9,10};
    double * sendIn8 = points8;
    Point p8(3, points8);
    PointPtr pointer8 = &p8;

    double points9[3] = {9,10,11};
    double * sendIn9 = points9;
    Point p9(3, points9);
    PointPtr pointer9 = &p9;

    double points10[3] = {10,11,12};
    double * sendIn10 = points10;
    Point p10(3, points10);
    PointPtr pointer10 = &p10;

    double points11[3] = {11,12,13};
    double * sendIn11 = points11;
    Point p11(3, points11);
    PointPtr pointer11 = &p11;

    double points12[3] = {12,13,14};
    double * sendIn12 = points12;
    Point p12(3, points12);
    PointPtr pointer12 = &p12;


    c1.add(pointer1);
    c1.add(pointer2);
    c1.add(pointer3);
    c1.add(pointer4);
    c1.add(pointer5);
    c1.add(pointer6);
    c1.add(pointer7);
    c1.add(pointer8);
    c1.add(pointer9);
    c1.add(pointer10);
    c1.add(pointer11);
    c1.add(pointer12);

    cout << c1 << endl;

    cout << c1.getCentroid() << endl;





    myFile.close();





    return 0;
}