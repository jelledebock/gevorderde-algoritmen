#ifndef __PUNTGENERATOR_H
#define __PUNTGENERATOR_H

class Puntgenerator{
public: Puntgenerator():a(0),d(0.5),q(1),r(1.008){};
    double geefpunt(){
        return (a+d<q?(a+=d)*sin(r):(a=-d,d*=r,q*=r*r));
    }
protected:
    double  a;
    double r,q,d;
};

#endif

