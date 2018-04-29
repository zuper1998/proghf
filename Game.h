/*
 * Game.h
 *
 *  Created on: 17 Apr 2018
 *      Author: Narcano
 */

#ifndef GAME_H_
#define GAME_H_
#include "Character.h"
















class MAP{
	static size_t defsize;
	static size_t resolution;
	char** gui;
	int** ui;
	size_t sizex;
	size_t sizey;
public:
MAP();
MAP(size_t x,size_t y);
~MAP();
int get_res(){return resolution;};
int get_x(){return sizex;};
int get_y(){return sizey;};
int** get_ui(){return ui;};
char** get_gui(){return gui;};

};





class Game{
private:
	MAP map;
	int turns_taken=0;

public:
	Game();
	Game(int x,int y,const char* load);
	char* info();
	char* draw();
	void play();
	void play(const char*);
	char* menu(char**);







};







#endif /* GAME_H_ */
