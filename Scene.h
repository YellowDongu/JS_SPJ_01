#pragma once

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void init() abstract;
	virtual void render(HDC _hdc) abstract;
	virtual int update() abstract;
	virtual void release() abstract;

protected:
};
