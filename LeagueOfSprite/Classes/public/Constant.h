#pragma once
#ifndef CONSTANT_H
#define CONSTANT_H

class Constant {
public:
	static int getArrowTag();
	static int getMonsterArrowTag();
	static int getPlayer2ArrowTag();
	static int getMonster2ArrowTag();
	static int getMonster3ArrowTag();

	static int getEdgeTag();

	static int getMonsterTag();
	static int getPlayerTag();
	static int getPlayer2Tag();
	static int getMonster2Tag();
	static int getMonster3Tag();

	static int getStormTag();
	static int getStorm2Tag();

	//game mode
	static int getSingleMode();
	static int getSoloMode();

	//game status
	static int getPlayWin();
	static int getPlayLose();
	static int getPlayer2Win();

private:
	static int arrowTag;
	static int monsterArrowTag;
	static int player2ArrowTag;
	static int monster2ArrowTag;
	static int monster3ArrowTag;

	static int edgeTag;

	//character
	static int monsterTag;
	static int monster2Tag;
	static int monster3Tag;
	static int playerTag;
	static int player2Tag;

	//player skill storm
	static int stormTag;
	static int storm2Tag;

	//game mode
	static int singleMode;
	static int soloMode;

	//game status for GameController
	static int playerWin;
	static int playerLose;
	static int player2Win;

};
#endif // !CONSTANT_H