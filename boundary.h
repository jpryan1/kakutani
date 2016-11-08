#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
class Boundary
{
    public:
    Boundary(float e) : epsilon(e){
//        lookup = new Point[500*500];
//        memset(lookup,-1,500*500*sizeof(Point));
//        
    }
    
    virtual float distanceToBoundary(Point p) = 0;//returns negative if outside
    
    virtual Point closestPoint(Point p) = 0; //returns closest point on boundary to p
    virtual float boundaryValue(Point exit) = 0; //must be in [0,1]
    
    int insideBoundary(Point p){
        return distanceToBoundary(p)>epsilon;
    }
    
    Point walkOnSphere(Point p);
    
    Point exitPoint(Point start);
   
    float expectationOfBrownian(Point start, int iterations);
    
    protected: //xcode is automatically dedenting subsequent lines o_O
    
    float epsilon;
   // Point* lookup;
    
    
};

class Rectangle : public Boundary{
    public:
    Rectangle(Point tl, Point br, float* bv, float e) :
    Boundary(e), top_left(tl), bottom_right(br), boundValues(bv),
    width(br.y-tl.y), height(br.x-tl.x){}

    float distanceToBoundary(Point p);//returns negative if outside
    
    Point closestPoint(Point p); //returns closest point on boundary to p
    
    float boundaryValue(Point exit); //must be in [0,1]
    
    
    protected:
    
    Point top_left;
    Point bottom_right;
    int width, height;
    
    // boundaryValues is an array of size 8. Each edge in
    // the rectangle gets an ordered pair (v1, v2) of values,
    // v1 is the value of the first endpoint (counterclockwise)
    // and v2 is the value of the other endpoint. The value of a
    // point on the edge is then a linear interpolation of the values
    // of the endpoints.
    float* boundValues;
    // The correspondence is
    // top edge:   v0 v1
    // left edge:  v2 v3
    // bottom edge v4 v5
    // right edge  v6 v7
    
    
};


class Circle : public Boundary{
    public:
    Circle(Point c, float r, float e) :
    Boundary(e), center(c), radius(r){}
    
    float distanceToBoundary(Point p);//returns negative if outside
    
    Point closestPoint(Point p); //returns closest point on boundary to p
    
    float boundaryValue(Point exit); //must be in [0,1]
    
    
protected:
    
    Point center;
    float radius;
    
    
  
    
    
};


class Polygon : public Boundary{
    public:
    Polygon(vector<Point> p, float e) : Boundary(e), points(p){
        distances = new float[500*500];
        initDistances();
    }
    ~Polygon(){
        delete(distances);
    }
    
    void initDistances();
    float distanceHelper(Point p);
    float distanceToBoundary(Point p);//returns negative if outside
    
    float distanceToSegment(Point p, Point a, Point b);
    int insidePolygon(Point p);
    Point closestPoint(Point p); //returns closest point on boundary to p
    float boundaryValue(Point exit); //must be in [0,1]
 
protected:
    float* distances;

    vector<Point> points;
    Point r,s; //distanceToSegment sets these,
                //and closestPoint gets them
//    float* distances;
    
    
};

class Mandelbrot : public Boundary{
public:
    Mandelbrot(float e) : Boundary(e){
        distances = new float[500*500];
        initDistances();
    }
    ~Mandelbrot(){
        delete(distances);
    }
    
    void initDistances();
    float distanceHelper(Point p);
    float distanceToBoundary(Point p);//returns negative if outside
    Point closestPoint(Point p); //returns closest point on boundary to p
    float boundaryValue(Point exit); //must be in [0,1]
    float* distances;
protected:
    
    
    
};









