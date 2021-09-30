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

float PlayScene::meters_to_Pixels(float meters, float scaleValue)
{
	return meters / scaleValue;
}

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
		m_pDetonator->getTransform()->position = glm::vec2(detonatorX, detonatorY + (gravity * gameTime));
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

	//set variables
	wookieX = m_pWookie->getTransform()->position.x;
	wookieY = m_pWookie->getTransform()->position.y;
	trooperX = m_pTrooper->getTransform()->position.x;
	trooperY = m_pTrooper->getTransform()->position.y;
	detonatorSpeed = meters_to_Pixels(detonatorSpeed, mtpScale);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 200.0f);

	addChild(m_pInstructionsLabel);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	

	ImGui::Begin("Change the variables here.", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);
	ImGui::Text("1 pixel is equal to 2 meters");
	ImGui::SliderFloat("wookieX", &wookieX, 0.0f, 775.0f, "%.3f");
	ImGui::SliderFloat("wookieY", &wookieY, 0.0f, 550.0f, "%.3f");
	ImGui::SliderFloat("trooperX", &trooperX, 0.0f, 775.0f, "%.3f");
	ImGui::SliderFloat("trooperY", &trooperY, 0.0f, 550.0f, "%.3f");
	ImGui::SliderFloat("detonatorSpeed", &detonatorSpeed, 1.0f, 100.0f, "%.3f");
	ImGui::SliderFloat("throwArc", &throwArc, 1.0f, 90.0f, "%.3f");
	ImGui::SliderFloat("gravity", &gravity, -1.0f, 1.0f, "%.3f");
	
	ImGui::Separator();

	if(ImGui::Button("Launch"))
	{
		launch = true;
	}

	if (ImGui::Button("Reset"))
	{
		launch = false;
	}

	

	
	
	ImGui::End();
}
