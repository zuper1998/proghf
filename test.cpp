/*
 * test.cpp
 *
 *  Created on: 25 Apr 2018
 *      Author: Narcano
 */
#include "gtest_lite.h"
#include <iostream>
#include "Game.h"
#include "Character.h"
using namespace std;
#define MEMTRACE
int main() {
	//Player
	TEST(player,kons){
		Player p1;
		EXPECT_EQ(p1.get_location(0)[0],0)<< "kons 1 workin";
		EXPECT_EQ(p1.get_location(0)[1],0) <<"kons 2 working";

	}ENDM
	TEST(player,attack) {
		runner e1(0,3);
		Player p1;
		e1.attack(&p1);
		EXPECT_NE(p1.get_location()[0],0)<< "Mukodik attack";
		EXPECT_NE(p1.get_location(0)[1],0)<< "Jap its workin";
	}ENDM

	TEST(player,insert) {
		Player p1;
		MAP m;
		p1.insert(&m);
		for (int i =0;i < m.get_x();i++) {
			for( int k; k < m.get_y();k++) {
				if (m.get_gui()[i][k]!=0) {
					SUCCEED();
				}
			}

		}
	}ENDM

	TEST(player,move){
		MAP m;
		Player p1;
		EXPECT_EQ(p1.get_location(0)[0],0)<< "kons 1 workin";
		EXPECT_EQ(p1.get_location(0)[1],0) <<"kons 2 working";
		p1.move(2,m);
		EXPECT_EQ(p1.get_location(0)[0],0)<< "kons 1 workin";
		EXPECT_EQ(p1.get_location(0)[1],3) <<"kons 2 working";

	}ENDM


	TEST(player, move) {
		MAP m;
		Player p1;
		p1.move(8,m);
		EXPECT_EQ(p1.get_location(0)[0],0)<< "move loc 1 prob";
		EXPECT_EQ(p1.get_location(0)[1],p1.get_speed()) <<"move loc 2 prob";

	}ENDM

	//ENEMY
	TEST(enemy, multipleins) {
		MAP m;
		int count = 0;
		runner nib(2,2);
		nib.create_enemy(&m,2);
		for (int i =0;i < m.get_x();i++) {
			for( int k; k < m.get_y();k++) {
				if (m.get_gui()[2][2]!=0&&m.get_gui()[i][k]!=0) {
					count++;
					if (count==6) {
						SUCCEED();
					}
				}
			}

		}

	}ENDM

	TEST(enemy,checker) {
		Player p1;
		MAP m;
		runner nib1(0,3);
		runner niba(0,4);
		nib1.nextenemy=&niba;
		int res= nib1.check_other(&p1);
		EXPECT_EQ(1,res)<<"wrong enemy checker";

	}ENDM

	TEST(enemy,move) {
		Player p1;
		runner e1(0,4);
		MAP m;
		e1.create_enemy(&m,2);
		e1.move(&p1);
		EXPECT_EQ(e1.get_location(0)[0],0)<< "move loc 1 prob";
		EXPECT_EQ(e1.get_location(0)[1],1) <<"move loc 2 prob";

	}ENDM

// enemy subclasses
	TEST(enemy,skill){
		runner run(0,0);
		tank tanke(0,1);
		run.skill();
		tanke.skill();
		EXPECT_EQ(run.get_speed(),tanke.get_speed()*2);
		EXPECT_EQ(tanke.get_hp(),run.get_hp()*2);


	}ENDM
//MAP
	TEST(MAP,kons){
		MAP m1;

		EXPECT_EQ(500,m1.get_x())<<"map 1 bad";
		EXPECT_EQ(500,m1.get_y())<<"map 1 bad";



	}ENDM

//Game

	TEST(game, play){
		Game game;
		int i = game.play();
		EXPECT_EQ(0,i)<<"game.play not workin";

	}ENDM


}
