/*
 * player.h
 *
 *  Created on: 10 May 2018
 *      Author: Narcano
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include "Character.h"
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
void Player::attack(enemy* attacked, MAP* m) {
	if (abs(attacked->get_location(1)[0] - this->get_location(1)[0]) < 3
			|| abs(attacked->get_location(1)[1] - this->get_location(1)[1])
					< 3) {
		int *p = attacked->get_location(1);
		attacked->set_hp(attacked->get_hp() - this->get_dmg());
		for (int i = 0; i < 2; i++)						//eltolja a damadottat
			p[i] = abs(p[i] - get_location(1)[0] + get_speed()) % (m->get_x()/m->get_res());
	}
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

void Player::move(int direction, MAP *m) {
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

	int yx = m->get_x() / m->get_res() - 1;
	int xx = (m->get_y() / m->get_res() - 1);

	p[0] = abs(p[0] + get_speed() * dirmodx) % (yx);
	p[1] = abs(p[1] + get_speed() * dirmody) % xx;

}
void Player::skill(MAP* m) {
// whirlwind;
	enemy* enem = this->nextenemy;
	while (enem != NULL) {
		this->attack(enem, m);
		enem = enem->nextenemy;
	}

}



#endif /* PLAYER_H_ */
