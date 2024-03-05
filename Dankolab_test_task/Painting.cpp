#include "Painting.h"

void Painter::paint(Game_field& field) {
	if (its_first_painting) {
		RECT global_rect = { 0, 0, window_start_width, window_start_height };
		FillRect(hdc, &global_rect, CreateSolidBrush(BG_color));
		RECT button_start_rect = { button_start_x0, button_start_y0, button_start_x1, button_start_y1 };
		FillRect(hdc, &button_start_rect, CreateSolidBrush(button_start_color));
		RECT test_start_rect = { button_start_x0 + (button_start_x1 - button_start_x0) / 6, button_start_y0, 
			button_start_x1, button_start_y1};
		HFONT my_font = CreateFontA(button_start_y1 - button_start_y0, (button_start_y1 - button_start_y0) / 2, 
			0, 0, 551, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, FF_DONTCARE, "MyFont");
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, get_color(button_start_text_color));
		SelectObject(hdc, my_font);
		DrawTextW(hdc, L"start", -1, &test_start_rect, 0);

	}
	std::vector<std::vector<Block*>>& blocks = field.get_massive_blocks();
	size_t rows = field.lines(), cols = field.columns(), x0 = field.x0(), y0 = field.y0(), 
		block_size = field.get_block_size(), indent = block_size / 10 + 1;
	RECT field_rect = { x0, y0, x0 + cols * block_size, y0 + rows * block_size };
	FillRect(hdc, &field_rect, CreateSolidBrush(BG_color));
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			if (blocks[i][j]) {
				RECT rect = { x0 + block_size * j + indent, y0 + block_size * i + indent,
					x0 + block_size * (j + 1) - indent, y0 + block_size * (i + 1) - indent };
				FillRect(hdc, &rect, CreateSolidBrush(blocks[i][j]->color()));
			}
		}
	}
	its_first_painting = false;
}