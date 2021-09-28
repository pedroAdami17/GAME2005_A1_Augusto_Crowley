#pragma once
#ifndef __WOOKIE__
#define __WOOKIE__
#include "DisplayObject.h"

class Wookie final : public DisplayObject
{
public:
	// constructors
	Wookie();

	// destructor
	~Wookie();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
private:

};

#endif /* defined (__TROOPER__) */