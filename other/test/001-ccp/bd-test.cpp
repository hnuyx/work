
#define MAX_DATA_LENGTH 100

struct DATA
{
    int type;
    char* data;
};

int fill_data(DATA* d, const char* data)
{
    if (data == NULL or d == NULL)
    {
        printf("data or d is NULL\n");
        return 1;
    }

    if (d->data == NULL)
        d->data = (char *) malloc(MAX_DATA_LENGTH);

    snprintf(d->data, MAX_DATA_LENGTH, "This is to fill the data: %s.", data);

    return 0;
}

