#include "Detonator.h"


#include "SoundManager.h"
#include "TextureManager.h"

Detonator::Detonator()
{
	TextureManager::Instance().load("../Assets/textures/Detonator.png", "detonator");

	auto size = TextureManager::Instance().getTextureSize("detonator");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(DETONATOR);
	getRigidBody()->isColliding = false;
}

Detonator::~Detonator()
= default;

void Detonator::draw()
{
	TextureManager::Instance().draw("detonator", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Detonator::update()
{
}

void Detonator::clean()
{
}
