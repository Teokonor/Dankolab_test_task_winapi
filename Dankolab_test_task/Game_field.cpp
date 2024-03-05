#include "Game_field.h"

COLORREF get_color(unsigned long HEX_code) {
	unsigned int R = HEX_code / 0x10000, G = HEX_code % 0x10000 / 0x100, B = HEX_code % 0x100;
	return RGB(R, G, B);
}

Game_field::Game_field(int lines, int columns) : Lines(lines), Columns(columns) {
	reboot(lines, columns);
}

void Game_field::reboot(int lines, int columns) {
	for (size_t i = 0; i < blocks.size(); i++) {
		for (size_t j = 0; j < blocks[i].size(); j++) {
			if (blocks[i][j]) {
				delete(blocks[i][j]);
			}
		}
	}
	blocks.resize(0);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, colors_quantity - 1);
	blocks.reserve(Lines * sizeof(std::vector<Block*>));
	for (size_t i = 0; i < Lines; i++) {
		std::vector<Block*> blocks_line(Columns);
		for (size_t j = 0; j < Columns; j++) {
			Block* block = new Block(get_color(colors_list[dist(gen)]), j, i);
			blocks_line[j] = block;
		}
		blocks.push_back(blocks_line);
	}
	for (size_t i = 0; i < Lines; i++) {
		for (size_t j = 0; j < Columns; j++) {
			blocks[i][j]->init_neighbors(i > 0 ? blocks[i - 1][j] : NULL, j < Columns - 1 ? blocks[i][j + 1] : NULL,
				i < Lines - 1 ? blocks[i + 1][j] : NULL, j > 0 ? blocks[i][j - 1] : NULL);
		}
	}
}

void Game_field::move_blocks(std::vector<Block*>& deleting_blocks) {
	std::vector<bool> column_changed(Columns, false);
	std::vector<size_t> lower_blocks(Columns, 0);
	for (Block* bl : deleting_blocks) {
		column_changed[bl->x()] = true;
		lower_blocks[bl->x()] = bl->y() > lower_blocks[bl->x()] ? bl->y() : lower_blocks[bl->x()];
		blocks[bl->y()][bl->x()] = NULL;
		delete(bl);
	}
	for (size_t col = 0; col < Columns; col++) {
		if (column_changed[col]) {
			size_t vertical_offset = 0;
			for (int row = lower_blocks[col]; row >= 0; row--) {
				Block* bl = blocks[row][col];
				if (bl == NULL) {
					vertical_offset++;
				}
				else {
					size_t row_new = row + vertical_offset;
					bl->move(col, row_new, NULL, col + 1 < Columns ? blocks[row_new][col + 1] : NULL,
						row_new + 1 < Lines ? blocks[row_new + 1][col] : NULL, col > 0 ? blocks[row_new][col - 1] : NULL);
					blocks[row_new][col] = bl;
					blocks[row][col] = NULL;
				}
			}
		}
	}
}

bool Game_field::change_by_click(int x, int y) {
	if (x < x_0 || y < y_0) {
		return false;
	}
	x -= x_0; x /= block_size;
	y -= y_0; y /= block_size;
	if (x >= Columns || y >= Lines || !blocks[y][x]) {
		return false;
	}
	std::vector<Block*> deleting_blocks;
	deleting_blocks.push_back(blocks[y][x]);
	COLORREF target_color = deleting_blocks[0]->color();
	size_t counter_deleting_blocks = 1;
	deleting_blocks[0]->not_checked_and_color_is(target_color);
	for (size_t i = 0; i < counter_deleting_blocks; i++) {
		Block* bl = deleting_blocks[i];
		Block* neighbors[4] = { bl->up_neighbor(), bl->right_neighbor(), bl->down_neighbor(), bl->left_neighbor() };
		for (Block* neighbor : neighbors) {
			if (neighbor && neighbor->not_checked_and_color_is(target_color)) {
				deleting_blocks.push_back(neighbor);
				counter_deleting_blocks++;
			}
		}
	}
	if (counter_deleting_blocks < 3) {
		for (Block* bl : deleting_blocks) {
			bl->uncheck();
		}
		return false;
	}
	move_blocks(deleting_blocks);
	return true;
}