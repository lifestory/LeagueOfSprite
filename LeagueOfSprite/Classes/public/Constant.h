#pragma once
#ifndef CONSTANT_H
#define CONSTANT_H

class Constant {
public:
	static int getArrowTag();
	static int getEdgeTag();

	static int getMonsterTag();
	static int getPlayerTag();
private:
	static int arrowTag;
	static int edgeTag;
	static int monsterTag;
	static int playerTag;
};
#endif // !CONSTANT_H