#pragma once
#ifndef CONSTANT_H
#define CONSTANT_H

class Constant {
public:
	static int getArrowTag();
	static int getMonsterArrowTag();
	static int getPlayer2ArrowTag();

	static int getEdgeTag();

	static int getMonsterTag();
	static int getPlayerTag();
	static int getPlayer2Tag();

	static int getStormTag();

	//game status
	static int getPlayWin();
	static int getPlayLose();

private:
	static int arrowTag;
	static int monsterArrowTag;
	static int player2ArrowTag;

	static int edgeTag;

	static int monsterTag;
	static int playerTag;
	static int player2Tag;

	//player skill storm
	static int stormTag;

	//game status for GameController
	static int playerWin;
	static int playerLose;

};
#endif // !CONSTANT_H