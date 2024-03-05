#pragma once
#include "Block.h"
#include <random>

COLORREF get_color(unsigned long HEX_code);

class Game_field {
	size_t Lines, Columns, colors_quantity = start_colors_quan, block_size = window_start_width / (start_columns + 1),
		x_0 = (window_start_width - block_size * start_columns) / 3, y_0 = (window_start_height - block_size * start_lines) / 3;
	std::vector<std::vector<Block*>> blocks;
	void move_blocks(std::vector<Block*>& deleting_blocks);
public:
	Game_field(int lines, int columns);
	std::vector<std::vector<Block*>>& get_massive_blocks() { return blocks; }
	size_t lines() { return Lines; }
	size_t columns() { return Columns; }
	int x0() { return x_0; }
	int y0() { return y_0; }
	int get_block_size() { return block_size; }
	void reboot(int lines, int columns);
	bool change_by_click(int x, int y);
};