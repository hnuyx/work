
class Base
{
protect:
    int _ref_cnt;
    char *_data;

public:
    Base() : _ref_cnt(0)
    {
        ++ _ref_cnt;
    }

    ~Base()
    {
        -- _ref_cnt;
        if(0 == _ref_cnt)
            free(_data);
    }

};

clase A : Base
{
private:

public:
    A()
    {
        _data = (char *)malloc(10);
    }

    void func(int a, int b);
    func_int_int;
    func


    A (const A& _a)
    {
        _data = _a._data;
    }

    ~A(){}
};

int main()
{
    A a;
    A b(a);

    return 0;
}
