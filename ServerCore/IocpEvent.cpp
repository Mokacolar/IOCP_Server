#include "pch.h"
#include "IocpEvent.h"

// IocpEvent�� �����Լ��� ������ �ʵ��� �����Ѵ�. 
// �ڷᱸ���� 0�� �ʵ忡 Overlapped 0�� �ʵ尡 �ƴ�,
// �����Լ��� ���� ���� ���� �����̴�.
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
