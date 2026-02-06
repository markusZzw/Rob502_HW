#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std::chrono_literals;

// a global variable
std::vector<double> myVector(32, 0);
// a global instance of std::mutex to protect global variable
std::mutex myMutex;

void increment()
{
    myMutex.lock();  // 手动加锁
    for (auto &vec_i : myVector)
    {
        std::this_thread::sleep_for(3ms);
        vec_i += 1;
    }
    myMutex.unlock();  // 手动解锁
}

void printVector()
{
    myMutex.lock();  // 手动加锁
    for (auto const &i : myVector)
    {
        std::this_thread::sleep_for(7ms);
        std::cout << i << ",";
    }
    std::cout << std::endl;
    myMutex.unlock();  // 手动解锁
}

int main()
{
    for (auto i{0}; i < 10; ++i)
    {
        std::thread t1(increment);
        std::thread t2(increment);
        
        // 等待两个增加线程完成
        t1.join();
        t2.join();
        
        // 然后再打印结果
        std::thread print_thread(printVector);
        print_thread.join();
        
        std::cout << "--- Iteration " << i + 1 << " completed ---" << std::endl;
    }
    
    std::cout << "Final result:" << std::endl;
    printVector();
    
    return 0;
}