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
	TEST(player,attack){
		runner e1(0,3);
		Player p1;
		e1.attack(&p1);
		EXPECT_NE(p1.get_location()[0],0)<< "Mukodik attack";
		EXPECT_NE(p1.get_location(0)[1],0)<< "Jap its workin";
	}ENDM

	TEST(player,insert){
		Player p1;
		MAP m;
		p1.insert(&m);
		for (int i =0;i < m.get_x();i++){
			for( int k; k < m.get_y();k++){
				if (m.get_gui()[i][k]!=0){
					 SUCCEED();
			}
		}



	}
	}ENDM
	//ENEMY
	TEST(enemy, multipleins){
		MAP m;
		int count = 0;
		runner nib(2,2);
		nib.create_enemy(&m,2,&nib);
		for (int i =0;i < m.get_x();i++){
					for( int k; k < m.get_y();k++){
						if (m.get_gui()[2][2]!=0&&m.get_gui()[i][k]!=0){
							count++;
							if (count==6){
								SUCCEED();
							}
					}
				}

	}ENDM

}



	TEST(enemy,checker){
		Player p1;
		MAP m;
		runner nib(1,3);
		nib.create_enemy(&m,2,&nib);



	}ENDM


}
