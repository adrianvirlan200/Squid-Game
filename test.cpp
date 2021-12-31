#include <iostream>
using namespace std;

class asds
{
    public:
    int a = 666666;
    asds(int x)
    {
        cout<<a;
    }
};


class test:public asds
{
public:
    int index;
    static int static_index_nr_elem;
    test():asds{1}
    {
        static_index_nr_elem++;
        index = static_index_nr_elem;
    }
    void print()
    {
        cout<<this->index<<endl;
    }
};

int test::static_index_nr_elem = 0;

int main()
{

    test *t[3];
    int i=0;

    t[i++] = new test();
    t[i++] = new test();
    t[i++] = new test();

    t[0]->print();
    t[1]->print();
    t[2]->print();

    delete t;
    return 1;
}