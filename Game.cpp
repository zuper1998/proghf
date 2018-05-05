/*
 * Game.cpp
 *
 *  Created on: 17 Apr 2018
 *      Author: Narcano
 */

#include <iostream>
#include "Game.h"
using namespace std;
size_t MAP::defsize = 100;

size_t MAP::resolution = 10;

void turn(MAP*, Player*p1);

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

Game::Game(const char* load) {
//loading algorithm here
}

void MAP::reset() {
	for (size_t x = 0; x < defsize; x++) {
		for (size_t y = 0; y < sizex; y++) {
			get_gui()[x][y] = '-';
			if ((y % resolution == 0) && (x % resolution == 0))
				get_ui()[x / resolution][y / resolution] = 0;
		}

	}
}
/*
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

 }*/

int Game::play() {
	MAP map;
	Player p1;
	runner nib(2, 0);
	p1.nextenemy = &nib;
	p1.insert(&map);
	p1.nextenemy->insert(&map);
	nib.create_enemy(&map, 2);

	for (int x = 0; x < map.get_x() / map.get_res(); x++) {
		for (int y = 0; y < map.get_x() / map.get_res(); y++) {

			std::cout << map.get_ui()[y][x] << " | ";

		}
		std::cout << endl;
	}

	for (int x = 0; p1.get_hp() > 0; x++) {
		turn(&map, &p1);
		turntaken();
	}
	return 0;
}

void turn(MAP* map, Player*p1) {
	int input;
	map->reset();
	std::cin >> input;
	while (std::cin.fail()) {
		std::cout << "Hibas bemenet"<<std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> input;
	}

	p1->move(input,*map);
	p1->insert(map);
	p1->nextenemy->insert(map);
	p1->nextenemy->move(p1);

	for (int x = 0; x < map->get_x() / map->get_res(); x++) {
		for (int y = 0; y < map->get_y() / map->get_res(); y++) {

			std::cout << map->get_ui()[y][x] << " | ";

		}
		std::cout << endl;
	}

}


