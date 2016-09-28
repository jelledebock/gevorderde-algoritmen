#include <iostream>
#include "zoekboom11.h"

using namespace std;

int main(int argc, char *argv[])
{
    Zoekboom <int, string> boom;

    boom.voegtoe(1,"jelle");
    boom.voegtoe(2,"tomas");
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
    return 0;
}
