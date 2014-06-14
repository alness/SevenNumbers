/*
 * GameScene.cpp
 */

#include "GameScene.h"
#include "CardClass.h"
#include "SimpleAudioEngine.h"
#include "CardUtil.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

GameScene::~GameScene() {
	delete pPlayer;
	delete pNpc;
}

CCScene* GameScene::scene(){
	CCScene* scene = CCScene::create();
	GameScene* layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

//初期化
bool GameScene::init(){
	if(!CCLayer::init()){
		return false;
	}
	//タップイベントの取得
	CCLog("タップイベントの取得");
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	//変数初期化
	CCLog("変数初期化");
	initForVariables();
	//背景表示
	CCLog("背景表示");
	showBackground();
	//カード表示
	CCLog("カード表示");
	showPlayerCard();
	showNpcCard();

	CCLog("パスボタン表示");
	showPass();

	phase = DRAW_PHASE;
	//フレーム処理
	CCLog("フレーム処理");
	this->scheduleUpdate();

	return true;
}

//フレーム処理の内容
void GameScene::update(float delta){

	switch(phase){
	case DRAW_PHASE:
		if(targetPlayerId == 1){
			playerDraw();
		}
		else{
			npcDraw();
		}
		break;
	case ACTION_PHASE:
		if(targetPlayerId != 1){
			npcAction();
		}
		break;
	}
}

void GameScene::nextTurn(){
	if(targetPlayerId ==1){
		targetPlayerId = 2;
	}
	else{
		targetPlayerId = 1;
	}
}

void GameScene::playerDraw(){

	int key=0;
	pPlayer->DrawCard(key);
	phase = ACTION_PHASE;
	showPlayerCard();

	CCLog("playerDraw");
}

void GameScene::npcDraw(){

//	int key=0;
//	pNpc->DrawCard(key);
	phase = ACTION_PHASE;
	CCLog("npcDraw");
}

void GameScene::npcAction(){

	CCLog("npcAction start");
	bool ret = false;
	//int randKey =  pNpc->getRandEnableCard(pNpc->getFieldCardList(),pPlayer->getFieldCardList(),phase);
//	int randKey = rand() % 6 -1;
	int randKey = -1;

	if(randKey == -1){
		CCLog("npcAction パス");
		ret = true; //パス
	}
	else if(randKey != -1){
		ret = pNpc->UseCard(randKey);
	}

	if(ret){
		CCLog("npcAction ret = true");
		phase = DRAW_PHASE;
		nextTurn();
		showNpcCard();
	}
	CCLog("npcAction end");
}

void GameScene::initForVariables(){
	srand((unsigned)time(NULL)); //乱数初期化

	//プレイヤー生成
	pPlayer = new User(1,false);
	pNpc = new User(2,true);
	targetPlayerId = 1;
	CCLog("initForVariables");
}

void GameScene::showBackground(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//背景を生成
	m_background = CCSprite::create(BACKGROUND_IMAGE);
	m_background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	addChild(m_background,kZOrderBackground, kTagBackground);
}

void GameScene::showPlayerCard(){

	CCLog("showCard");
	float offsetX = m_background->getContentSize().width * 0.3;
	float offsetY = 0;

	map<int, CardClass*> hasCard = pPlayer->getHasCard();
	list<int> playerField = pPlayer->getFieldCardList();
	list<int> npcField = pNpc->getFieldCardList();
	map<int, CardClass*>::iterator it = hasCard.begin();

	map<int, CardClass*> fieldCard = pPlayer->getFieldCard();
	map<int, CardClass*>::iterator fieldIt = fieldCard.begin();

	//手持ちカードの表示
	CCLog("showCard hasCard");
	while( it != hasCard.end() )
	{
		CardClass *pCard = it->second;
		CCLog("hasCard loop tag:%d",pCard->getTag());
		if(pCard->IsEnabled(playerField,npcField,ACTION_PHASE)){
			CCLog("true");
			offsetY = 50;
		}
		else{
			CCLog("false");
			offsetY = 0;
		}
		CCPoint point = CardUtil::getCardPosition(pCard,HAS_CARD,it->first,offsetX,offsetY);
		CCNode* pNode = m_background->getChildByTag(pCard->getTag());
		if(pNode){
			pCard->runAction(CCMoveTo::create(0.2f,point));
		}
		else{
			pCard->setPosition(point);
			m_background->addChild(pCard,kZOrderCard,pCard->getTag());
		}
		++it;
	}

	CCLog("showCard fieldCard");
	//フィールド表示
	while(fieldIt != fieldCard.end()){
		CardClass *pCard = fieldIt->second;
		CCPoint point = CardUtil::getCardPosition(pCard,FIELD_CARD,pCard->getId(),offsetX/2,0);
		CCNode* pNode = m_background->getChildByTag(pCard->getTag());
		if(pNode){
			pCard->runAction(CCMoveTo::create(0.2f,point));
		}
		else{
			pCard->setPosition(point);
			m_background->addChild(pCard,kZOrderCard,pCard->getTag());
		}
		++fieldIt;
	}
}

void GameScene::showPass(){

	CCPoint point;
	float passWidth = 0;
	float passHeight = 0;
	m_pass = CCSprite::create(PASS_IMAGE);

	passWidth = m_pass->getContentSize().width;
	passHeight = m_pass->getContentSize().height;

	point = CCPoint( passWidth*2 ,passHeight * 2);
	m_pass->setPosition(point);
	m_background->addChild(m_pass,kZOrderPass,kTagPass);
}

void GameScene::showNpcCard(){

	CCLog("showNpcCard");
	float offsetX = m_background->getContentSize().width * 0.3;
	float offsetY = m_background->getContentSize().height * 0.7;

	map<int, CardClass*> hasCard = pNpc->getHasCard();
	map<int, CardClass*>::iterator it = hasCard.begin();

	map<int, CardClass*> fieldCard = pNpc->getFieldCard();
	map<int, CardClass*>::iterator fieldIt = fieldCard.begin();

	//手持ちカードの表示
		CCLog("showCard NpcHasCard");
		while( it != hasCard.end() )
		{
			CardClass *pCard = it->second;
			CCLog("npcHasCard loop tag:%d",pCard->getTag());
			offsetY = 300;
			CCPoint point = CardUtil::getCardPosition(pCard,HAS_CARD,it->first,offsetX,offsetY);
			CCLog("getChildByTag tag:%d",pCard->getTag());
			CCNode* pNode = m_background->getChildByTag(pCard->getTag());
			if(pNode){
				pCard->runAction(CCMoveTo::create(0.2f,point));
			}
			else{
				pCard->setPosition(point);
				m_background->addChild(pCard,kZOrderCard,pCard->getTag());
			}
			++it;
		}


	CCLog("showCard fieldCard");
	//フィールド表示
	while(fieldIt != fieldCard.end()){
		CardClass *pCard = fieldIt->second;
		CCPoint point = CardUtil::getCardPosition(pCard,FIELD_CARD,pCard->getId(),offsetX/2,0);
		CCNode* pNode = m_background->getChildByTag(pCard->getTag());
		if(pNode){
			pCard->runAction(CCMoveTo::create(0.2f,point));
		}
		else{
			pCard->setPosition(point);
			m_background->addChild(pCard,kZOrderCard,pCard->getTag());
		}
		++fieldIt;
	}
}

bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){
	return true;
}

void GameScene::ccTouchEnded(CCTouch* pTouch , CCEvent* pEvent){

	switch(phase){
	case ACTION_PHASE:
		actionTauch(pTouch,pEvent);
		break;

	}

}


void GameScene::actionTauch(CCTouch* pTouch , CCEvent* pEvent){

	//カードあたり判定
	map<int, CardClass*> hasCard = pPlayer->getHasCard();
	map<int, CardClass*>::iterator it = hasCard.begin();
	CCPoint touchPoint = m_background->convertTouchToNodeSpace(pTouch);
	CCLog("actionTauch");
	while( it != hasCard.end() )
	{
		CardClass* pCard = it->second;
		int currentTag = pCard->getTag();
		CCNode* node = m_background->getChildByTag(currentTag);
		if(node && node->boundingBox().containsPoint(touchPoint)){
			if(pPlayer->UseCard(it->first)){
				nextTurn();
				phase = DRAW_PHASE;
			}
		}
		it++;
	}

	//パスボタンあたり判定
	CCNode* passNode = m_background->getChildByTag(kTagPass);
	if(passNode && passNode->boundingBox().containsPoint(touchPoint)){
		nextTurn();
		phase = DRAW_PHASE;
		CCLog("パス");
	}
}











