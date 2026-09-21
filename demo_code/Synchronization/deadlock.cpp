#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx1;
mutex mtx2;
void thread_A()
{
    lock_guard<mutex> lock1(mtx1);
    cout << "Thread A: locked mutex 1\n";
    this_thread::sleep_for(
        chrono::milliseconds(100)
    );
    cout << "Thread A: waiting for mutex 2...\n";
    lock_guard<mutex> lock2(mtx2);
    cout << "Thread A finished\n";
}
void thread_B()
{
    lock_guard<mutex> lock2(mtx2);
    cout << "Thread B: locked mutex 2\n";
    this_thread::sleep_for(
        chrono::milliseconds(100)
    );
    cout << "Thread B: waiting for mutex 1...\n";
    lock_guard<mutex> lock1(mtx1);
    cout << "Thread B finished\n";
}
int main()
{
    thread t1(thread_A);
    thread t2(thread_B);
    t1.join();
    t2.join();
    return 0;
}
