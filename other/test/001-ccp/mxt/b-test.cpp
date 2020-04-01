
#include <stdio.h>
#include <stdint.h>

#include <string>
#include <map>

typedef std::map<std::string, uint32_t> IntMap;
typedef IntMap::iterator IntMapIter;

#define FILENAME_MAX_SIZE  256
#define STRATEGY_MAX_SIZE  64
#define WORD_MAX_SIZE      64
#define KEY_MAX_SIZE       128

void to_lowers(char *w)
{
    while(*w != '\0')
    {
        *w = tolower(*w);
        ++ w;
    }
}

int main()
{
    IntMap strategyMap;
    IntMap fileMap;
    IntMap wordMap;
    char strategy[STRATEGY_MAX_SIZE];
    char filename[FILENAME_MAX_SIZE];
    char fullname[FILENAME_MAX_SIZE];
    char word[WORD_MAX_SIZE];
    char key[KEY_MAX_SIZE];

    //const char *strategys[] = {"business", "entertainment", "politics", "sport", "tech"};
    const char *strategys[] = {"tmp", "tmp1"};
    int size = sizeof(strategys) / sizeof(char *);
    int twordcnt = 0;
    for(int i = 0; i < size; ++i)
    {
        int swordcnt = 0;
        for(int j = 0; j < 600; ++j)
        {
            snprintf(fullname, FILENAME_MAX_SIZE, "bbc/%s/%03d.txt", strategys[i], j+1);
            FILE *fp = fopen(fullname, "r");
            if(!fp)
                break;

            int wordcnt = 0;
            while(EOF != fscanf(fp, "%s", word))
            {
                to_lowers(word);
                snprintf(key, KEY_MAX_SIZE, "%s%s", fullname, word);
                IntMapIter iter = wordMap.find(key);
                if(iter == wordMap.end())
                    wordMap[word] = 1;
                else
                    wordMap[word] += 1;
                
                ++ wordcnt;
            }
            fileMap[fullname] = wordcnt;
            swordcnt += wordcnt;

            fclose(fp);
        }
        strategyMap[strategys[i]] = swordcnt;
        twordcnt += swordcnt;
    }

    while(true)
    {
        printf("please input: strategy filename word\n");
        scanf("%s %s %s", strategy, filename, word);
        snprintf(fullname, FILENAME_MAX_SIZE, "bbc/%s/%03d.txt", strategy, filename);
        snprintf(key, KEY_MAX_SIZE, "%s%s", fullname, word);
        IntMapIter iter = strategyMap.find(strategy);
        if(iter == strategyMap.end())
        {
            printf("wrong strategy\n");
            continue;
        }

        iter = fileMap.find(fullname);
        if(iter == fileMap.end())
        {
            printf("wrong filename\n");
            continue;
        }

        iter = word.find(key);
        if(iter == wordMap.end())
        {
            printf("wrong word\n");
            continue;
        }

        double tf =  

    }

    return 0;
}

