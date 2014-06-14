/*
 * AttackCard.cpp
 */

#include "AttackCard.h"
using namespace std;
using namespace cocos2d;

AttackCard::AttackCard(CARD_CATEGORY category , int id,int tag) :CardClass(category , id,tag){
}

AttackCard::~AttackCard() {
}


bool AttackCard::IsEnabled(list<int> playerFieldCard,list<int> targetFieldCard,PHASE phase){
	CCLog("攻撃カード");
	if(phase != ACTION_PHASE)
		return false;

	//フィールドに存在してなければ使用可能
	int cnt = targetFieldCard.size();
	return cnt > 0;
}


const char* AttackCard::getImageFileName(){
	switch((ATTACK_CARD_ID)id){
	case STEAL:
		return "card/steal.jpg";
	case DESTROY:
		return "card/destroy.jpg";
	}
		return "";
}
