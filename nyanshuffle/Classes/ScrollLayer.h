//
//  CCScrollLayer.h
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010 All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
//  Changed for cocos2d-x 2.1.1 by Tomoaki Shimizu on 02/16/2013
//

#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class ScrollLayer : public Layer
{
protected:
	// Holds the current height and width of the screen
	int scrollHeight;
	int scrollWidth;
	
	// Holds the height and width of the screen when the class was inited
	int startHeight;
	int startWidth;
	
	// Holds the current page being displayed
	int currentScreen;
	
	// A count of the total screens available
	int totalScreens;
	
	// The initial point the user starts their swipe
	int startSwipe;	
    
	void moveToPage(int page);
	void moveToNextPage();
	void moveToPreviousPage();
	virtual void onExit();
	virtual bool TouchBegan(Touch *touch, Event *withEvent);
	virtual void TouchMoved(Touch *touch, Event *withEvent);
	virtual void TouchEnded(Touch *touch, Event *withEvent);
	EventListenerTouch *m_listener;
public:
	static ScrollLayer* createWithLayers(Array *layers,int widthOffset);
	bool initWithLayers(Array *layers,int widthOffset);
	NODE_FUNC(ScrollLayer);
};
