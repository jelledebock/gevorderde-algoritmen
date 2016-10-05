/* 
 * File:   main.cpp
 * Author: Jelle De Bock
 *
 * Created on October 5, 2016, 6:31 PM
 */

#include <iostream>
#include "src/zoekboom11.h"

using namespace std;

int main(int argc, char *argv[])
{
    Zoekboom <int, string> boom;

    boom.voegtoe(3,"jelle");
    boom.voegtoe(1,"tomas");
    boom.voegtoe(4,"klaas");
    boom.voegtoe(54,"jan");
    boom.voegtoe(8,"korneel");
    boom.voegtoe(6,"alice");
    boom.voegtoe(4,"bob");
    boom.voegtoe(3,"mark");


    cout<<boom;
    cout<<"Diepte: "<<boom.getDiepte()<<endl;
    cout<<"# knopen: "<<boom.getAantalKnopen()<<endl;
    cout<<"Som diepte: "<<boom.getSomDiepte()<<endl;
    cout<<"Gemiddelde diepte: "<<boom.getGemiddeldeDiepte()<<endl;
    boom.roteer(true);
    cout<<"Na rotatie naar links: "<<endl;
    cout<<boom;
    return 0;
}
