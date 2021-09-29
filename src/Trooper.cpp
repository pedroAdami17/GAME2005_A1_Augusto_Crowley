#include "Trooper.h"


#include "SoundManager.h"
#include "TextureManager.h"

Trooper::Trooper()
{
	TextureManager::Instance().load("../Assets/textures/Stormtrooper.png", "Trooper");

	auto size = TextureManager::Instance().getTextureSize("Trooper");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(TROOPER);
	getRigidBody()->isColliding = false;
}

Trooper::~Trooper()
= default;

void Trooper::draw()
{
	TextureManager::Instance().draw("Trooper", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Trooper::update()
{
}

void Trooper::clean()
{
}