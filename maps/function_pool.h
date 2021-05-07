//#pragma once
//
//#include <iostream>
//#include <string>
//#include<unordered_map>
//#include<chrono>
//#include "utils.h"
//#include <fstream>
//#include"DictionaryTree.h"
//#include<algorithm>
//#include <queue>
//#include <functional>
//#include <mutex>
//#include <condition_variable>
//#include <atomic>
//#include <cassert>
//#include<thread>
//
//// Import things we need from the standard library
//using std::cout;
//using std::endl;
//using std::string;
//using std::to_string;
//using std::hash;
//using std::cin;
//long long int number = 0;
//long long int numberofPermutation_m = 0;
//long long int numberofPermutation_t = 0;
//using std::chrono::duration_cast;
//using std::chrono::seconds;
//using std::chrono::milliseconds;
//using std::chrono::microseconds;
//using std::vector;
//using std::thread;
//using std::mutex;
//using std::unique_lock;
//using std::queue;
//using std::condition_variable;
//
//class Function_pool
//{
//private:
//	std::queue<std::function<bool(std::string)>> function_queue;
//	std::mutex lock;
//	std::condition_variable data_condition;
//	std::atomic<bool> accept_functions;
//public:
//	Function_pool();
//	~Function_pool();
//	void push(std::function<bool(std::string)> func);
//	void done();
//	void infinite_loop_func();
//};
//Function_pool::Function_pool() : function_queue(), lock(), data_condition(), accept_functions(true)
//{
//}
//
//Function_pool::~Function_pool()
//{
//}
//
//void Function_pool::push(std::function<bool(std::string)> func)
//{
//	std::unique_lock<std::mutex> lock(lock);
//	function_queue.push(func);
//	// when we send the notification immediately, the consumer will try to get the lock , so unlock asap
//	lock.unlock();
//	data_condition.notify_one();
//}
//
//void Function_pool::done()
//{
//	std::unique_lock<std::mutex> lock(lock);
//	accept_functions = false;
//	lock.unlock();
//	// when we send the notification immediately, the consumer will try to get the lock , so unlock asap
//	data_condition.notify_all();
//	//notify all waiting threads.
//}
//
//void Function_pool::infinite_loop_func()
//{
//	std::function<void()> func;
//	while (true)
//	{
//		{
//			std::unique_lock<std::mutex> lock(lock);
//			data_condition.wait(lock, [this]() {return !function_queue.empty() || !accept_functions; });
//			if (!accept_functions && function_queue.empty())
//			{
//				//lock will be release automatically.
//				//finish the thread loop and let it join in the main thread.
//				return;
//			}
//			func = function_queue.front();
//			function_queue.pop();
//			//release the lock
//		}
//		func();
//	}
//}
//
