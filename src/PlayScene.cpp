#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawLineF(Renderer::Instance().getRenderer(), wookieX, wookieY, wookieX + vx, wookieY + vy);

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	//Set up delta time
	float dt = 0.05f;

	//Set up variables
	wookieX = m_pWookie->getTransform()->position.x;
	wookieY = m_pWookie->getTransform()->position.y;
	trooperX = m_pTrooper->getTransform()->position.x;
	trooperY = m_pTrooper->getTransform()->position.y;
	detonatorStartX = m_pWookie->getTransform()->position.x;
	detonatorStartY = m_pWookie->getTransform()->position.y;

	//Physics done here
	vx = cosf(-throwArc * M_PI / 180) * detonatorSpeed;
	vy = sinf(-throwArc * M_PI / 180) * detonatorSpeed;

	if (launch)
	{
		gameTime += dt;
		detonatorX = detonatorStartX + detonatorSpeed * cosf(-throwArc * M_PI / 180) * gameTime;
		detonatorY = detonatorStartY + detonatorSpeed * sinf(-throwArc * M_PI / 180) * gameTime + (0.5 * gravity * powf(gameTime, 2));
		m_pDetonator->getTransform()->position = glm::vec2(detonatorX, detonatorY + (gravity * dt));
	}
	else
	{
		gameTime = 0.0f;
		m_pWookie->getTransform()->position = glm::vec2(wookieX, wookieY);
		m_pTrooper->getTransform()->position = glm::vec2(trooperX, trooperY);
		m_pDetonator->getTransform()->position = glm::vec2(detonatorStartX, detonatorStartY);
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	//Set up sprites here
	m_pBackground = new Background();
	m_pBackground->getTransform()->position = glm::vec2(300, 300);
	addChild(m_pBackground);

	m_pWookie = new Wookie();
	m_pWookie->getTransform()->position = glm::vec2(50, 550);
	addChild(m_pWookie);

	m_pTrooper = new Trooper();
	m_pTrooper->getTransform()->position = glm::vec2(trooperDistance, 550);
	addChild(m_pTrooper);

	m_pDetonator = new Detonator();
	addChild(m_pDetonator);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance().changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		//TheGame::Instance().changeSceneState(END_SCENE);
		launch = true;
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	addChild(m_pInstructionsLabel);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Change the variables here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	if(ImGui::Button("Launch"))
	{
		
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();
}
