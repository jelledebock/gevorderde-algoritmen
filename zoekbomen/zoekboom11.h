#ifndef __ZOEKBOOM_H
#define __ZOEKBOOM_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>

using std::ostream;
using std::unique_ptr;

/**********************************************************************

   Class: Zoekboom
   
   beschrijving: Binaire zoekboom waarin geen duplicaatsleutels zijn toegestaan.
   
***************************************************************************/

template <class Sleutel,class Data>
class Zoekknoop;

template <class Sleutel,class Data>
class Zoekboom : public unique_ptr<Zoekknoop<Sleutel,Data>>{
public:
    Zoekboom(){};

    Zoekboom(Zoekknoop<Sleutel, Data> *knoop){
        this->reset(knoop);
    };

    Zoekboom(Zoekboom &&boom){
        if(*boom != *this){
            this = new Zoekknoop<Sleutel, Data>((*boom)->sleutel, (*boom)->data);
            Zoekknoop<Sleutel, Data> *foo = boom.release();
            delete foo;
        }
    };
    //Copy constructor is voorlopig niet aan de orde: dan zou je ook knopen moeten kunnen kopiëren : Zoekboom(Zoekboom &boom);
    void voegtoe(const Sleutel& sleutel,const Data& data);
    Zoekboom<Sleutel,Data>& operator=(Zoekboom<Sleutel,Data> &&other){
        if(other!=*this){
            (*this)->sleutel = other->sleutel;
            (*this)->data = other->data;
        }
        return *this;
    }

    friend ostream& operator<<(ostream &, const Zoekboom &);
protected:
//zoekfunctie zoekt sl en geeft de boom in waaronder de sleutel zit (eventueel een lege boom als de sleutel
//ontbreekt) en de pointer naar de ouder (als die bestaat, anders nulpointer).
//noot: alhoewel de functie niets verandert aan de boom is ze geen const functie.
    void zoek(const Sleutel& sleutel, Zoekknoop<Sleutel,Data>*& ouder, Zoekboom<Sleutel,Data>*& plaats);
};

template <class Sleutel, class Data>
ostream& operator<<(ostream & out, const Zoekboom<Sleutel, Data> &boom){
    if(*boom){
        out<<"Knoop: "<<(*boom);
        out<<"Ouder: "<<(*boom)->ouder;
        out<<"Data: "<<(*boom)->data;

        //kinderen
        Zoekboom<Sleutel, Data> volgende = (*boom)->links;

        while(*volgende){
            out<<"Knoop: "<<(*volgende);
            out<<"Ouder: "<<(*volgende)->ouder;
            out<<"Data: "<<(*volgende)->data;
            volgende = (*volgende)->links;
        }
    }
    return out;
}

template <class Sleutel,class Data>
class Zoekknoop {
    friend class Zoekboom<Sleutel,Data>;
    protected:
        Sleutel sleutel;
        Data data;
        Zoekknoop<Sleutel,Data>* ouder;
        Zoekboom<Sleutel,Data> links,rechts;
        Zoekknoop():ouder(0){}
        Zoekknoop<Sleutel,Data>(Sleutel sleutel, Data data){
            this->sleutel = sleutel;
            this->data = data;
        };
};

template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::voegtoe(const Sleutel& sleutel,const Data& data){
    Zoekboom<Sleutel,Data>* plaats;
    Zoekknoop<Sleutel,Data>* ouder;
    zoek(sleutel, ouder, plaats);
    if (!plaats){
        Zoekboom<Sleutel,Data> nieuw(new Zoekknoop<Sleutel,Data>(sleutel,data));
        nieuw->ouder=ouder;
        *plaats=move(nieuw);
    };
    
};

template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::zoek(const Sleutel& sleutel, Zoekknoop<Sleutel,Data>*& ouder, Zoekboom<Sleutel,Data>*& plaats){
    plaats=this;
    while (*plaats && (*plaats)->sleutel !=sleutel){
        if ((*plaats)->sleutel < sleutel)
            plaats=&(*plaats)->rechts;
        else
            plaats=&(*plaats)->links;
    };
};
#endif
