/*
 * DefendCard.cpp
 *
 *  Created on: 2014/05/06
 *      Author: m.kamata
 */

#include "DefendCard.h"
using namespace std;
using namespace cocos2d;

DefendCard::DefendCard(CARD_CATEGORY category , int id,int tag) :CardClass(category , id,tag){

}

DefendCard::~DefendCard() {
}


bool DefendCard::IsEnabled(list<int> playerFieldCard,list<int> targetFieldCard,PHASE phase){
	CCLog("守りカード");
	return phase == DEFEND_PHASE;
}


const char* DefendCard::getImageFileName(){

	switch((DEFEND_CARD_ID)id){
		case GUARD:
			return "card/guard.jpg";
		case PARRY:
			return "card/parry.jpg";
		case COUNTER:
			return "card/counter.jpg";
	}
	return "";
}
