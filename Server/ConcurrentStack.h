#pragma once
#include <mutex>

template<typename T>
class LockStack
{
public:
	LockStack() {};
	LockStack(const LockStack&) = delete;
	LockStack& operator = (const LockStack&) = delete;

	void Push(T value) {
		lock_guard<mutex> lock(_mutex);
		_stack.push(std::move(value));
		_condVar.notify_one();
	}

	bool TryPop(T& value) { 
		// exception을 사용하지말고 그냥 프로그램이 뻗게 놔둬라.
		// 다른곳에서도 사용할 때 문제가 생길 수 있으므로
		lock_guard<mutex> lock(_mutex);
		if (_stack.empty())
			return false;

		value = std::move(_stack.top());
		_stack.pop();
		return true;
	}
	
	void WaitPop(T& value) {
		unique_lock<mutex> lock(_mutex);
		_condVar.wait(lock, [this] {return _stack.empty() == false; });
		value = std::move(_stack.top());
		_stack.pop();
	}


	bool Empty() {
		lock_guard<mutex> lock(_mutex);
		return _stack.empty();
	}

private:
	stack<T> _stack;
	mutex _mutex;
	condition_variable _condVar;
};


