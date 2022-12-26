#include"Sprite.h"

#pragma once
class Fade
{
private:
	const int FADE_TIME = 60;
	Sprite* sprite_ = nullptr;
	float alpha = 0;
	uint32_t* stage_;
	uint32_t texture_ = 0;


public:
	void Initialize();
	void FadeUpdate();
	void Draw();
	void FadeScene();
	void ChangeScene();
};