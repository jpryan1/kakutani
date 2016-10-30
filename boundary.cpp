
#include "boundary.h"
#include "winding.h"


//TODO consider for polygon precomputing distance of all pixels inside., especially if planning on varying boundary values for same shape


Point Boundary::walkOnSphere(Point p){
    float radius = distanceToBoundary(p);
    float ang = rand()*2*3.141592653;
    return Point(p.x+radius*cos(ang), p.y + radius*sin(ang));
}

Point Boundary::exitPoint(Point start){
    Point current = start;
   
    while(insideBoundary(current)){
        
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






float Polygon::distanceToSegment(Point p, Point a, Point b){
    
    //Assumption is that, if a is (0,0) and b is (1,0)
    // then (0.5, 1) is inside and (0.5, -1) is outside.
    
    //Border case, if the point is collinear with the
    //line segment, then we return 10000; Basically,
    //this will cause distanceToBoundary to ignore it,
    //and the closest segment will be the one connected
    //to ab, with which p cannot also be collinear.
    //Yes, this is a hack.
    
    //Also, I'jb
    float distance;
    int px, py, ax, ay, bx, by, apx, apy, abx, aby, bpx, bpy;
    double ux,uy;
    px = p.x;
    py = p.y;
    ax = a.x;
    ay = a.y;
    bx = b.x;
    by = b.y;
    apx = px-ax;
    apy = py-ay;
    abx = bx-ax;
    aby = by-ay;
    bpx = px-bx;
    bpy = py-by;
    
//    Point ap = p-a;
    
//    Point ab = b-a;
//    float cross = ab.cross(ap);
    float cross = abx*apy-aby*apx;
    int sign = (cross > 0) - (cross < 0);//isn't this nice
  //  std::cout<<abx<<" "<<aby<<" "<<apx<<" "<<apy<<"\n";

//    float ab_norm = norm(ab);
    float ab_norm = sqrt(abx*abx+aby*aby);
//    Point ab_unit = Point(ab.x/ab_norm, ab.y/ab_norm);
    ux = abx/ab_norm;
    uy = aby/ab_norm;
    
    float dot = apx*ux+apy*uy;
    if(sign==0){
        if(dot>=0&&dot<=ab_norm){
            return 0;
        }return 10000;
    }
//    float dot = ap.dot(ab_unit);
    if(dot<0){
         //       distance = norm(ap);
        return sign*sqrt(apx*apx+apy*apy);//distance;
    }
    else if(dot > ab_norm){
        return sign*sqrt(bpx*bpx+bpy*bpy);//norm(p-b);
    }
    else{
        double x = apx-dot*ux;
        double y = apy-dot*uy;
        return sign*sqrt(x*x+y*y);//norm(ap-dot*ab_unit);
    }
}
Point Polygon::closestPoint(Point p){
//    double px,py,abx,aby,sx,sy,rx,ry,ux,uy,apy,apx;
//    px = p.x;py=p.y;sx=s.x;sy=s.y;rx=r.x;ry=r.y;
//    abx=sx-rx;aby=sy-ry;apx=px-rx;apy=py-ry;
////    Point ab = s-r;
////    Point ap = p-r;
//    float ab_norm = sqrt(abx*abx+aby*aby);//norm(ab);
//    
//    //Point ab_unit = Point( ab.x/ab_norm, ab.y/ab_norm);
//    ux=abx/ab_norm;
//    uy=aby/ab_norm;
//    float dot = apx*ux+apy*uy;//ap.dot(ab_unit);
//    if(dot<0) return r;
//    if(dot>ab_norm) return s;
//    return Point(rx+dot*ux,ry+dot*uy);//r + dot*ab_unit;
    
    return p;//for now, use this. Only consequence is that
    // boundaryValue(p) is defined less precisely
}






float Polygon::distanceToBoundary(Point p){
    if(p.x<0||p.y<0||p.x>499||p.y>499) std::cout<<"ERROR"<<std::endl;
    return distances[p.y+500*p.x];
//    r = points[points.size()-1];
//    s = points[0];
//    float min = distanceToSegment(p,
//                points[points.size()-1], points[0]);
//
//    float dist;
//    for(int i=0; i<points.size()-1;i++){
//        dist = distanceToSegment(p, points[i], points[i+1]);
//        if(std::abs(dist)<std::abs(min)){
//            min = dist;
//            r = points[i];
//            s = points[i+1];
//        }
//    }
//    return min;
}
float Polygon::boundaryValue(Point exit){
    if(exit.y+exit.x>500) return 1; //just make the right side hot, idk
    return 0;
}

int Polygon::insidePolygon(Point p){
    
    vector<Point> the_copy(points);
    Point repeat(points[0].x, points[0].y);
    the_copy.push_back(the_copy[0]);
    int flag = wn_PnPoly(p, (Point *) &the_copy[0], points.size());
    return flag;
    
    //find closest point
    //find next closest point, wrt orientation
    //check if point is on correct side of that side

    
    
    //This needs to be done properly, but it's giving me a lot of difficulty for some reason
    
//    int counter = 0;
//    
//    //cast a ray from wall, see how many segments intersected
//    Point a,b;
//    float proj;
//    int j;
//    for(int i=0;i<points.size();i++){
//        j = (i+1)%points.size();
//        if(points[i].y<points[j].y){
//            a = points[i];
//            b = points[j];
//        }else{
//            a = points[j];
//            b = points[i];
//        }
//        //b has larger y values
//        if(b.y>=p.y&&p.y>=a.y){ //if p is between them
//            //make sure p is to the left of the segment ab
//            if(b.y==a.y){
//                if((b.x-p.x)*(a.x-p.x)<0){
//                    counter++;
//                }
//            }else{
//                proj = (p.y-a.y)/(b.y-a.y);
//                proj = a.x + proj*(b.x-a.x);
//                if(proj<=p.x){
//                    counter++;
//                }
//            }
//        }
//    }
//
//    return counter%2;
}



float Polygon::distanceHelper(Point p){
    
   
    
    float min = distanceToSegment(p,
                                  points[points.size()-1], points[0]);
    
    
    float dist;
    int flag = 0;
    for(int i=0; i<points.size()-1;i++){
        dist = distanceToSegment(p, points[i], points[i+1]);
        
        if(std::abs(dist)<std::abs(min)){
            flag = 0;
            min = dist;
        }else if(std::abs(dist)==std::abs(min)){
            flag = 1;
        }
        
    }
    if(flag){
        if(insidePolygon(p)){
            min = abs(min);
        }else{
            return -1;
        }
    }
        //if flag is one, we don't know if its in or out.
       //std::cout<<p<<" got "<<rayTest(p)<<std::endl;
    return min;
}
void Polygon::initDistances(){
    
    for(int row = 0; row<500; row++){
        for(int col = 0; col<500; col++){
            distances[col+500*row] = distanceHelper(Point(row,col));
        }
    }
}













