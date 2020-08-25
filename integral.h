#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <cmath>
using namespace std;


template< typename F>
double adaptiveSimpsonsAux1(F&& f,double a, double b, double epsilon,double S, double fa, double fb, double fc, int bottom) {
    double c = (a + b)/2, h = b - a;
    double d = (a + c)/2, e = (c + b)/2;
    double fd = f(d), fe = f(e);
    double Sleft = (h/12)*(fa + 4*fd + fc);
    double Sright = (h/12)*(fc + 4*fe + fb);
    double S2 = Sleft + Sright;
    if(S==0)return 0;
    if (bottom <= 0 || fabs(S2 - S)/abs(S) <= 15*epsilon) {
        //if( bottom <=0 );
        return S2 + (S2 - S)/15;
    }
    return adaptiveSimpsonsAux1(f,a, c, epsilon/2, Sleft,  fa, fc, fd, bottom-1) +
    adaptiveSimpsonsAux1(f, c, b, epsilon/2, Sright, fc, fb, fe, bottom-1);
}

//
// Adaptive Simpson's Rule
//
template< typename F>
double adaptiveSimpsons1(F&& f,double a, double b, double epsilon, int maxRecursionDepth) {   
    double c = (a + b)/2, h = b - a;
    double fa = f(a), fb = f(b), fc = f(c);
    double S = (h/6)*(fa + 4*fc + fb);
    return adaptiveSimpsonsAux1(f,a, b, epsilon, S, fa, fb, fc, maxRecursionDepth);
}                                                                                                   



#endif
