#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pMember1NameLabel = new Label("Patrick Crowley", "Consolas", 70, blue, glm::vec2(400.0f, 40.0f));
	m_pMember1NameLabel->setParent(this);
	addChild(m_pMember1NameLabel);

	m_pMember1NumberLabel = new Label("101305076", "Consolas", 40, blue, glm::vec2(400.0f, 85.0f));
	m_pMember1NumberLabel->setParent(this);
	addChild(m_pMember1NumberLabel);

	m_pMember2NameLabel = new Label("Pedro Augusto", "Consolas", 70, blue, glm::vec2(400.0f, 135.0f));
	m_pMember2NameLabel->setParent(this);
	addChild(m_pMember2NameLabel);

	m_pMember2NumberLabel = new Label("101300796", "Consolas", 40, blue, glm::vec2(400.0f, 185.0f));
	m_pMember2NumberLabel->setParent(this);
	addChild(m_pMember2NumberLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 50, blue, glm::vec2(400.0f, 250.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();
}

