
#include <stdio.h>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, int> tmap;
    map<string, int> *pmap = &tmap;
    tmap["123"] = 1;
    printf("%d\n", (*pmap)["123"]);

}
