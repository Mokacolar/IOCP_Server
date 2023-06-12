#pragma once
class Room
{
public:
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);

private:
	USE_LOCK;
	map<uint64, PlayerRef> _players;
};
extern Room GRoom;
//미래에는 여러 room을 이용할 수 있는 roommanager같은게 필요