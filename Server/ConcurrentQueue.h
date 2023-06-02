#pragma once
#include <mutex>

template<typename T>
class LockQueue
{
public:
	//��Ƽ������ ȯ�濡�� ���� ������ x
	LockQueue() {};
	LockQueue(const LockQueue&) = delete;
	LockQueue& operator = (const LockQueue&) = delete;

	void Push(T value) {
		lock_guard<mutex> lock(_mutex);
		_q.push(std::move(value));
		_condVar.notify_one();
	}

	bool TryPop(T& value) {
		// exception�� ����������� �׳� ���α׷��� ���� ���ֶ�.
		// �ٸ��������� ����� �� ������ ���� �� �����Ƿ�
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
		value = std::move(_q.top()); // ��쿡 ���� ���� �۾��� ����.
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



