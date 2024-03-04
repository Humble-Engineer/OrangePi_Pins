/* 本程序用来测试函数指针，
 * 函数指针是一个存储函数名的指针
 * 通过指针指向不同函数名来调用函数*/


#include <iostream>

using namespace std;



int add(int x,int y)
{
    return x+y;
}

int sub(int x,int y)
{
    return x-y;
}

// 设置一个函数指针p,可以存放任意该类型的函数（输入参数2个int,返回值int类型）
// 此处的“*”用于标识p是一个指针
int (*p)(int a,int b);


int main()
{
    // 指针指向add函数（函数名就是所在的地址，类似数组，所以“&”也可以省略）
    p = &add;

    // 这里的“*”表示把p指针里的那个函数拿出来（解索引），然后运行
    cout << "p->add 运行结果:" << (*p)(2,1) << endl;

    p = &sub;

    cout << "p->sub 运行结果:" << (*p)(2,1) << endl;

    return 0;
}
