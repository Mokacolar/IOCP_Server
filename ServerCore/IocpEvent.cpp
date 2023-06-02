#include "pch.h"
#include "IocpEvent.h"

// IocpEvent에 가상함수를 만들지 않도록 유의한다. 
// 자료구조의 0번 필드에 Overlapped 0번 필드가 아닌,
// 가상함수가 들어가는 것을 막기 위함이다.
/*--------------
	IocpEvent
---------------*/

IocpEvent::IocpEvent(EventType type) : eventType(type)
{
	Init();
}

void IocpEvent::Init()
{
	OVERLAPPED::hEvent = 0;
	OVERLAPPED::Internal = 0;
	OVERLAPPED::InternalHigh = 0;
	OVERLAPPED::Offset = 0;
	OVERLAPPED::OffsetHigh = 0;
}
