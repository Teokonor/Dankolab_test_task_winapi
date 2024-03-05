#pragma once
#include "Const.h"
#include <Windows.h>
#include <vector>

class Block {
	COLORREF Color;
	Block* Up_neighbor = NULL, * Right_neighbor = NULL, * Down_neighbor = NULL, * Left_neighbor = NULL;
	int X, Y;
	bool Checked = false;
public:
	Block(COLORREF color, int x, int y) : Color(color), X(x), Y(y) {}
	~Block();
	void init_neighbors(Block* up_neighbor, Block* right_neighbor, Block* down_neighbor, Block* left_neighbor);
	bool not_checked_and_color_is(COLORREF color);
	COLORREF color() { return Color; }
	Block* up_neighbor() { return Up_neighbor; }
	Block* right_neighbor() { return Right_neighbor; }
	Block* down_neighbor() { return Down_neighbor; }
	Block* left_neighbor() { return Left_neighbor; }
	int x() { return X; }
	int y() { return Y; }
	void uncheck() { Checked = false; }
	void move(int new_x, int new_y, Block* up_neighbor, Block* right_neighbor, Block* down_neighbor, Block* left_neighbor);
	void set_connections(Block* this_object);
};