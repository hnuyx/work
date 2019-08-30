
#include <stdio.h>
#include <string>
#include <iostream>

int main()
{
    const char *a = "123456";
    const char *b = NULL;

    std::string s1, s2, s3, s4, s5, s6;
    s1.assign(a, 6);
    s2.assign(b, 0);
    s3.assign(b, 0);
    s4.assign(b, 0);
    s5.assign(b, 0);
    s6.assign(b, 0);

    std::cout << s1 << "1" << s2 << "1" << s3 << "1" << s4 << "1" << s5 << "1" << s6 << "1" << std::endl;

    //printf("s1: %s, s2: %s\n", s1.c_str(), s2.c_str());

    return 0;
}
