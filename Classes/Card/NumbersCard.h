/*
 * NumbersCard.h
 *
 *  Created on: 2014/05/06
 *      Author: m.kamata
 */

#ifndef NUMBERSCARD_H_
#define NUMBERSCARD_H_

#include "CardClass.h"
#include "cocos2d.h"


class NumbersCard: public CardClass {
public:
	NumbersCard();
	NumbersCard(CARD_CATEGORY category , int id,int tag);
	virtual ~NumbersCard();

	virtual bool IsEnabled(std::list<int> playerFieldCard,std::list<int> targetFieldCard,PHASE phase);
	virtual const char* getImageFileName();
};

#endif /* NUMBERSCARD_H_ */
