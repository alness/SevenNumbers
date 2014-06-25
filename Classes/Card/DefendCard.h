/*
 * DefendCard.h
 *
 *  Created on: 2014/05/06
 *      Author: m.kamata
 */

#ifndef DEFENDCARD_H_
#define DEFENDCARD_H_

#include "CardClass.h"

class DefendCard: public CardClass {
public:
	DefendCard(CARD_CATEGORY category , int id,int tag);
	virtual ~DefendCard();
	virtual bool IsEnabled(std::list<int> playerFieldCard,std::list<int> targetFieldCard,PHASE phase);
	virtual const char* getImageFileName();
};

#endif /* DEFENDCARD_H_ */
