#include <string>
#include <iostream>
#include <thread>
#include <vector>  // 需要添加这个头文件

// create a function called "print" which takes in an int and a std::string and prints both arguments
void print(int n, const std::string &str)
{
    std::string msg = std::to_string(n) + " : " + str;
    std::cout << msg << std::endl;
}

int main()
{
    std::vector<std::string> s = {
        "Educative.blog",
        "Educative",
        "courses",
        "are great"};
    std::vector<std::thread> threads;
    
    // Write a for-loop to create "std::thread" objects and add them to the "threads" vector
    for (size_t i = 0; i < s.size(); i++) {
        // 创建线程，传入print函数和参数
        threads.push_back(std::thread(print, i, s[i]));
    }
    
    // Next, iterate over each of the threads in "threads" and call "join()".
    // This will cause the program to wait until the threads have completed.
    for (auto &t : threads) {
        t.join();  // 等待线程执行完毕
    }
    
    return 0;
}