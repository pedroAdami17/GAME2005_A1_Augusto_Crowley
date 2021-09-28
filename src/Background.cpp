#include "Background.h"
#include "TextureManager.h"

Background::Background()
{
	TextureManager::Instance().load("../Assets/textures/Background.jpg", "Background");

	auto size = TextureManager::Instance().getTextureSize("Background");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(BACKGROUND);
	getRigidBody()->isColliding = false;
}

Background::~Background()
= default;

void Background::draw()
{
	TextureManager::Instance().draw("Background", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Background::update()
{
}

void Background::clean()
{
}