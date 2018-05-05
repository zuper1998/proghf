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

int abs(int szam) {
	return szam < 0 ? -szam : szam;

}
character::~character() {
	delete[] location;
}

void character::attack(character* attacked) {
	int *p = attacked->get_location(1);
	attacked->hp -= dmg;

	for (int i = 0; i < 2; i++)						//eltolja a damadottat
		p[i] = abs(p[i] - location[0]) + speed;

}
Player::Player() {
	get_location(1)[0] = 0;
	get_location(1)[1] = 0;
	player_name = "KOCDYR";
	playerskill_type = 0;
	set_dmg(6);
	set_hp(100);
	set_speed(2);
	set_code(1);

}
Player::Player(const char* name, int skillt, int lvl) {
	int *location_d = get_location(1);
	location_d[0] = 0;
	location_d[1] = 0;
	player_name = name;
	playerskill_type = skillt;
	set_dmg(6 * lvl);
	set_hp(100 * lvl);
	set_speed(5 * lvl);
	set_code(1 * lvl);
}

void Player::insert(MAP *map) {
	if (this->get_location(1)[0] > map->get_y()) {
		this->get_location(1)[0] = map->get_y() - 1;
	} else if (this->get_location(1)[0] > map->get_x()) {
		this->get_location(1)[0] = map->get_x() - 1;
	}
	Player* enemstart = this;
	map->get_ui()[enemstart->get_location(1)[0]][enemstart->get_location(1)[1]] =
			enemstart->get_code();
}

void Player::move(int direction,MAP m) {
	/*
	 7  8  9
	 4  5  6
	 1  2  3*/
	int *p = get_location(1);
	int dirmody = 1;
	int dirmodx = 1;
	switch (direction) {

	case 1:
		dirmodx = -1;
		dirmody = -1;

		break;
	case 2:
		dirmodx = 0;
		dirmody = -1;

		break;
	case 3:
		dirmody = -1;

		break;
	case 4:
		dirmodx = -1;
		dirmody = 0;

		break;
	case 5:
		dirmodx = 0;
		dirmody = 0;

		break;

	case 6:
		dirmody = 0;

		break;
	case 7:
		dirmodx = -1;

		break;
	case 8:
		dirmodx = 0;

		break;
	default:
		break;

	}

	int yx=m.get_x()/m.get_res()-1;
	int xx=(m.get_y()/m.get_res()-1);

	p[0] = abs(p[0] + get_speed() * dirmodx)%(yx);
	p[1] = abs(p[1] + get_speed() * dirmody)%xx;

}
void Player::skill() {
	std::cout << "using skill" << playerskill_type << std::endl;
}

//ENEMY def
void enemy::insert(MAP *map) {
	enemy* enemstart = this;
	map->get_ui()[enemstart->get_location(1)[0]][enemstart->get_location(1)[1]] =
			enemstart->get_code();
	while (enemstart->nextenemy != NULL) {
		enemstart = enemstart->nextenemy;
		map->get_ui()[enemstart->get_location(1)[0]][enemstart->get_location(1)[1]] =
				enemstart->get_code();

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

void enemy::Set_Ai_type() {
	Ai_type = 2;
}

void enemy::move(Player* p1) {

	enemy* ep = this;

	if (p1->get_location(1)[0] > ep->get_location(1)[0]) {
		get_location(1)[0] = abs(get_location(1)[0]+get_speed());

	}
	if (p1->get_location(1)[0] < ep->get_location(1)[0]) {
		get_location(1)[0] = abs(get_location(1)[0]-get_speed());

	}
	if (p1->get_location(1)[1] > ep->get_location(1)[1]) {
		get_location(1)[1] = abs(get_location(1)[1]+ get_speed());

	}
	if (p1->get_location(1)[1] < ep->get_location(1)[1]) {
		get_location(1)[1] = abs(get_location(1)[1]-get_speed());

	}
	ep = ep->nextenemy;

}

//enemy subcalss def

void runner::skill() {
	this->set_speed(get_speed() * 2);
	std::cout << "G O T A  G O  F A S T" << std::endl;
}

void tank::skill() {
	this->set_hp(get_hp() * 2);
	std::cout << "Me is B I G" << std::endl;
}

