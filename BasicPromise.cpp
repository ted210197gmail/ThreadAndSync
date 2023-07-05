//
// Created by Ted Wu on 2023/7/5.
//

#include "BasicPromise.h"

#include<iostream>
#include<thread>
#include<future>

using namespace std;

void ThreadFunction(int a, std::promise<int>& p)
{
    std::cout<<"Inside ThreadFunction:"<<a<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)*a);
    //store the value in promise object
    p.set_value(a*2);
    std::cout<<"I have filled the promise but this thread still can continue"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"Puspose of promise is to returned the value BUT want thread to continue"<<std::endl;
    std::cout<<"This statement should be executed at the end"<<std::endl;
    return ;
}


BasicPromise::BasicPromise() {
    std::cout<<"Thread with promise and future"<<std::endl;

    //Create Promise object that will be used to store value in thread
    std::promise<int> p;

    //Thread 1  and its detachable, main thread will NOT wait for it.
    std::thread t1(ThreadFunction, 5, std::ref(p));
    //t1.detach();

    //Create Future Object that will be used to retrieve value
    //same value has been stored using promise object so we need
    //to pass promise object as argument to future object
    std::future<int> f (p.get_future());

    //get the value using get(), This is BLOCKING Call
    int result = f.get();
    std::cout<<"Result:"<<result<<std::endl;

    t1.join();
}