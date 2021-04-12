#include "function.h"

int main() {
	resizeConsole(1200, 600);
	resetData();
	drawBoard();
	tab();
	header();
	move(3, 3);
	run();
	return 0;
}