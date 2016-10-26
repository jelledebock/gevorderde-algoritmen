/* 
 * File:   main.cpp
 * Author: jelle
 *
 * Created on October 26, 2016, 9:03 AM
 */

#include <cstdlib>
#include <iostream>

#include "Boom2D.h"

using namespace std;

void zoek_dichtste_test(Boom2D boom);

int main(int argc, char** argv) {
    Boom2D boom;
    boom.lees_punten("puntenverz.txt");
    
    zoek_dichtste_test(boom);
    cout<<"Punt (0,20) in tree? "<<(boom.zoek_punt(0,20)?"Ja":"Nee")<<endl;
    cout<<"Punt (0,30) in tree? "<<(boom.zoek_punt(0,30)?"Ja":"Nee")<<endl;

    return 0;
}

void zoek_dichtste_test(Boom2D boom){
    for(int i=0;i<200;i+=10){
        for(int j=0;j<200;j+=10){
            punt2 punt(i,j);
            std::pair<int, Node2D*> dichtste = boom.zoek_dichtste(i,j);
            cout << "punt2" << punt << " heeft buur " <<  *(dichtste.second) << ", gevonden in" << setw(5) << dichtste.first << " doorzochte knopen" << endl;
        }
    }
}

