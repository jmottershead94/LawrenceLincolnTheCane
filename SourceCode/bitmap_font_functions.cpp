// Examples of how to use the bitmap font data in font.cpp to draw text on the bitmap screen.

#include <stdio.h>
#include "font.h"

// Draw ASCII character c at position (x, y) in colour colour.
void DrawChar8(int x, int y, int colour, char c) {
	for (int yo = 0; yo < 8; yo++) {
		for (int xo = 0; xo < 8; xo++) {
			if (font_bold[int(c)][(yo * 8) + xo]) {
				PlotPixel8(x + xo, y + yo, colour);
			}
		}
	}
}

// Draw \0-terminated string s at position (x, y) in colour colour.
void DrawString8(int x, int y, int colour, const char *s) {
	while (*s != '\0') {
		DrawChar8(x, y, colour, *s);
		x += 8;
		s++;
	}
}

// Then you can use it something like this...
void SomeOtherFunction() {
	int score = 42;

	DrawString8(10, 10, 1, "Hello world!");
	
	// To print variables, use snprintf to produce a string, then print the string.
	// (Look at the manual for "printf" to see how the % directives work.)
	char buf[40];
	snprintf(buf, sizeof buf, "Score is %03d", score);
	DrawString8(10, 30, 1, buf);
}