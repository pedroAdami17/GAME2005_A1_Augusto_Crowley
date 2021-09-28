#pragma once
#ifndef __TROOPER__
#define __TROOPER__
#include "DisplayObject.h"

class Trooper final : public DisplayObject
{
public:
	// constructors
	Trooper();

	// destructor
	~Trooper();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
private:

};

#endif /* defined (__TROOPER__) */