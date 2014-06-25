/*
 * CardUtil.cpp
 *
 *  Created on: 2014/05/06
 *      Author: m.kamata
 */


#include "CardUtil.h"
#include "Config.h"

using namespace std;
using namespace cocos2d;

map<pair<CARD_CATEGORY, int>,int > CardUtil::m_allCard; //カードカテゴリ毎→ID毎のタググループ管理
int CardUtil::m_allCountUp = 0;

CardUtil::CardUtil() {

}

CardUtil::~CardUtil() {

}

bool CardUtil::IsAllCardEnabled(){
	int allCount = 0;
	for(int i = 1 ; i <= CATEGORY_TYPE_COUNT;i++){
		int idCount;
		switch(i){
		case 1:
			idCount = NUMBERS_TYPE_COUNT;
			break;
		case 2:
			idCount = ATTACK_TYPE_COUNT;
			break;
		case 3:
			idCount = DEFEND_TYPE_COUNT;
			break;
		default:
			idCount = 0;
			break;
		}

		for(int j = 1 ; j <= idCount;j++){
			allCount += m_allCard[pair<CARD_CATEGORY,int>((CARD_CATEGORY)i,j)];
		}
	}
	int max = NUMBERS_TYPE_COUNT * NUMBERS_CARD_NUM +ATTACK_TYPE_COUNT * ATTACK_CARD_NUM + DEFEND_TYPE_COUNT *  DEFEND_CARD_NUM;
	return allCount < max;
}

bool CardUtil::IsCategoryEnabled(CARD_CATEGORY category){

	int categoryCount = 0;
	int max = 0;
		int idCount;
		switch(category){
		case NUMBERS:
			idCount = NUMBERS_TYPE_COUNT;
			max = NUMBERS_TYPE_COUNT * NUMBERS_CARD_NUM ;
			break;
		case ATTACK:
			idCount = ATTACK_TYPE_COUNT;
			max = ATTACK_TYPE_COUNT * ATTACK_CARD_NUM ;
			break;
		case DEFEND:
			idCount = DEFEND_TYPE_COUNT;
			max = DEFEND_TYPE_COUNT *  DEFEND_CARD_NUM;
			break;
		}
		for(int i = 1 ; i <= idCount;i++){
			categoryCount += m_allCard[pair<CARD_CATEGORY,int>(category,i)];
		}
	return categoryCount < max;
}

void CardUtil::UpdateAllCard(CARD_CATEGORY category,int id){
	map<pair<CARD_CATEGORY, int>,int>::iterator itr;
	pair<CARD_CATEGORY,int> key = pair<CARD_CATEGORY,int>(category,id);
	itr = m_allCard.find(key);

	if(itr != m_allCard.end()){
		m_allCard[key] += 1;
	}
	else{
		m_allCard[key] = 1;
	}
	m_allCountUp++;
}

CardClass* CardUtil::createCard(){

	CCLog("createCard");
	//全カード枚数チェック
	if(!IsAllCardEnabled()){
		CCLog("全カード枚数チェックでエラー");
		return NULL;
	}

	CARD_CATEGORY category = (CARD_CATEGORY)(rand() % 3 + 1);
	while(!IsCategoryEnabled(category)){
		category = (CARD_CATEGORY)(rand() % 3 + 1);
	}
	int id = 0;
	int max = 0;
	switch(category){
	case NUMBERS:
		id = rand() % NUMBERS_TYPE_COUNT + 1;
		max = NUMBERS_CARD_NUM;
		break;
	case ATTACK:
		id = rand() % ATTACK_TYPE_COUNT + 1;
		max = ATTACK_CARD_NUM;
		break;
	case DEFEND:
		id = rand() % DEFEND_TYPE_COUNT+ 1;
		max = DEFEND_CARD_NUM;
			break;
		}
	while(m_allCard[pair<CARD_CATEGORY,int>(category,id)] >= max){
		switch(category){
			case NUMBERS:
				id = rand() % NUMBERS_TYPE_COUNT + 1;
				max = NUMBERS_CARD_NUM;
				break;
			case ATTACK:
				id = rand() % ATTACK_TYPE_COUNT + 1;
				max = ATTACK_CARD_NUM;
				break;
			case DEFEND:
				id = rand() % DEFEND_TYPE_COUNT + 1;
				max = DEFEND_CARD_NUM;
				break;
			}
	}

	UpdateAllCard(category,id);
	CCLog("createCard category:%d,id:%d,tag:%d",category,id,BASE_CARD_TAG + m_allCountUp);
	CardClass* pCard =CardClass::createCard(category,id,BASE_CARD_TAG + m_allCountUp);

	return pCard;
}

CCPoint CardUtil::getCardPosition(CardClass* pCard,CARD_VIEW_TYPE viewType,int key,float addOffsetX,float addOffsetY){

	CCLog("getCardPosition");
	CCPoint point;
	float offsetX = addOffsetX;
	float offsetY = addOffsetY;

	CCLog("getCardPosition getSize");
	//カードのサイズ取得

	float cardWidth = 0;
	float cardHeight = 0;
	if(pCard){
		CCLog("getCardPosition pCard true");

		cardWidth = pCard->getContentSize().width;
		cardHeight = pCard->getContentSize().height;
	}

	CCLog("getCardPosition switch viewType:%d",viewType);
	switch(viewType){
	case HAS_CARD:
		point = CCPoint(cardWidth * (key-1) + offsetX,cardHeight*1.5 + offsetY);
		break;
	case FIELD_CARD:
		offsetY += cardHeight*2;
		point = CCPoint(cardWidth * (key) + offsetX,cardHeight + offsetY);
		break;
	case DEAD_CARD:
		break;
	}
	return point;
}

//初期化
void CardUtil::initCardUtil(){
	CardUtil::m_allCard.clear();
	CardUtil::m_allCountUp = 0;
}












