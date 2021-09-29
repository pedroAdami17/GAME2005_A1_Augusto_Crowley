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

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
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
	float trooperDistance = 485.0f; //Multiply it by pixels per meter scale later
	float detonatorSpeed = 95.0f; //Multuply it by pixels per meter scale later
	float detonatorMass = 2.2f; //This is in kiliograms so might have to change
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
	float throwArc = 50.0f; //Need to find the angle from the problem and store it here for now use a default value
	float gravity = 1.0f;
	bool launch = false;

	

};

#endif /* defined (__PLAY_SCENE__) */