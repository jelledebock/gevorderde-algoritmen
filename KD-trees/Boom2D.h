/* 
 * File:   Boom2D.h
 * Author: Jelle De Bock
 *
 * Created on October 26, 2016, 9:04 AM
 */

#ifndef BOOM2D_H
#define BOOM2D_H

#include "punt2.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <stack>

using namespace std;

enum Direction{
    LEFT,RIGHT
};

class Node2D{
    friend class Boom2D;
private:
    Node2D *links,*rechts;
    punt2 *punt;
public:
    Node2D(int x, int y) { punt = new punt2(x,y);};
    Direction getDirection(punt2*,int);
    Node2D* get(int,int,int);
    int distance(int,int);
    friend std::ostream& operator<<(std::ostream& out, const Node2D punt){
        return out<<*(punt.punt);
    };
    std::pair<int, Node2D*> find_closest(int,int,int,int);
};

Node2D* Node2D::get(int x, int y, int depth){
    if(depth%2==0){
        return x < punt->x?links:rechts;
    }
    else{
        return y < punt->y?links:rechts;
    }
}

Direction Node2D::getDirection(punt2* p, int depth){
    if(depth%2==0){
        return p->x < punt->x?Direction::LEFT:Direction::RIGHT;
    }
    else{
        return p->y < punt->y?Direction::LEFT:Direction::RIGHT;
    }
}

int Node2D::distance(int x, int y){
    return (x-punt->x)*(x-punt->x)+(y-punt->y)*(y-punt->y);
}

class Boom2D{
public:
    void lees_punten(string file);
    void voeg_punt_toe(int,int);
    bool zoek_punt(int,int);
    std::pair<int,Node2D*> zoek_dichtste(int,int);
    
private:
    Node2D *root=nullptr;
    int aantal_knopen=0;
};

void Boom2D::voeg_punt_toe(int x, int y){
    aantal_knopen++;
    if(!this->root){
        root = new Node2D(x,y);
    }
    else{
        int d=0;    //diepte bijhouden (op even diepte x-waarde, op oneven diepte y-waarde)
        punt2 *point_2_add = new punt2(x,y);
        Node2D *current = this->root;
        Node2D *previous;
        Direction dir;
        while(current){
            previous = current;
            dir = current->getDirection(point_2_add,d);
            if(dir == Direction::LEFT){
                current = current->links;
            }
            else{
                current = current->rechts;
            }
            d++;
        }
        
        //we hebben point_2_add slechts als hulp gebruikt dus mag weg
        delete point_2_add;
        
        //We gaan een opvolger toevoegen
        if(dir == Direction::LEFT){
            previous->links = new Node2D(x,y);
        }
        else{
            previous->rechts = new Node2D(x,y);
        }
    }
}

void Boom2D::lees_punten(string file){
    ifstream input;
    input.open(file);
    
    while(!input.eof()){
        int x,y;
        
        input>>x;
        input>>y;
        
        voeg_punt_toe(x,y);
    }
}

std::pair<int, Node2D*> Node2D::find_closest(int x,int y,int d, int aantal_bezocht){
    //cout<<"\t\t(x="<<x<<"y="<<y<<") : bezoektje aan ("<<this->punt->x<<","<<this->punt->y<<")"<<endl;
    std::pair<int, Node2D*> best = std::make_pair(aantal_bezocht,this);
    Node2D* next_node;
    Direction direction;
    
    if(d%2==0){
        if(x<this->punt->x){
            next_node = this->links;
            direction = Direction::LEFT;
        }
        else{
            next_node = this->rechts;
            direction = Direction::RIGHT;
        }
    }
    else{
        if(y<this->punt->y){
            next_node = this->links;
            direction = Direction::LEFT;
        }
        else{
            next_node = this->rechts;
            direction = Direction::RIGHT;
        }
    }
    
    std::pair<int, Node2D*> possible_best;
    
    if(next_node){
        possible_best = next_node->find_closest(x,y,d+1,aantal_bezocht+1);
        best.first = possible_best.first;
        if(best.second->distance(x,y)>possible_best.second->distance(x,y)){
            best.second = possible_best.second;
        }
    }

    next_node = 0;
    
    //check other side of tree
    if(direction==Direction::LEFT){
        next_node=this->rechts;
    }
    else{
        next_node=this->rechts;
    }
    
    if(next_node){
        if(d%2==0){
            if((this->punt->x-x)*(this->punt->x-x) < best.second->distance(x,y)){
                possible_best = next_node->find_closest(x,y,d+1,best.first+1);
                best.first = possible_best.first;
            }
        }
        else if((this->punt->y-y)*(this->punt->y-y) < best.second->distance(x,y)){
             possible_best = next_node->find_closest(x,y,d+1,best.first+1);
             best.first = possible_best.first;
        }
         
        if((possible_best.second!=nullptr) && (best.second->distance(x,y)>possible_best.second->distance(x,y))){
            best.second = possible_best.second;
        }
    }
   

    return best;
    
}

std::pair<int,Node2D*> Boom2D::zoek_dichtste(int x, int y){
    if(!this->root){
        throw "Could not start searching, empty root!";
    }
    return this->root->find_closest(x,y,0,0);
}

bool Boom2D::zoek_punt(int x, int y){
    Node2D* kandidaat = zoek_dichtste(x,y).second;
    
    if(*(kandidaat->punt)==punt2(x,y)){
        return true;
    }
    else{
        return false;
    }
    
}



#endif /* BOOM2D_H */

