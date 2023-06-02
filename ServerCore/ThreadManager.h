#pragma once

#include <mutex>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void		Launch(function<void(void)> callback);
	void		Join();

	static void InitTLS();
	static void DestroyTLS();


private:
	Mutex				_lock;
	vector<thread>	_threads;
};


