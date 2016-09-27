#include <iostream>
#include "zoekboom11.h"

using namespace std;

int main(int argc, char *argv[])
{
    Zoekboom <int, string> boom;

    boom.voegtoe(1,"jelle");
    boom.voegtoe(2,"tomas");

    cout<<boom;

    return 0;
}
