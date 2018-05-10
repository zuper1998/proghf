/*
 * Game.cpp
 *
 *  Created on: 17 Apr 2018
 *      Author: Narcano
 */
#define TESTING
#include <iostream>
#include "Game.h"
#include <fstream>
#include "player.h"
using namespace std;
size_t MAP::defsize = 500;

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

void MAP::ins_gui() {
	char a;
	const char* filename;
	for (size_t x = 0; x < this->sizex; x++) {
		for (size_t y = 0; y < this->sizey; y++) {
			if ((y % resolution == 0) && (x % resolution == 0)) {
				int k = (ui[x / resolution][y / resolution]);

				if (k == 1) {
					filename = "hero.txt";

				} else if (k == 2) {
					filename = "enemy1.txt";

				} else if (k == 3) {
					filename = "enemy2.txt";
				} else {
					filename = "";
				}

				std::ifstream infile(filename);
				for (size_t ix = x; ix < x + 10; ix++) {
					for (size_t iy = y; iy < y + 10; iy++) {
						a = '-';
						(infile >> a);
						gui[iy][ix] = a;
					}
				}
			}

		}

	}

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

void MAP::print_gui() {

	for (size_t x = 0; x < this->sizex; x++) {
		for (size_t y = 0; y < this->sizey; y++) {
			std::cout << this->get_gui()[y][x];

		}
		std::cout << endl;
	}

	std::cout << "Movement: the corresponging key on the numpad" << endl
			<< "skill: 0" << endl << "attack: 5" << endl
			<< "your character code is 1" << endl;

}

void MAP::print_ui() {
	for (int x = 0; x < this->get_x() / this->get_res(); x++) {
		for (int y = 0; y < this->get_y() / this->get_res(); y++) {

			std::cout << this->get_ui()[y][x] << " | ";

		}
		std::cout << endl;
	}
}

//Game def

Game::Game() {
	MAP map;
}


int Game::end(){
	std::cout<<"You survived "<<turns_taken<<" turns";
	return turns_taken;
}



int Game::play() {
	MAP map;
	Player p1;
	runner nib(2, 0);
	p1.nextenemy = &nib;
	p1.insert(&map);
	p1.nextenemy->insert(&map);
	nib.create_enemy(&map, 2);
	map.ins_gui();
	map.print_gui();
	//map.print_ui();

	for (int x = 0; p1.get_hp() > 0; x++) {
		turn(&map, &p1);
		turntaken();
	}

	return 0;
}

void turn(MAP* map, Player*p1) {
	int input;
	map->reset();

#ifndef TESTING
	std::cin >> input;

	while (std::cin.fail()) {
		std::cout << "Hibas bemenet"<<std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> input;
	}
#endif
#ifdef TESTING
	input = 2;
#endif

	if (input == 5) {
		enemy* enem = p1->nextenemy;
		while (enem != NULL) {
			if (abs(enem->get_location(1)[0] - p1->get_location(1)[0]) < 3
					|| abs(enem->get_location(1)[1] - p1->get_location(1)[1])
							< 3) {
				p1->attack(enem, map);
			}
			enem = enem->nextenemy;
		}
	}
	if (input == 0) {
		p1->skill(map);
	}
	p1->move(input, map);
	p1->insert(map);
	p1->nextenemy->insert(map);
	p1->nextenemy->move(p1);
	p1->nextenemy->attack(p1, map);
	p1->nextenemy->create_enemy(map, (rand() % 2) + 1);
	//map->print_ui();
	map->ins_gui();
	map->print_gui();
	p1->nextenemy->garbage_collector();
}

