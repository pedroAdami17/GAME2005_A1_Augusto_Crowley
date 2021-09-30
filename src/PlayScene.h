#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Label.h"
#include "Trooper.h"
#include "Detonator.h"
#include "Wookie.h"
#include "Background.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	float meters_to_Pixels(float meters, float scaleValue);

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Detonator* m_pDetonator;
	Wookie* m_pWookie;
	Trooper* m_pTrooper;
	Background* m_pBackground;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;

	//Variables
	float mtpScale = 3.0f;
	float trooperDistance = 535.0f;
	float detonatorSpeed = 95.0f; 
	float detonatorMass = 2.2f;
	float wookieX;
	float wookieY;
	float detonatorX;
	float detonatorY;
	float detonatorStartX;
	float detonatorStartY;
	float trooperX;
	float trooperY;
	float vx;
	float vy;
	float gameTime;
	float throwArc = 15.90f;
	float gravity = 1.0f;
	bool launch = false;

	

};

#endif /* defined (__PLAY_SCENE__) */