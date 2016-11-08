#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main(){
    Size s(500,500);
    VideoWriter v("video.avi", CV_FOURCC('M', 'P', '4', 'V'), 30, s);
    Mat image(500,500,CV_8UC3);
    
    for(int i=0; i<500; i++){
        for(int j=0; j<500; j++){
            image.at<Vec3b>(i,j) = Vec3b(255,255,255);
        }
    }
    int x = 250;
    int y = 250;
    int r;
    for(int i = 0; i<100;i++){
        v<<image;
        image.at<Vec3b>(x,y) = Vec3b(0,0,0);
        r = rand()%4;
        switch(r){
            case 0:
                x++;
                break;
            case 1:
                y++;
                break;
            case 2:
                x--;
                break;
            case 3:
                y--;
                break;
            default:
                break;
        }
        if(x<0||y<0||x>=500||y>=500) break;
    }
    v.release();
    return 0;
    
}

