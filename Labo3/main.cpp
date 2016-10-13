/* 
 * File:   main.cpp
 * Author: Jelle De Bock
 *
 * Created on October 13, 2016, 6:31 PM
 */

#include <cstdlib>

#include "bridges.h"

using namespace std;

int main(int argc, char** argv) {
    BruggenManager manager("versnick.dat");
    cout<<manager;
    return 0;
}

