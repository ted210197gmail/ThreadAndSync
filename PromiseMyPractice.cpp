//
// Created by Ted Wu on 2023/7/5.
//

#include "PromiseMyPractice.h"

#include <iostream>
#include <thread>
#include <future>
#include <vector>

using namespace std;

void threadFunction(int a, promise<int>& p) {
    p.set_value(a*2);
}

void PromiseMyPractice::basic() {
    promise<int> p;
    thread t1(threadFunction, 5, std::ref(p));
    future<int> f = p.get_future();
    cout<<f.get()<<endl;
    t1.join();
}

void PromiseMyPractice::sharedFuture() {
    promise<int> p;
    future<int> f = p.get_future();
    shared_future<int> sf = f.share();

    thread t1(
            [sf]() {
                cout << "t1's value is "<<sf.get()<<endl;
            }
            );
    thread t2(
            [sf]() {
                cout<<"t2's value is "<<sf.get()<<endl;
            }
            );

    p.set_value(50);
    t1.join();
    t2.join();

}

void PromiseMyPractice::packageTask() {
    // https://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async
    // https://www.geeksforgeeks.org/packaged-task-advanced-c-multithreading-multiprocessing/
    packaged_task<int(int, int)> task(
            [](int a, int b) {
                //cout<<a<<" "<<b<<endl;
                int val = 0;
                for(int i=0;i<1000;++i) {
                    val += a+b;
                }
                return val;
            });
    future<int> f = task.get_future();
    // We can move this task into another thread, or let it run in main thread like below
    thread t(move(task), 2, 3);
    // 1. packaged_task needs to init. f.get() is not enough
    // 2. The task will be run while the parameters are given
    //task(2, 3);
    cout<<"packaged_task: "<<f.get()<<endl;

    f = async(launch::async,
              [](int a, int b){return a+b;}
              ,2, 3);
    // Note: we dont need to call t.join() because f.get() will wait until the result is completed
    cout<<"async: "<<f.get()<<endl;
}

PromiseMyPractice::PromiseMyPractice() {

}
