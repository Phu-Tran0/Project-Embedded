#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <semaphore>
#include <shared_mutex>
#include <chrono>

using namespace std;

/* 1. Race Condition + Mutex */
int counter = 0;
mutex counter_mutex;
void increment()
{
    for(int i = 0; i < 10000; i++)
    {
        lock_guard<mutex> lock(counter_mutex);
        counter++;
    }
}
void mutex_demo()
{
    vector<thread> threads;
    counter = 0;
    for(int i = 0; i < 10; i++)
        threads.emplace_back(increment);

    for(auto &t : threads)
        t.join();
    cout << "Final counter = "
         << counter << endl;
}
/* 2. Condition Variable */
queue<int> buffer;
mutex buffer_mutex;
condition_variable cv;
bool finished = false;
void producer()
{
    for(int i = 1; i <= 5; i++)
    {
        {
            lock_guard<mutex> lock(buffer_mutex);

            buffer.push(i);

            cout << "Produced: "
                 << i << endl;
        }
        cv.notify_one();

        this_thread::sleep_for(
            chrono::milliseconds(100)
        );
    }
    {
        lock_guard<mutex> lock(buffer_mutex);
        finished = true;
    }
    cv.notify_all();
}
void consumer()
{
    while(true)
    {
        unique_lock<mutex> lock(buffer_mutex);
        cv.wait(lock, []{
            return !buffer.empty() || finished;
        });
        while(!buffer.empty())
        {
            int value = buffer.front();
            buffer.pop();
            cout << "Consumed: "
                 << value << endl;
        }
        if(finished && buffer.empty())
            break;
    }
}
void condition_variable_demo()
{
    thread p(producer);
    thread c(consumer);

    p.join();
    c.join();
}
/* 3. Semaphore */
counting_semaphore<3> sem(3);
void semaphore_worker(int id)
{
    sem.acquire();
    cout << "Thread "
         << id
         << " entered resource\n";

    this_thread::sleep_for(
        chrono::seconds(1)
    );
    cout << "Thread "
         << id
         << " left resource\n";

    sem.release();
}
void semaphore_demo()
{
    vector<thread> threads;
    for(int i = 0; i < 6; i++)
        threads.emplace_back(
            semaphore_worker,
            i
        );
    for(auto &t : threads)
        t.join();
}
/* 4. RW Lock */
shared_mutex rw_mutex;
int shared_data = 0;
void reader(int id)
{
    shared_lock<shared_mutex> lock(rw_mutex);
    cout << "Reader "
         << id
         << " reads "
         << shared_data
         << endl;
}
void writer(int id, int value)
{
    unique_lock<shared_mutex> lock(rw_mutex);
    shared_data = value;
    cout << "Writer "
         << id
         << " writes "
         << value
         << endl;
}
void rwlock_demo()
{
    thread w(writer, 1, 100);
    thread r1(reader, 1);
    thread r2(reader, 2);
    w.join();
    r1.join();
    r2.join();
}
/* MAIN */
int main()
{
    cout << "\n===== Mutex Demo =====\n";
    mutex_demo();
    cout << "\n===== Condition Variable Demo =====\n";
    condition_variable_demo();
    cout << "\n===== Semaphore Demo =====\n";
    semaphore_demo();
    cout << "\n===== RW Lock Demo =====\n";
    rwlock_demo();
    return 0;
}
