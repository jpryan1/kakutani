#include <string>
#include <stdio.h>

#include "boundary.h"


using namespace std;
using namespace cv;

int main(){
    double duration;
    clock_t start = clock();
    
    Mat image(500,500,CV_32FC3);
    
    float temp;
    float epsilon = 2;
    int iterations = 1000;
//    float bv[8];
//    bv[0]=1;
//    bv[1]=1;
//    bv[2]=0;
//    bv[3]=0;
//    bv[4]=0.5;
//    bv[5]=0.5;
//    bv[6]=0;
//    bv[7]=0;
   
//    Rectangle rect(Point(150,150),Point(350,350),
//                   bv, epsilon);
//    
    
    Circle circle(Point(250,250),200, 2);
    Point p;
    for(int i=0; i<500; i++){
        for(int j=0; j<500; j++){
            p = Point(i,j);
            if(!circle.insideBoundary(p)){
                continue;
            }
            temp = circle.expectationOfBrownian(p, iterations);
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
    applyColorMap(colorImage, c, COLORMAP_JET);
    imshow("Display", c);
    waitKey(0);
    return 0;
    
}
