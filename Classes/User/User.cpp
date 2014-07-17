/*
 * User.cpp
 *
 *  Created on: 2014/05/06
 *      Author: m.kamata
 */

#include "User.h"
#include "CardUtil.h"

using namespace std;
using namespace cocos2d;


User::User(int userId,bool isNpc) {
	this->userId = userId;
	this->isNpc = isNpc;
	CreateStartHasCard();
}

User::~User() {

//	  for (map<int,CardClass*>::iterator it = hasCard.begin(); it != hasCard.end(); ++it) {
//	        delete (it->second);
//	    }
//	  hasCard.clear();
//
//	  for (map<int,CardClass*>::iterator it = fieldCard.begin(); it != fieldCard.end(); ++it) {
//	        delete (it->second);
//	    }
//	  fieldCard.clear();
}

int User::getUserId(){
	return userId;
}

int User::getRandEnableCard(list<int> playerFieldCard,list<int> targetFieldCard,PHASE phase){
	CCLog("getRandEnableCard");
	map<int, CardClass*> enableCard;
	list<int> keyList;
	map<int, CardClass*>::iterator it = hasCard.begin();

	while(it != hasCard.end() )
	{
		CCLog("getRandEnableCard while first:%d ",it->first);
		if(it->second && it->second->IsEnabled(playerFieldCard,targetFieldCard,phase)){
			CCLog("getRandEnableCard while IsEnabled first:%d",it->first);
			enableCard.insert(pair<int, CardClass*>( it->first,it->second));
			keyList.push_back(it->first);
		}
		++it;
	}

	CCLog("getRandEnableCard return keyList.size:%d",keyList.size());
	if(keyList.size() == 0)
		return -1;


	int randNum = rand() % keyList.size();
	CCLog("getRandEnableCard return key:%d",randNum);
	return randNum;

}

map<int,CardClass*> User::getHasCard(){
	return hasCard;
}

map<int,CardClass*> User::getFieldCard(){
	return fieldCard;
}

list<int> User::getFieldCardList(){

	list<int> ret;
	map<int, CardClass*>::iterator it = fieldCard.begin();
	while( it != fieldCard.end() )
	{
		ret.push_back(it->first);
		++it;
	}
	return ret;
}

void User::CreateStartHasCard(){
	for(int i = 0; i < INIT_CARD_NUM;i++){
		//カードを生成
		CardClass *pCard = CardUtil::createCard();
		hasCard.insert(pair<int,CardClass*>(i,pCard));
	}
}

void User::DrawCard(int &key){
	CCLog("User::DrawCard");
	CardClass *pCard = CardUtil::createCard();

	int i = 0;
	map<int,CardClass*>::iterator it = hasCard.find(i);

	while(it != hasCard.end()){
		CCLog("hasCard.find :%d",i);
		it = hasCard.find(++i);
	}
	hasCard.insert(pair<int,CardClass*>(i,pCard));
	CCLog("hasCard.insert");
	key = i;

}

bool User::UseCard(int key){

	bool ret = false;
	CardClass* pCard = hasCard[key];
	switch(pCard->getCategory()){
	case NUMBERS:
		CCLOG("UseCard:NUMBERS %d",key);
		fieldCard[pCard->getId()] = pCard;
		hasCard.erase(key);
		ret = true;
		break;
	case ATTACK:
		CCLOG("UseCard:ATTACK %d",key);
		break;
	case DEFEND:
		CCLOG("UseCard:DEFEND %d",key);
		break;
	}
	return ret;
}











