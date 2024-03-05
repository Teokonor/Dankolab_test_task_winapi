#include "Block.h"

Block::~Block() {
	set_connections(NULL);
}

void Block::init_neighbors(Block* up_neighbor, Block* right_neighbor, Block* down_neighbor, Block* left_neighbor) {
	Up_neighbor = up_neighbor;
	Right_neighbor = right_neighbor;
	Down_neighbor = down_neighbor;
	Left_neighbor = left_neighbor;
}

bool Block::not_checked_and_color_is(COLORREF color) {
	if (Checked) {
		return false;
	}
	Checked = (color == Color);
	return Checked;
}

void Block::move(int new_x, int new_y, Block* up_neighbor, Block* right_neighbor, Block* down_neighbor, Block* left_neighbor) {
	set_connections(NULL);
	init_neighbors(up_neighbor, right_neighbor, down_neighbor, left_neighbor);
	X = new_x; Y = new_y;
	set_connections(this);
}

void Block::set_connections(Block* this_object) {
	if (Up_neighbor) {
		Up_neighbor->Down_neighbor = this_object;
	}
	if (Right_neighbor) {
		Right_neighbor->Left_neighbor = this_object;
	}
	if (Down_neighbor) {
		Down_neighbor->Up_neighbor = this_object;
	}
	if (Left_neighbor) {
		Left_neighbor->Right_neighbor = this_object;
	}
}