/* 
 * File:   splayboomb.h
 * Author: Jelle De Bock
 *
 * Created on October 6, 2016, 4:15 PM
 */

#ifndef SPLAYBOOMB_H
#define SPLAYBOOMB_H

#include "../zoekbomen/src/zoekboom11.h"
#include <iostream>
#include <stack>
using namespace std;

enum Direction{
    links=false,rechts=true
};

template<class Sleutel, class Data>
class Splayboomb : public Zoekboom<Sleutel,Data>{
    public:
        //belangrijke opmerkingen bij het splayen:
        //  1) Je moet op de 1 of andere wijze te weten komen, of je moet zig-ziggen of zig-zaggen
        //      bijvoorbeeld:
        //              ouder is linker kind van grootouder
        //              node is rechter kind van ouder
        //              => voer zig-zag uit op node
        void splay(stack<Zoekboom<Sleutel,Data>*>& ouders, stack<Direction>& richtingen){
            if(ouders.size()>=2){ //zig zig of zig zag
                Zoekboom<Sleutel, Data>* ouder = ouders.top(); ouders.pop();
                Zoekboom<Sleutel, Data>* grootouder = ouders.top(); ouders.pop();
                bool naar_links_ouder = richtingen.top() ; richtingen.pop();
                bool naar_links_grootouder = richtingen.top() ; richtingen.pop();
                
                if(naar_links_grootouder==naar_links_ouder){//zig zig
                    grootouder->roteer(naar_links_grootouder);
                    grootouder->roteer(naar_links_ouder);
                }
                else{//zigzag
                    ouder->roteer(naar_links_ouder);
                    grootouder->roteer(naar_links_grootouder);
                }              
            }
            else if(ouders.size()==1){ //zig
                //node is rechter kind -> roteer naar links 
                //node is linker kind -> roteer naar rechts
                Zoekboom<Sleutel, Data>* node = ouders.top();
                ouders.pop();
                
                bool naar_links = richtingen.top(); richtingen.pop();
                
                node->roteer(naar_links);
            }

        };
        Data* zoek(const Sleutel& sleutel, int& diepte){
            diepte=0;
            Zoekboom<Sleutel, Data>* node = this;
            stack<Direction> richtingen;
            stack<Zoekboom<Sleutel, Data>*> ouders;
            
            while((*node) && (*node)->getSleutel() != sleutel){
                diepte++;
                ouders.push(node);
                if(sleutel<(*node)->getSleutel()){
                    richtingen.push(Direction::links);
                    node = node->get()->Links();
                }
                else if(sleutel > (*node)->getSleutel()) {
                    richtingen.push(Direction::rechts);
                    node = node->get()->Rechts();
                }
            }
            
            while(!ouders.empty()){
                splay(ouders,richtingen);
            }
            
            if(this->get()){
                return this->get()->getData();
            }
            else{
                return nullptr;
            }
        };
};

#endif /* SPLAYBOOMB_H */

