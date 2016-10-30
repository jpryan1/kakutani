#include <string>
#include <stdio.h>

#include "boundary.h"


using namespace std;
using namespace cv;

int main(){
  
    double duration;
    clock_t start = clock();
    
    

    vector<Point> vec;
    vec.push_back(Point(100,101));
    vec.push_back(Point(401,100));
    vec.push_back(Point(400,201));
    vec.push_back(Point(301,200));
    vec.push_back(Point(290,311));
    vec.push_back(Point(401,300));
    vec.push_back(Point(400,401));
    vec.push_back(Point(101,400));
    vec.push_back(Point(100,301));
    vec.push_back(Point(201,300));
    vec.push_back(Point(200,201));
    vec.push_back(Point(101,200));
 
    Mat image(500,500,CV_32FC3);
  
    float temp;
    float epsilon = 2;
    int iterations = 100;
   

//    Rectangle rect(Point(150,150),Point(350,350),
//                   bv, epsilon);

   // Circle circle(Point(250,250),200, 2);
    Polygon poly(vec, 2);
//    Mat im(500,500, CV_32FC1, poly.distances);
//    imshow("display",im);
//    waitKey(0);
//    return 0;
    
    Point p;
    for(int i=0; i<500; i++){
        for(int j=0; j<500; j++){
            p = Point(i,j);
            if(!poly.insideBoundary(p)){
                continue;
            }
            temp = poly.expectationOfBrownian(p, iterations);
          
//            temp*=5;
//            temp = round(temp);
//            temp/=5.0;
            image.at<Vec3f>(i,j) =Vec3f(temp,temp,temp);
        }
    }
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout<<"Elapsed time: "<<duration<<endl;
    Mat colorImage, c;
    image.convertTo(colorImage, CV_8UC3,255);
    applyColorMap(colorImage, c, COLORMAP_SPRING);
    imshow("Display", c);
    waitKey(0);
    return 0;
    
}
