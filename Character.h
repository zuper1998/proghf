/*
 * Character.h
 *
 *  Created on: 17 Apr 2018
 *      Author: Narcano
 */
class MAP;
#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Game.h"
class enemy;

class character {
	int hp;
	int dmg;
	int speed;
	int code = -1;

private:
	int* location; //x and y coordinates
public:
	character() {
		location = new int[2];
		speed = 3;
		hp = 50;
		dmg = 3;
		//skin = new char*[1]; // place holder
		location[0] = 0;
		location[1] = 0;
	}
	;
	virtual ~character()=0;
	virtual void move();
	;
	int* get_location() {
		int* temp_loc = new int[2];
		temp_loc[1] = location[1];
		temp_loc[0] = location[0];
		return temp_loc;
	}
	; //get copy of location array  WARNING: have to be deleted or memory leak

	int* get_location(int) {
		return location;
	}
	; //get the pointer to the location pointer
	int get_speed() {
		return speed;
	}
	;
	void set_speed(int i) {
		speed = i;
	}
	int get_code() {
		return code;
	}
	void set_hp(int i) {
		hp = i;
	}
	;

	int get_hp() {
		return hp;
	}
	;

	void set_code(int i) {
		code = i;
	}
	void insert(MAP *map, character* enemstarter);
	void set_dmg(int i) {
		dmg = i;
	}

	int get_dmg() {
		return dmg;
	}

};

class Player: public character { // marked with 1 on the ui
	int code = 1;
public:
	Player();
	Player(const char*, int skillt, int lvl);
	int playerskill_type;
	enemy* nextenemy = NULL;
	const char* player_name;
	void attack(enemy*,MAP*);
	void move(int, MAP* m);
	void skill(MAP*);
	void insert(MAP *map);

	~Player() {
		return;
	}
	;
};

class enemy: public character {
	int Ai_type = 1; //1 aggresive 2 swarm
public:
	void attack(Player*,MAP*);
	void insert(MAP *map);
	void create_enemy(MAP *map, int type);
	void move(Player*);
	enemy(size_t, size_t);
	enemy* nextenemy = NULL;
	int check_other(Player*);
	void Set_Ai_type();
	void virtual skill() {
		throw "this shouldnt happen";
	}
	;
	void garbage_collector(){
		enemy * enem = this;
		while (enem!=NULL){
			if (enem->get_hp()<1){
				enem->set_code(0);
				enem->set_dmg(0);
			}
			enem = enem->nextenemy;
		}
	}
	virtual ~enemy();
};

class runner: public enemy { //marked with 2 on ui

public:
	enemy* nextenemy = NULL;

	runner(size_t x, size_t y) :
			enemy(x, y) {
		get_location(1)[0] = x;
		get_location(1)[1] = y;
		set_code(2);
	}

	void skill();

};

class tank: public enemy { //marked with 3 on the ui
public:
	tank(size_t x, size_t y) :
			enemy(x, y) {
		get_location(1)[0] = x;
		get_location(1)[1] = y;
		set_code(3);
	}

	void skill();
};

#endif /* CHARACTER_H_ */
