#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

class Constant {
public:
	static int getArrowTag();
	static int getEdgeTag();

	static int getMonsterTag();
	static int getPlayerTag();
	static int getStormTag();

private:
	static int arrowTag;
	static int edgeTag;
	static int monsterTag;
	static int playerTag;

	//player skill storm
	static int stormTag;
};
#endif // !_CONSTANT_H_