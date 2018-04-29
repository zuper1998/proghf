/*
 * Game.cpp
 *
 *  Created on: 17 Apr 2018
 *      Author: Narcano
 */

#include <iostream>
#include "Game.h"
using namespace std;
size_t MAP::defsize = 500;

size_t MAP::resolution = 10;

void turn(MAP*, Player*p1);


void insert_enem(MAP*, character* ene);





// MAP DEF
MAP::MAP() {
	sizey = defsize;
	sizex = defsize;
	gui = new char*[sizex];
	ui = new int*[sizex / resolution];

	for (size_t x = 0; x < defsize; x++) {
		gui[x] = new char[sizey];
		if (x % resolution == 0) {
			ui[x / resolution] = new int[sizey / resolution];
		}

		for (size_t y = 0; y < sizex; y++) {
			gui[x][y] = '-';
			if ((y % resolution == 0) && (x % resolution == 0))
				ui[x / resolution][y / resolution] = 0;
		}

	}
}

MAP::MAP(size_t x1, size_t y1) {

	sizey = y1;
	sizex = x1;
	gui = new char*[sizex];
	ui = new int*[sizex / resolution];

	for (size_t x3 = 0; x3 < defsize; x3++) {
		sizey = y1;
		sizex = x1;
		int x2 = x3;
		gui[x2] = new char[sizey];
		if (x2 % resolution == 0)
			ui[x2] = new int[(sizey / resolution)+1];
		for (size_t y3 = 0; y3 < sizex; y3++) {
			int y2 = y3;
			gui[x2][y2] = '-';
			if ((y2 % resolution == 0) && (x2 % resolution == 0))
				ui[x2 / resolution][y2 / resolution] = 0;
		}

	}

}

MAP::~MAP() {
	for (size_t x = 0; x < sizex; x++) {
		delete[] gui[x];
		if (x % resolution == 0)
			delete[] ui[x / resolution];

	}
	delete ui;
	delete gui;

}
//Game def

Game::Game() {
	MAP map;
}

Game::Game(int x, int y, const char* load) {
//loading algorithm here
	MAP map(x, y);
}

char* Game::info() {
	int ** ui = map.get_ui();
	int coordy = map.get_y() / map.get_res();
	int coordx = map.get_x() / map.get_res();

	int enemies = 0;

	for (int x = 0; x < coordx; x++) {
		for (int y = 0; y < coordy; y++) {
			if (ui[x][y] > 1) {
				enemies += 1;
			}
		}
	}

	return (char*) "Enemy counter:" + enemies;

}


void Game::play() {
	MAP map;
	Player p1;
	runner nib(2,0);
	p1.nextenemy = &nib;
	p1.insert(&map);
	p1.nextenemy->insert(&map);
	nib.create_enemy(&map, 2);


	for (int x = 0; x < map.get_x() / map.get_res(); x++) {
			for (int y = 0; y < map.get_x() / map.get_res(); y++) {

				std::cout << map.get_ui()[x][y] << " | ";

			}
			std::cout << endl;
		}

	for (int x = 0; p1.get_hp() > 0; x++) {
		turn(&map, &p1);

	}

}




void turn(MAP* map, Player*p1) {
	int input;
	std::cin >> input;
	p1->move(input);
	p1->insert(map);

	for (int x = 0; x < map->get_x() / map->get_res(); x++) {
		for (int y = 0; y < map->get_x() / map->get_res(); y++) {

			std::cout << map->get_ui()[x][y] << " | ";

		}
		std::cout << endl;
	}

}

