#include <iostream>
#include <unistd.h>
int main()
{
    std::cout << "hello" << std::endl;
    int size = 1024 * 1024 * 1024; //4G内存
    std::cout << "alloc" << std::endl;
    int* arr = (int*)malloc(size * sizeof(int));
    std::cout << "cal" << std::endl;
    for (int i = 0; i < size; i++)
        arr[i] = 0;
    usleep(100 * 1000 * 1000);
    std::cout << "end" << std::endl;
    return 0;
}
