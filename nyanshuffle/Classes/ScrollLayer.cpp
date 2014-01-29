//
//  CCScrollLayer.cpp
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010. All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
//  Changed for cocos2d-x 2.1.1 by Tomoaki Shimizu on 02/16/2013
//

#include "ScrollLayer.h"

ScrollLayer* ScrollLayer::createWithLayers(Array *layers, int widthOffset)
{	
	ScrollLayer *pRet = new ScrollLayer();
	if (pRet && pRet->initWithLayers(layers, widthOffset))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool ScrollLayer::initWithLayers(Array *layers, int widthOffset)
{	
	if (Layer::init())
	{		
		// Make sure the layer accepts touches
//旧バージョン
//		Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
//新バージョン詳細な書き方
        auto m_listener = EventListenerTouchOneByOne::create();
        m_listener->onTouchBegan = CC_CALLBACK_2(ScrollLayer::onTouchBegan, this);
        m_listener->onTouchMoved = CC_CALLBACK_2(ScrollLayer::onTouchMoved, this);
        m_listener->onTouchEnded = CC_CALLBACK_2(ScrollLayer::onTouchEnded, this);
        m_listener->onTouchCancelled = CC_CALLBACK_2(ScrollLayer::onTouchCancelled, this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
//        setTouchEnabled(true);
//        setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
		
		// Set up the starting variables
		if(!widthOffset)
		{
			widthOffset = 0;
		}	
		currentScreen = 1;
		
		// offset added to show preview of next/previous screens
		scrollWidth  = (int)Director::sharedDirector()->getWinSize().width - widthOffset;
		scrollHeight = (int)Director::sharedDirector()->getWinSize().height;
		startWidth = scrollWidth;
		startHeight = scrollHeight;
		
		// Loop through the array and add the screens
		unsigned int i;
		for (i=0; i<layers->count(); i++)
		{
			Layer* l = (Layer*)(layers->objectAtIndex(i));
			l->setAnchorPoint(ccp(0,0));
			l->setPosition(ccp((i*scrollWidth),0));
			addChild(l);			
		}
		
		// Setup a count of the available screens
		totalScreens = layers->count();
		return true;	
	}
	else
	{
		return false;
	}	
}

void ScrollLayer::moveToPage(int page)
{	
//	EaseBounce* changePage = EaseBounce::create(MoveTo::create(0.3f, ccp(-((page-1)*scrollWidth),0)));
//	this->runAction(changePage);
	currentScreen = page;	
}

void ScrollLayer::moveToNextPage()
{	
//	EaseBounce* changePage = EaseBounce::create(MoveTo::create(0.3f, ccp(-(((currentScreen+1)-1)*scrollWidth),0)));
//
//	this->runAction(changePage);
//	currentScreen = currentScreen+1;
}

void ScrollLayer::moveToPreviousPage()
{	
//	EaseBounce* changePage =EaseBounce::create(MoveTo::create(0.3f, ccp(-(((currentScreen-1)-1)*scrollWidth),0)));
//	this->runAction(changePage);
//	currentScreen = currentScreen-1;
}

void ScrollLayer::onExit()
{
//	Director::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	Layer::onExit();
}

bool ScrollLayer::TouchBegan(Touch *touch, Event *withEvent)
{
	Point touchPoint = touch->getLocationInView();
	touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	
	startSwipe = (int)touchPoint.x;
	return true;
}

void ScrollLayer::TouchMoved(Touch *touch, Event *withEvent)
{	
	Point touchPoint = touch->getLocationInView();
	touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	
	this->setPosition(ccp((-(currentScreen-1)*scrollWidth)+(touchPoint.x-startSwipe),0));
}

void ScrollLayer::TouchEnded(Touch *touch, Event *withEvent)
{
	
	Point touchPoint = touch->getLocationInView();
	touchPoint = Director::sharedDirector()->convertToGL(touchPoint);
	
	int newX = (int)touchPoint.x;
    
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
	}
	else
	{
		this->moveToPage(currentScreen);		
	}		
}
