
#include <iostream>
#include <complex>
#include <math.h>

using namespace std;


float distanceHelper(float x, float y);


int main(){

	cout<<distanceHelper(300,430)<<endl;

	return 0;
}

float distanceHelper(float x, float y){
    

    complex<float> c( (x-250.0)*(1/100.0), (y-250.0)*(1/100.0) );
    complex<float> z(0.0, 0.0);
    complex<float> dz(0.0, 0.0);
    
//        Complex z( 0.0f, 0.0f );
//        Complex dz( 0.0f, 0.0f );
//
    float m2;

    for( int i=0; i<1024; i++ ){
	
        dz = 2.0f*z*dz + 1.0f;
        z = z*z + c;
        m2 = pow(z.real(),2)+pow(z.imag(),2);
cout<<z<<" "<<m2<<endl;
        if( m2>1e19 )
            break;
    }
	
//        // distance estimation: G/|G'|
    return sqrtf( m2/( pow( dz.real(),2 )+pow(dz.imag(),2) ))*0.5*logf(m2);
}
