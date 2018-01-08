#pragma once
#include "Object.h"

class Background : public Object
{
public:
	Background();
	~Background();

protected:
	virtual void initShader() override;
	virtual void initVAO() override;

public:
	virtual void render() override;
};

