/*
 * enemy.cpp
 *
 *  Created on: 17 Apr 2018
 *      Author: Narcano
 */
#include <iostream>
#include "Character.h"
using namespace std;
// PLAYER def
#define TESTING
int abs(int szam) {
	return szam < 0 ? -szam : szam;

}
void character::move() {
}

character::~character() {
return;
}

//ENEMY def
void enemy::insert(MAP *map) {
	enemy* enemstart = this;

	while (enemstart->nextenemy != NULL) {
		if (enemstart->get_location(1)[0] > 0
				&& enemstart->get_location(1)[0]
						< (map->get_x() / map->get_res() - 1)
				&& enemstart->get_location(1)[1] > 0
				&& enemstart->get_location(1)[1]
						< (map->get_x() / map->get_res() - 1)) {

			map->get_ui()[enemstart->get_location(1)[0]][enemstart->get_location(
					1)[1]] = enemstart->get_code();

		}
		enemstart = enemstart->nextenemy;

	}
}

void enemy::create_enemy(MAP *map, int type) {

	/*
	 0
	 3		1
	 2
	 */
	enemy* tmp;
	tmp = this;

	size_t x = (map->get_x() / map->get_res()) - 1;
	size_t y = (map->get_y() / map->get_res()) - 1;
	size_t spawn_x = x;
	size_t spawn_y = y;
	size_t random = rand() % 4;

	switch (random) {
	case 0:
		spawn_x = rand() % x;
		break;
	case 1:
		spawn_y = rand() % y;
		break;
	case 2:
		spawn_x = rand() % x;
		spawn_y = 0;
		break;
	case 3:
		spawn_x = 0;
		spawn_y = rand() % x;

		break;

	}
	x = x < 0 ? -x : x;
	y = y < 0 ? -y : y;

	if (map->get_ui()[spawn_x][spawn_y] != 0) {
		create_enemy(map, type);
	}

	while (tmp->nextenemy != NULL) {
		tmp = tmp->nextenemy;
	}

	if (type == 2) {
		runner* new_enemy1 = new runner(spawn_x, spawn_y); // new_enemy(spawn_x, spawn_y);

		tmp->nextenemy = new_enemy1;
	}
	if (type == 3) {
		tank* new_enemy2 = new tank(spawn_x, spawn_y); // new_enemy(spawn_x, spawn_y);

		tmp->nextenemy = new_enemy2;
	}

	this->insert(map);
}

enemy::enemy(size_t x, size_t y) {
	get_location(1)[0] = x;
	get_location(1)[1] = y;
}

enemy::~enemy() {

		delete[] get_location(0);

	return;
}

int enemy::check_other(Player *player) { //1 up - 2 down - 3 left - 4 down
	int up = 0, down = 0, left = 0, right = 0;

	enemy* ep = this;

	while (ep != NULL) {

		if (player->get_location(1)[0] > ep->get_location(1)[0]) {
			left++;
		}
		if (player->get_location(1)[0] < ep->get_location(1)[0]) {
			right++;
		}
		if (player->get_location(1)[1] > ep->get_location(1)[1]) {
			down++;
		}
		if (player->get_location(1)[1] < ep->get_location(1)[1]) {
			up++;
		}
		ep = ep->nextenemy;
	}

	if (up > down)
		return 1;
	else if (down > up)
		return 2;
	if (right > left)
		return 3;
	else
		return 4;
}

void enemy::attack(Player* attacked, MAP* m) {
	if (this->get_dmg() != 0) {
		if (abs(attacked->get_location(1)[0] - this->get_location(1)[0]) < 3
				|| abs(attacked->get_location(1)[1] - this->get_location(1)[1])
						< 3) {
			int *p = attacked->get_location(1);
			attacked->set_hp(attacked->get_hp() - this->get_dmg());
			for (int i = 0; i < 2; i++)					//eltolja a damadottat
				p[i] = abs(p[i] - get_location(1)[i] + get_speed())
						% (m->get_x() / m->get_res() - 1);
		}
	}
	if (this->nextenemy != NULL) {
		this->nextenemy->attack(attacked, m);
	}
	int k = rand() % 4;
	if (k == 1) {
		this->skill();
	}
}

void enemy::move(Player* p1) {

	enemy* ep = this;
	while (ep != NULL) {
		if (p1->get_location(1)[0] > ep->get_location(1)[0]) {
			get_location(1)[0] = abs(get_location(1)[0] + get_speed());

		}
		if (p1->get_location(1)[0] < ep->get_location(1)[0]) {
			get_location(1)[0] = abs(get_location(1)[0] - get_speed());

		}
		if (p1->get_location(1)[1] > ep->get_location(1)[1]) {
			get_location(1)[1] = abs(get_location(1)[1] + get_speed());

		}
		if (p1->get_location(1)[1] < ep->get_location(1)[1]) {
			get_location(1)[1] = abs(get_location(1)[1] - get_speed());

		}

		ep = ep->nextenemy;
	}
}

//enemy subcalss def

void runner::skill() {
	this->set_speed(get_speed() * 2);
#ifndef TESTING
	std::cout << "G O T A  G O  F A S T" << std::endl;
#endif
}

void tank::skill() {
	this->set_hp(get_hp() * 2);
#ifndef TESTING

	std::cout << "Me is B I G" << std::endl;
#endif
}

