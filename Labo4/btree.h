#ifndef __BTREE
#define __BTREE
#include "schijf.h"
#include <iostream>
#include <stack>

using std::endl;
using std::cerr;
using std::ostream;
//Dit bestand bevat code en hoofdingen van
template<class T, class D,unsigned int m>
class Btree;
template<class T,class D,unsigned int m>
class Bknoop;
//betekenis m: zie cursus

//crashtest voorkomt dat er meer dan drie knopen in het 'geheugen' zitten.
//dit veronderstelt wel dat er nooit knopen op de Schijf gedeletete worden,
template<class T,class D,unsigned int m>
class Bknoop{
friend class Btree<T,D,m>;
public:
    Bknoop<T,D,m>(){4/(-4+ ++crashtest);};
    ~Bknoop<T,D,m>(){--crashtest;};

    const Bknoop<T,D,m>& operator=(const Bknoop<T,D,m>& b){
        k=b.k;
        isblad=b.isblad;
        for (unsigned int i=0;i<k;i++){
            sleutel[i]=b.sleutel[i];
            data[i]=b.data[i];
        }
        if (!isblad){
            for (unsigned int i=0;i<=k;i++){
                index[i]=b.index[i];
            }
        }
        return *this;
    }
    //opmerking: sleutel[0] en data[0] worden niet gebruikt, zodat indexen vanaf 1 lopen
    T sleutel[m];
    D data[m];
    blokindex index[m];
    unsigned int k;
    bool isblad;
private:
    static int crashtest;
};
template<class T,class D,unsigned int m>
int Bknoop<T,D,m>::crashtest=0;


template<class T, class D,unsigned int m>
class Btree{
    typedef Bknoop<T,D,m> Knoop;
public:
    Btree(Schijf<Knoop>& s):schijf(s){
        wortel.k=0;
        wortel.isblad=true;
        wortelindex=schijf.schrijf(wortel);
    }
    //zoek de knoop in de boom, gegeven de data
    D zoek(T key);
    D zoek(T key, std::stack<unsigned int>& pad);
    //voegt een knoop toe
    void voegtoe(T key, D data);
    //Verwijdert een gegeven knoop
    Knoop verwijder(T key);
    

private:
   Schijf<Knoop>& schijf;
   Knoop wortel;
   blokindex wortelindex;
};

//Zoek een knoop in de B-tree en geef zijn Data terug indien deze bestaat
template<class T, class D,unsigned int m>
D Btree<T,D,m>::zoek(T key, std::stack<unsigned int>& path){
    Knoop knoop;
    schijf.lees(knoop, wortelindex);
    //Zoek in sleutels
    int i=1;
        
    while(i<=knoop.k){
        if(knoop.sleutel[i]==key){
            return knoop.data[i];
        }
        else if(knoop.sleutel[i]>key){
            if(!knoop.isblad){
                path.push(knoop.index[i]);
                schijf.lees(knoop, knoop.index[i]);
                i=1; 
            }
            else{
                return 0;
            }
        }
        else{
            i++;
        }
    }
    return 0;
}

template<class T, class D,unsigned int m>
void Btree<T,D,m>::voegtoe(T key, D data){
   
}


template<class T, class D,unsigned int m>
Bknoop<T,D,m> Btree<T,D,m>::verwijder(T key){}

#endif
