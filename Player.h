#include"Sprite.h"

#pragma once
class Player
{
private:
	int Player = 1;
	int PlayerLife = 1;
	const float MOVE_SPD = 1.0f;
	const float ROT_SPD = 0.03f;
	const int MAX_LIFE = 3;
	int life_ = MAX_LIFE;

public:
	void PlayerUpdate();
	void Rotate();
	void Initialize();
	void SpriteDraw();
	void Draw();
	void Init();

};
