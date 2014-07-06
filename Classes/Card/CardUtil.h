/*
 * CardUtil.h
 *
 *  Created on: 2014/05/06
 *      Author: m.kamata
 */

#ifndef CARDUTIL_H_
#define CARDUTIL_H_

#include "CardClass.h"
#include "Config.h"
#include "cocos2d.h"

#define CATEGORY_TYPE_COUNT 3
#define NUMBERS_TYPE_COUNT 7
#define ATTACK_TYPE_COUNT 2
#define DEFEND_TYPE_COUNT 2

#define NUMBERS_CARD_NUM 4
#define ATTACK_CARD_NUM 3
#define DEFEND_CARD_NUM 2

class CardUtil {
private :
	static bool IsAllCardEnabled();
	static bool IsCategoryEnabled(CARD_CATEGORY category);
	static void UpdateAllCard(CARD_CATEGORY category,int id);
public:
	CardUtil();
	virtual ~CardUtil();

	static std::map<std::pair<CARD_CATEGORY, int>,int > m_allCard; //カードカテゴリ毎→ID毎のタググループ管理
	static int m_allCountUp;
	static CardClass* createCard();
	static cocos2d::CCPoint getCardPosition(CardClass* pCard, CARD_VIEW_TYPE viewType,int key,float addOffsetX,float addOffsetY);
	static void initCardUtil();
};

#endif /* CARDUTIL_H_ */
