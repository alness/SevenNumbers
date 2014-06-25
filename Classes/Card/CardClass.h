/*
 * CardClass.h
 *
 *  Created on: 2014/05/05
 *      Author: m.kamata
 */

#ifndef CARDCLASS_H_
#define CARDCLASS_H_


#include "cocos2d.h"
#include "Config.h"
#include <string>

class CardClass : public cocos2d::CCSprite
{
private :
protected:
	CARD_CATEGORY category;
	int tag;
	int id;
public:
	CARD_CATEGORY getCategory();
	int getId();
	int getTag();
	void setTag(int tag);

	CardClass();
	CardClass(CARD_CATEGORY category , int id,int tag); //指定生成
	virtual ~CardClass();
	virtual bool initCard();
	virtual bool IsEnabled(std::list<int> playerFieldCard,std::list<int> targetFieldCard,PHASE phase);
	virtual const char* getImageFileName();

	static CardClass* createCard(CARD_CATEGORY category,int id,int tag);
};



#endif /* CARDCLASS_H_ */
