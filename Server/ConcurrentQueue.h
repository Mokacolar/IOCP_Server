#pragma once
#include <mutex>

template<typename T>
class LockQueue
{
public:
	//멀티스레드 환경에서 복사 생성자 x
	LockQueue() {};
	LockQueue(const LockQueue&) = delete;
	LockQueue& operator = (const LockQueue&) = delete;

	void Push(T value) {
		lock_guard<mutex> lock(_mutex);
		_q.push(std::move(value));
		_condVar.notify_one();
	}

	bool TryPop(T& value) {
		// exception을 사용하지말고 그냥 프로그램이 뻗게 놔둬라.
		// 다른곳에서도 사용할 때 문제가 생길 수 있으므로
		lock_guard<mutex> lock(_mutex);
		if (_q.empty())
			return false;

		value = std::move(_q.top());
		_q.pop();
		return true;
	}

	void WaitPop(T& value) {
		unique_lock<mutex> lock(_mutex);
		_condVar.wait(lock, [this] {return _q.empty() == false; });
		value = std::move(_q.top()); // 경우에 따라 복사 작업을 줄임.
		_q.pop();
	}


	bool Empty() {
		lock_guard<mutex> lock(_mutex);
		return _q.empty();
	}

private:
	queue<T> _q;
	mutex _mutex;
	condition_variable _condVar;
};



