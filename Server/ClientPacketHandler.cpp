#include "pch.h"
#include "ClientPacketHandler.h"
#include "GameSession.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// ���� ������ �۾���

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	session
	return true;
}

bool Handle_C_ENTER_GAME(PacketSessionRef& session, Protocol::C_ENTER_GAME& pkt)
{
	return true;
}

bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
{
	return true;
}