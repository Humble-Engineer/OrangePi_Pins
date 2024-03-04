/* 举例了一个简单的指针函数
 * 该函数的返回值类型为指针 */

#include <iostream>

using namespace std;


int sum;

// 返回值为int*(整形指针)的函数
// 这里的“*”表示返回值类型是指针
int* add(int a,int b)
{
    sum = a+b;

    // 返回sum所在的地址
    return &sum;
}


int main()
{
    cout << "变量sum的存放地址：" << &sum << endl;

    cout << "函数add的返回值为：" << add(1,2) << endl;

    // 这里的“*”表示取出返回值（地址）中的数据（解引用）
    cout << "函数返回值解引用：" << *add(1,2) << endl;

    return 0;
}
