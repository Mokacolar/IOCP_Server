#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "Memory.h"
#include "DeadLockProfiler.h"
#include "SocketUtils.h"
#include "SendBuffer.h"

Memory*				GMemory				= nullptr;
GlobalQueue*		GGlobalQueue		= nullptr;
ThreadManager*		GThreadManager		= nullptr;
DeadLockProfiler*	GDeadLockProfiler	= nullptr;
SendBufferManager*	GSendBufferManager	= nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GThreadManager				= new ThreadManager();
		GMemory						= new Memory();
		GSendBufferManager			= new SendBufferManager();
		GDeadLockProfiler			= new DeadLockProfiler();
		GGlobalQueue				= new GlobalQueue();
		SocketUtils::Init();
	}

	~CoreGlobal()
	{
		delete GThreadManager;
		delete GMemory;
		delete GSendBufferManager;
		delete GDeadLockProfiler;
		delete GGlobalQueue;
		SocketUtils::Clear();
	}
} GCoreGlobal;