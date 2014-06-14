/*
 * AttackCard.h
 */

#ifndef ATTACKCARD_H_
#define ATTACKCARD_H_

#include "CardClass.h"

class AttackCard: public CardClass {
public:
	AttackCard(CARD_CATEGORY category , int id,int tag);
	virtual ~AttackCard();
	virtual bool IsEnabled(std::list<int> playerFieldCard,std::list<int> targetFieldCard,PHASE phase);
	virtual const char* getImageFileName();
};

#endif /* ATTACKCARD_H_ */
