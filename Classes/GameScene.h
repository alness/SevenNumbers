
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Config.h"
#include "User.h"

#define BACKGROUND_IMAGE "bg.png"
#define PASS_IMAGE "pass.png"
#define NUMBERS_CARD_NUM 8
#define ATTACK_CARD_NUM 4
#define DEFEND_CARD_NUM 4

class GameScene : public cocos2d::CCLayer
{
private :
	User* pPlayer;
	User* pNpc;
	int targetPlayerId;
	PHASE phase;

	void update(float delta);
	void nextTurn();

	void playerDraw();
	void npcDraw();
	void npcAction();
protected:
	enum kTag{
		kTagBackground = 1,
		kTagPass = 2,
		kTagBaseCard = BASE_CARD_TAG,

	};
	enum kZOrder{
		kZOrderBackground,
		kZOrderCard,
		kZOrderPass,
	};

	cocos2d::CCSprite* m_background;
	cocos2d::CCSprite* m_pass;
	void showBackground();

	float m_cardHeight;
	float m_cardWidth;

	void initForVariables();
	void showPlayerCard();
	void showNpcCard();
	void showPass();

	void actionTauch(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);


public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);

    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

    virtual ~GameScene();

};

#endif // __GAME_SCENE_H__
