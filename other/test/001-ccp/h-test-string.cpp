
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
    string s = "";
    string d = " edf";
    string e = " kfd";

    s += "abc";
    s += " ";
    s += "bcd";

    s += d + e;
    printf("%s\n", s.c_str());

    return 0;
}
