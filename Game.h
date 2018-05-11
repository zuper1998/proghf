/*
 * Game.h
 *
 *  Created on: 17 Apr 2018
 *      Author: Narcano
 */

#ifndef GAME_H_
#define GAME_H_
#include "Character.h"

class MAP {
	static size_t defsize;
	static size_t resolution;
	char** gui;
	int** ui;
	size_t sizex;
	size_t sizey;
public:
	MAP();
	~MAP();
	int get_res() {
		return resolution;
	}
	;
	int get_x() {
		return sizex;
	}
	;
	int get_y() {
		return sizey;
	}
	;
	int** get_ui() {
		return ui;
	}
	;
	char** get_gui() {
		return gui;
	}
	;
	void print_ui();
	void ins_gui();
	void print_gui();
	void reset();

};

class Game {
private:
	MAP map;
	int turns_taken = 0;

public:
	Game();
	char* draw();
	int play();
	int play(const char*);
	char* menu(char**);
	void turntaken() {
		turns_taken += 1;
	}
	int end();

};

#endif /* GAME_H_ */
