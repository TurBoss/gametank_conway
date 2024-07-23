// Conway's Game of Life ported to GameTank by TurBoss 2024
// https://rosettacode.org/wiki/Conway%27s_Game_of_Life#C

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "gametank.h"
#include "drawing_funcs.h"
#include "input.h"
#include "persist.h"
#include "banking.h"


#define U_WIDTH 48
#define U_HEIGHT 48
#define CELL_SIZE 4

void show(void *u);
void evolve(void *u);
void game();



int main () {

    init_graphics();

    flip_pages();
    clear_border(0);
    await_draw_queue();
    flip_pages();
    await_draw_queue();
    clear_border(0);


    game();

    return (0);                                     //  We should never get here!

}


void show(void *u)
{
	bool (*univ)[U_WIDTH] = u;

	int x;
	int y;

	for (x = 0; x < U_WIDTH; x++) {
		for (y = 0; y < U_HEIGHT; y++){
			if (univ[y][x]){
		        draw_box(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE, 92);
			}
			else {
				draw_box(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE, 0);
			}
		}
	}

}


void evolve(void *u)
{
	bool (*univ)[U_WIDTH] = u;
	bool new[U_HEIGHT][U_WIDTH];

	int x;
	int y;
	int n;
	int x1;
	int y1;

	for (x = 0; x < U_WIDTH; x++) {
		for (y = 0; y < U_HEIGHT; y++){
			n = 0;
			for (y1 = y - 1  ; y1 <= y + 1; y1++) {
			    for (x1 = x - 1; x1 <= x + 1; x1++) {
					if (univ[(y1 + U_HEIGHT) % U_HEIGHT][(x1 + U_WIDTH) % U_WIDTH]){
						n++;
					}
		    	}
		    }
			if (univ[y][x]) {
				n--;
			}
			new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
		}
	}

	for (x = 0; x < U_WIDTH; x++) {
		for (y = 0; y < U_HEIGHT; y++) {
			univ[y][x] = new[y][x];
		}
	}
}


void game()
{

	bool univ[U_HEIGHT][U_WIDTH];

	int x;
	int y;

	for (x = 0; x < U_WIDTH; x++) {
		for (y = 0; y < U_HEIGHT; y++){
			univ[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
		}
	}

	while (true) {
	    clear_screen(3);
		show(univ);
		evolve(univ);
	    // await_draw_queue();
	    flip_pages();

	}
}
