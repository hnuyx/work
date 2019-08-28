
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
    string s = "";

    s += "abc";
    s += " ";
    s += "bcd";
    printf("%s\n", s.c_str());

    return 0;
}
