#pragma once
#include "Job.h"
#include "LockQueue.h"

/*---------------
	JobQueue
----------------*/

class JobQueue : public enable_shared_from_this<JobQueue>
{
public:
	// 비동기적으로 실행
	void DoAsync(CallbackType&& callback)
	{
		Push(ObjectPool<Job>::MakeShared(std::move(callback)));
	}

	template<typename T, typename Ret, typename... Args>
	void DoAsync(Ret(T::* memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		Push(ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Args>(args)...));
	}

	void				ClearJobs() { _jobs.Clear(); }

public:
	void				Push(JobRef job, bool pushOnly = false);
	void				Execute();

protected:
	LockQueue<JobRef>	_jobs;
	Atomic<int32>		_jobCount = 0;
};

