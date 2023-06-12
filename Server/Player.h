#pragma once
class Player
{
public:
	uint64 playerId = 0;
	string name;
	Protocol::PlayerType type = Protocol::PLAYER_TYPE_NONE;
	GameSessionRef ownerSession; //memory leak를 막기위해 cycle을 끊어줘야함.

};

