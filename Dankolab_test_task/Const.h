#pragma once

const int window_start_x = 0, window_start_y = 0, window_start_width = 640, window_start_height = 512;
const int BG_color = 0x666666, button_start_color = 0xAAAAAA, button_start_text_color = 0x222222;

const size_t start_columns = 16, start_lines = 10, start_colors_quan = 3;

const int button_start_x0 = window_start_width / 2 - window_start_width / (start_columns + 1) * 3 / 2,
	button_start_y0 = (window_start_height - window_start_width / (start_columns + 1) * start_lines) / 3 / 4,
	button_start_x1 = window_start_width / 2 + window_start_width / (start_columns + 1),
	button_start_y1 = (window_start_height - window_start_width / (start_columns + 1) * start_lines) / 3 * 3 / 4;

const int colors_list[] = { 0xFF0000, 0x00FF00, 0x0000FF };
