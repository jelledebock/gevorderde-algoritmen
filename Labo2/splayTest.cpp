#include "splayboomb.h"
#include <iostream>
#include "csv.h"
#include "puntgenerator.h"

using namespace std;

void splaytest(){
    	Splayboomb<int, char> s;
	s.voegtoe(1, 'a');
	s.voegtoe(9, 'b');
	s.voegtoe(2, 'c');
	s.voegtoe(8, 'd');
	s.voegtoe(3, 'e');
	s.voegtoe(7, 'f');
	s.voegtoe(4, 'g');
	s.voegtoe(6, 'h');
	s.voegtoe(5, 'i');
	
	
	cout << "Potentiaal voor splay's " << s.potentiaal() << endl;
	
	cout<<s;
	cout<<endl<<endl;
	
	int depth;
	char *d = s.zoek(5, depth);
	cout << "Potentiaal na splay's " << s.potentiaal() << endl;
	if (d) {
		cout << "found data " << *d << ", at depth of " << depth << endl;
	} else {
		cout << "no data found" << endl;
	}
	cout<<s;
	cout << endl << endl;
	
	
	int aantalDatapunten = 1000;
	int aantalMeetpunten = 50;
	cout << "Generating graphs..." << endl << "\tPotentiaal van in order, voor splayen... ";
	
    CsvData grafiek("meetigen", '.');
    Splayboomb<double, unsigned int> z1;
    vector<double> dieptedata;
    vector<double> potentiaalData;
    int aantal=0;
    for (int i=0; i < aantalDatapunten; i++ ){
        z1.voegtoe(i, i);
        aantal++;
        if (aantal * aantalMeetpunten >= aantalDatapunten){
            potentiaalData.push_back(z1.potentiaal());
            aantal = 0;
        }
    }
    grafiek.voegDataToe(potentiaalData);
	
	cout << "Done" << endl << "\tPotentiaal van random, voor splayen... ";
    Puntgenerator puntgenerator;
    Splayboomb<double, unsigned int> z2;
    dieptedata.clear();
    potentiaalData.clear();
    aantal=0;
    for (int i=0; i < aantalDatapunten; i++ ){
        z2.voegtoe(puntgenerator.geefpunt(), i);
        aantal++;
        if (aantal * aantalMeetpunten >= aantalDatapunten){
            potentiaalData.push_back(z2.potentiaal());
            aantal = 0;
        }
    }
    grafiek.voegDataToe(potentiaalData);
	
	cout << "Done" << endl << "\tZoekdiepte per 50 zoekoperaties van in order sleutels... ";
    dieptedata.clear();
    potentiaalData.clear();
    aantal = 0;
	int tDepth = 0;
    for (int i=aantalDatapunten; i > 0; i-=10){
        z1.zoek(i, depth);
        tDepth += depth;
        aantal+=10;
        if (aantal * aantalMeetpunten >= aantalDatapunten){
            dieptedata.push_back(tDepth);
            potentiaalData.push_back(z1.potentiaal());
            aantal = 0;
		    tDepth = 0;
        }
    }
    
    grafiek.voegDataToe(dieptedata);
    grafiek.voegDataToe(potentiaalData);
    
    cout << "Done" << endl << "\tZoekdiepte per 50 zoekoperaties van random sleutels... ";
    dieptedata.clear();
    potentiaalData.clear();
    aantal = 0;
	tDepth = 0;
    for (int i=aantalDatapunten; i > 0; i-=10){
        z2.zoek(puntgenerator.geefpunt(), depth);
        tDepth += depth;
        aantal+=10;
        if (aantal * aantalMeetpunten >= aantalDatapunten){
            dieptedata.push_back(tDepth);
            potentiaalData.push_back(z2.potentiaal());
            aantal = 0;
		    tDepth = 0;
        }
    }
    
    grafiek.voegDataToe(dieptedata);
    grafiek.voegDataToe(potentiaalData);
    
    cout << "Done" << endl;
}

void kleinetest(){
    Splayboomb<int, string> boom;

    boom.voegtoe(3,"jelle");
    boom.voegtoe(1,"tomas");
    boom.voegtoe(4,"klaas");
    boom.voegtoe(54,"jan");
    boom.voegtoe(8,"korneel");
    boom.voegtoe(6,"alice");
    boom.voegtoe(4,"bob");
    boom.voegtoe(3,"mark");

    cout<<"----------------VOOR-------------------"<<endl;
    cout<<boom;
    cout<<"----------------Zoek-------------------"<<endl;
    int diepte;
    cout<<"Data van 6: "<<boom.zoek(6, diepte)<<endl;
    cout<<boom;
}

void zoekboomdiepte(){
    int aantalDatapunten = 1000000;
    
    CsvData grafiek("dieptedata",',');
    Puntgenerator dePuntgenerator;
    Zoekboom<double,unsigned int> deZoekboom;
    vector<double> dieptedata;
    int aantal=0;
    for (int i=0; i<aantalDatapunten; i++ ){
        double nupunt=dePuntgenerator.geefpunt();
//        deZoekboom.voegtoe(dePuntgenerator.geefpunt(),i);
        deZoekboom.voegtoe(nupunt,i);
        aantal++;
        if (aantal*50 >= aantalDatapunten){
            dieptedata.push_back(deZoekboom.getDiepte());
            aantal=0;
        }
    }
    grafiek.voegDataToe(dieptedata);
}

int main(void) {
    kleinetest();
    splaytest();
    zoekboomdiepte();
}
