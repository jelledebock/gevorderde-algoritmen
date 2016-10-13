
/* 
 * File:   bridges.h
 * Author: Jelle De Bock
 *
 * Created on October 13, 2016, 6:32 PM
 */

#ifndef BRIDGES_H
#define BRIDGES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;

class Brug{
public:
    Brug(int arena, int winkelcentrum, int premie){
        this->arena = arena;
        this->winkel = winkelcentrum;
        this->premie = premie;
    };
    int getPremie() const{
        return premie;
    };
    int getArena() const{
        return arena;
    };
    int getWinkel() const{
        return winkel;
    };
    bool operator<(const Brug& b2) const{
        return this->getPremie() < b2.getPremie(); };
private:
    int arena;
    int winkel;
    int premie;
};

class BruggenManager{
public:
    BruggenManager(string file);
    void optimaliseer_smeergeld();
    friend ostream& operator<<(ostream& out, BruggenManager& manager);
private:
    int maximaal_bedrag;
    int max_bruggen;
    vector<Brug> te_bouwen_bruggen;
    vector<Brug> voorstellen;
    Brug zoek_brug(int winkel);
};


BruggenManager::BruggenManager(string file){
    ifstream input(file);
    maximaal_bedrag=0;
    
    if(input.is_open()){
        input>>max_bruggen;
        int i = 0;
        
        while(i<max_bruggen && !input.eof()){
            int smeergeld, winkel_index;
            input>>smeergeld;
            input>>winkel_index;
            
            Brug voorstel(i,winkel_index,smeergeld);
            voorstellen.push_back(voorstel);
            
            i++;
        }
        
        optimaliseer_smeergeld();
    }
}

void BruggenManager::optimaliseer_smeergeld(){
    //We hebben 2-2d arrays nodig
    //1 houdt de cummulatieve bedragen bij
    //1 houdt de voorgangers bij.
    int bedragen[max_bruggen+1][max_bruggen+1];
    char voorganger[max_bruggen+1][max_bruggen+1];
    
    //Iinitialiseer extra rijen
    bedragen[0][0]=0;
    voorganger[0][0]='X';
    for(int i=1;i<max_bruggen+1;i++){
        bedragen[0][i]=0;
        bedragen[i][0]=0;
        
        voorganger[0][i]='L';
        voorganger[i][0]='B';
    }
    
    //Array is reeds gesorteerd op arena's
    //We bepalen dus de langste toenemende sequentie op basis van de winkelcentra
    for(int i=1;i<max_bruggen+1;i++){
        //per rij gaan we kijken waar de index i overeenkomt met de winkelcentrum index
        for(int j=1;j<max_bruggen+1;j++){
            int winkel_centrum = voorstellen[j-1].getWinkel();     //bepaal winkelcentrum overeenkomstig met de kolomindex
            //cout<<"i="<<i<<", winkelcentrum="<<winkel_centrum<<endl;
            if(winkel_centrum==i-1){//we moeten het bedrag verhogen van de voorganger verhogen
                //haal bedrag op diagonaal op
                int vorig_bedrag=bedragen[i-1][j-1];
                //Werk array bij
                bedragen[i][j]=vorig_bedrag+voorstellen[j-1].getPremie();
                voorganger[i][j]='X';
            }
            else{ //zoek of het hoogste bedrag links of boven ligt?
                int bedrag_links = bedragen[i][j-1];
                int bedrag_boven = bedragen[i-1][j];
                
                if(bedrag_links>bedrag_boven){
                    voorganger[i][j]='L';
                    bedragen[i][j]=bedrag_links;
                }
                else{
                    voorganger[i][j]='B';
                    bedragen[i][j]=bedrag_boven;
                }
            }
        }
    }
    
    // Handig om te debuggen : print de DP array uit 
      
    string voorgangers_array="";
    string bedragen_array = "";
    
    for(int i=0;i<max_bruggen+1;i++){
        for(int j=0;j<max_bruggen+1;j++){
            char richting = voorganger[i][j];
            stringstream ss;
            ss<<richting;
            string out;
            ss>>out;
            voorgangers_array+=""+out;
            bedragen_array+=to_string(bedragen[i][j]);
            
            voorgangers_array+=",\t";
            bedragen_array+=",\t";

        }
        voorgangers_array+="\n";
        bedragen_array+="\n";
    }
    
    cout<<"Voorgangers array..."<<endl<<voorgangers_array<<endl;
    cout<<"Bedragen...."<<endl<<bedragen_array;
        
    //We starten rechts onder en willen naar links boven, en telkens we diagonaal moeten springen voegen we ons winkelcentrum toe aan de opgenomen bedragen
    int i=max_bruggen;
    int j=max_bruggen;
    
    maximaal_bedrag = bedragen[max_bruggen][max_bruggen];
    
    //cout<<bedragen[max_bruggen][max_bruggen]<<" in the pocket!!!"<<endl;
    vector<int> keuze_centra;
    
    while(i>0 &&  j>0){
        char keuze = voorganger[i][j];
        
        //cout<<keuze<<" ("<<i<<","<<j<<")"<<"bedrag = "<<bedragen[i][j]<<endl;
        switch(keuze){
            case 'X':       //moet toevoegen aan ons langste duurste bruggensequentie
                cout<<"("<<i<<","<<j<<")"<<endl;
                te_bouwen_bruggen.push_back(zoek_brug(j));
                i--;
                j--;
                break;
            case 'L':
                j--;
                break;
            case 'B':
                i--;
                break;
        }
        
    }   
}

Brug BruggenManager::zoek_brug(int index){
    int i=0;
    while(i<voorstellen.size()){
        if(voorstellen[i].getWinkel()==index)
            return voorstellen[i];
        i++;
    }
}

ostream& operator<<(ostream& out, BruggenManager& manager){
    out<<"Bruggenmanager"<<endl;
    out<<"Maximaal smeergeld te cashen: "<<manager.maximaal_bedrag<<endl;
    if(manager.te_bouwen_bruggen.size()>0){
        out<<"Overzicht van bruggen bij maximale winst: "<<endl;
        for(auto brug : manager.te_bouwen_bruggen){
               out<<"\tBrug van arena "<<brug.getArena()<<" naar winkelcentrum "<<brug.getWinkel()<<" brengt "<<brug.getPremie()<<" op."<<endl;
        }
    }
    else{
        out<<"Beschikbare voorstellen: "<<endl;
        for(auto brug : manager.voorstellen){
               out<<"\tBrug van arena "<<brug.getArena()<<" naar winkelcentrum "<<brug.getWinkel()<<" brengt "<<brug.getPremie()<<" op."<<endl;
        }
    }
   
}

#endif /* BRIDGES_H */

