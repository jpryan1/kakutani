
#include "boundary.h"

Point Boundary::walkOnSphere(Point p){
    float radius = distanceToBoundary(p);
    float ang = rand()*2*3.141592653;
    return Point(p.x+radius*cos(ang), p.y + radius*sin(ang));
}

Point Boundary::exitPoint(Point start){
    Point current = start;
    while( insideBoundary(current)){
        current = walkOnSphere(current);
    }
    return closestPoint(current);
}


float Boundary::expectationOfBrownian(Point start, int iterations){
    float sum = 0;
    Point exit;
    for(int i=0;i<iterations;i++){
        exit = exitPoint(start);
        sum += boundaryValue(exit);
    }
    return sum/iterations;
    
}


float Rectangle::distanceToBoundary(Point p){
    return min( p.x - top_left.x, min(p.y-top_left.y,
            min( bottom_right.x-p.x, bottom_right.y-p.y)));
}


Point Rectangle::closestPoint(Point p){ //returns closest point on boundary to p
    if(p.x-top_left.x<=epsilon){
        return Point(top_left.x,p.y);
    }
    else if(p.y-top_left.y<=epsilon){
        return Point(p.x,top_left.y);
    }
    else if(bottom_right.x-p.x<=epsilon){
        return Point(bottom_right.x,p.y);
    }
    else{
        return Point(p.x, bottom_right.y);
    }
}

float Rectangle::boundaryValue(Point p){ //must be in [0,1]
    float lambda;
    if(p.x == top_left.x){
        lambda = (p.y-top_left.y)/(width + 0.0);
        return boundValues[0]*lambda + boundValues[1]*(1-lambda);
    }else if(p.y == top_left.y){
        lambda = (bottom_right.x - p.x)/(height + 0.0);
        return boundValues[2]*lambda+ boundValues[3]*(1-lambda);
    }else if(p.x == bottom_right.x){
        lambda = (bottom_right.y - p.y)/(width + 0.0);
        return boundValues[4]*lambda+ boundValues[5]*(1-lambda);
    }else{
        lambda = (p.x - top_left.x)/(height + 0.0);
        return boundValues[6]*lambda+ boundValues[7]*(1-lambda);
        
    }
}



float Circle::distanceToBoundary(Point p){
    Point q = p - center;
    return radius - norm(q);
}

Point Circle::closestPoint(Point p){
    Point q = p - center;
    double qnorm =  norm(q);
    Point r = Point(radius*q.x/qnorm, radius*q.y/qnorm);
    return r+center;
    
    
}
float Circle::boundaryValue(Point exit){
//    float x = (exit.y+0.0)/exit.x;
//    float angle = atan(x);
//    return (cos(angle)+1)/2.0;
//    
    if(exit.y<center.y&&exit.x<center.x) return 1;
     if(exit.y>center.y&&exit.x>center.x) return 1;
    return 0;
}










