/*
 * User.h
 */

#ifndef USER_H_
#define USER_H_

#include "CardClass.h"
#include "cocos2d.h"

#define INIT_CARD_NUM 5

class User {
private:
	int userId;
	bool isNpc;
	std::map<int,CardClass*> hasCard;
	std::map<int,CardClass*> fieldCard;
	std::list<CardClass> deadCard;
public:

	int getUserId();
	int getRandEnableCard(std::list<int> playerFieldCard,std::list<int> targetFieldCard,PHASE phase);
	std::map<int,CardClass*> getHasCard();
	std::map<int,CardClass*> getFieldCard();
	std::list<int> getFieldCardList();
	std::list<CardClass> getDeadCard();

	User(int userId,bool isNpc);
	virtual ~User();

	void CreateStartHasCard();
	void DrawCard(int &key);
	bool UseCard(int key);
};

#endif /* USER_H_ */
