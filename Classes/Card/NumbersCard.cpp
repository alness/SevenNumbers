/*
 * NumbersCard.cpp
 */

#include "NumbersCard.h"
#include <algorithm>
#include <iostream>
#include <list>
using namespace std;
using namespace cocos2d;

NumbersCard::NumbersCard():CardClass(){

}
NumbersCard::NumbersCard(CARD_CATEGORY category , int id,int tag) :CardClass(category , id, tag ){

}

NumbersCard::~NumbersCard() {

}


bool NumbersCard::IsEnabled(list<int> playerFieldCard,list<int> targetFieldCard,PHASE phase){

	CCLog("NumbersCard::IsEnabled");
	if(phase != ACTION_PHASE)
		return false;

	CCLog("NumbersCard::IsEnabled PhaseCheck ok");
	//フィールドに存在してなければ使用可能
	list<int>::iterator pos;
	if(playerFieldCard.size() == 0)
		return true;

	CCLog("NumbersCard::IsEnabled SizeCheck ok");
	pos = find( playerFieldCard.begin(), playerFieldCard.end(), id );
	return pos == playerFieldCard.end();

}


const char* NumbersCard::getImageFileName(){

	switch(id){
		case 1:
			return "card/1.jpg";
		case 2:
			return "card/2.jpg";
		case 3:
			return "card/3.jpg";
		case 4:
			return "card/4.jpg";
		case 5:
			return "card/5.jpg";
		case 6:
			return "card/6.jpg";
		case 7:
			return "card/7.jpg";
		break;
	}
	return "";
}

