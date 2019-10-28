#include <stdio.h>
#include <stdlib.h>

#include <string>

int main()
{
    std::string content = "abc\nabc\n";

    try{
        FILE *fp = fopen("1.txt", "a+");
        if(fp)
        {
            fwrite(content.c_str(), 1, content.length(), fp);
            fwrite("\n----------------------------\n", 1, 30, fp);
            fclose(fp);
        }
    }
    catch (const std::exception& e)
    {
    }

    return 0;
}
