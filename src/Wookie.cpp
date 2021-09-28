#include "Wookie.h"


#include "SoundManager.h"
#include "TextureManager.h"

Wookie::Wookie()
{
	TextureManager::Instance().load("../Assets/textures/Wookie.png", "Wookie");

	auto size = TextureManager::Instance().getTextureSize("Wookie");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(WOOKIE);
	getRigidBody()->isColliding = false;
}

Wookie::~Wookie()
= default;

void Wookie::draw()
{
	TextureManager::Instance().draw("Wookie", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Wookie::update()
{
}

void Wookie::clean()
{
}