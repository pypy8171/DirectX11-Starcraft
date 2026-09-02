#pragma once

#include "YongEngine/Script.h"

class CTileScript
	: public CScript
{

public:
	virtual int update();


public:
	CLONE(CTileScript);
public:
	CTileScript();
	~CTileScript();
};

