/*
 * Config.h
 *
 *  Created on: 2014/05/05
 *      Author: m.kamata
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define BASE_CARD_TAG 1000

enum PHASE{
	LOAD_PHASE = -1,
	DRAW_PHASE = 0,
	ACTION_PHASE = 1,
	ATTACK_PHASE = 2,
	DEFEND_PHASE = 3,
};

enum CARD_CATEGORY{
	NUMBERS = 1,
	ATTACK = 2,
	DEFEND = 3,
};

enum NUMBERS_ID{
	ONE =1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
};

enum ATTACK_CARD_ID{
	STEAL = 1,
	DESTROY = 2,
};

enum DEFEND_CARD_ID{
	GUARD = 1,
	PARRY = 2,
	COUNTER = 3,
};

enum CARD_VIEW_TYPE{
	HAS_CARD=1,
	FIELD_CARD=2,
	DEAD_CARD=3,
};


#endif /* CONFIG_H_ */
