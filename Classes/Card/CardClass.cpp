/*
 * CardClass.cpp
 *
 *  Created on: 2014/05/05
 *      Author: m.kamata
 */


#include "CardClass.h"
#include "NumbersCard.h"
#include "AttackCard.h"
#include "DefendCard.h"
#include <stdio.h>
#include <string>

using namespace std;
using namespace cocos2d;


CardClass::CardClass(){
}
CardClass::CardClass(CARD_CATEGORY category,int id,int tag){
	this->category = category;
	this->id = id;
	this->tag = tag;
}
CardClass::~CardClass(){

}

CardClass* CardClass::createCard(CARD_CATEGORY category,int id,int tag){

	CardClass *pCard;
	switch(category){
	case NUMBERS:
		pCard = new NumbersCard(category,id,tag);
		break;
	case ATTACK:
		pCard = new AttackCard(category,id,tag);
		break;
	case DEFEND:
		pCard = new DefendCard(category,id,tag);
		break;
	default :
		pCard = new CardClass(category,id,tag);
		break;
	}


	if(pCard && pCard->initCard()){
		CCLog("card autorelease");
		return pCard;
	}
	else{
		CC_SAFE_DELETE(pCard);
		CCLog("CC_SAFE_DELETE");
		return NULL;
	}
}

bool CardClass::initCard(){

	CCLog("initCard file name :%s",getImageFileName());
	if(!CCSprite::initWithFile(getImageFileName())){
		return false;
	}
	return true;
}

bool CardClass::IsEnabled(list<int> playerFieldCard,list<int> targetFieldCard,PHASE phase){
	CCLog("親クラスにくる・・・だと・・？　IsEnabled編");
	return false;
	//TODO 継承クラス先で各自定義
}


const char* CardClass::getImageFileName(){
	CCLog("親クラスにくる・・・だと・・？ getImageFileName編");
	return "";
}

CARD_CATEGORY CardClass::getCategory(){	return category;}
int CardClass::getId(){	return id;}

int CardClass::getTag(){
	return tag;
}

void CardClass::setTag(int tag){
	CCLog("before tag:%d",this->tag);
	this->tag = tag;
	CCLog("after tag:%d",this->tag);
}
