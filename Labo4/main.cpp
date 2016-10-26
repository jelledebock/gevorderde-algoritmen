/* 
 * File:   main.cpp
 * Author: jelle
 *
 * Created on October 18, 2016, 6:40 PM
 */

#include <cstdlib>
#include "btree.h"
#include "schijf.h"
#include <fstream>

using namespace std;

struct Woord{
    string woord;
    
    bool operator<(const struct Woord &w) const{
        return (this->woord.compare(w.woord)<0?true : false);
    }
    
    bool operator>(const struct Woord &w) const{
        return (this->woord.compare(w.woord)>0?true : false);
    }
     
    bool operator==(const Woord &w) const{
        return this->woord.compare(w.woord)==0;
    }
};

int main(int argc, char** argv) {
    //Maak een schijf aan (met een knoop met als key het aantal voorkomens (int) en als data het eigenlijke woord (string)
    Schijf< Bknoop<Woord,int, 4u>> don_quichote_schijf;
    //Maak btree aan die gebruik maakt van deze schijf
    Btree<Woord,int ,4u> don_quichote_tree(don_quichote_schijf);
    
    ifstream input;
    input.open(argv[1]);
    if(!input){
        cerr << "File niet gevonden!" <<endl;
        exit(1);
    }
    string woord;
    input >> woord;
    
    while(!input.eof()){
        Woord w;
        w.woord = woord;
        //Zoek of woord reeds aanwezig is
        int aantal_keer = don_quichote_tree.zoek(w);
        //Voeg toe of update
        don_quichote_tree.voegtoe(w, aantal_keer+1);
        
        input>>woord;
    }   
    
    input.close();
    
    return 0;
}

