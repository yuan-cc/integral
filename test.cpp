#include <iostream>
#include <cmath>
#include <functional>
#include "integral.h"
using namespace std;

double foo(double x,double spec[],int m)
{
    return spec[m]*x;
}

class test_class{
    public:
        double member_function(double a);
};

double test_class::member_function(double a)
{
    return a+1;
}

int main()
{
    int max_iteration=5,m=1;
    double spec[3]={1,2,3};

    double relative_error=0.01,integral_up=1.0, integral_down=0.0;
    // with parameters
    cout<<adaptiveSimpsons1(bind(foo,placeholders::_1,spec,m),integral_down,integral_up,relative_error,max_iteration)<<endl;

    // use member function as an integrand
    test_class temp;
    cout<<adaptiveSimpsons1(bind(&test_class::member_function,&temp,std::placeholders::_1),integral_down,integral_up,relative_error,max_iteration)<<endl;
    return 0;
}

