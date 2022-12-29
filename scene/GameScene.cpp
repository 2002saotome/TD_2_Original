#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	delete title_;
	delete GameScene_;
	delete GamePlay_;
	delete GameCrear_;
	delete GameOver_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//テクスチャを入れ込む
	textureHandle_[0] = TextureManager::Load("Title.png");
	textureHandle_[1] = TextureManager::Load("GameScene.png");
	textureHandle_[2] = TextureManager::Load("GamePlay.png");
	textureHandle_[3] = TextureManager::Load("GameCrear.png");
	textureHandle_[4] = TextureManager::Load("GameOver.png");

	//スプライトを生成
	title_ = Sprite::Create(textureHandle_[0], { 0,0 });
	GameScene_ = Sprite::Create(textureHandle_[1], { 0,0 });
	GamePlay_ = Sprite::Create(textureHandle_[2], { 0,0 });
	GameCrear_ = Sprite::Create(textureHandle_[3], { 0,0 });
	GameOver_ = Sprite::Create(textureHandle_[4], { 0,0 });
}

void GameScene::Update() 
{
	switch (scene_)
	{
		//タイトル
	case 0:
#pragma region TITLE
		//初期化
		Timer = 250;
		if (input_->TriggerKey(DIK_RIGHT))
		{
			scene_ = 1;
		}
		break;

		//ゲーム説明
	case 1:
#pragma region GAMESCENE
		if (input_->TriggerKey(DIK_RIGHT))
		{
			scene_ = 2;
		}

		//ゲームプレイ
	case 2:
#pragma region GAMEPLAY
		if (scene_ == 2)
		{
			Timer--;
		}
		if (Timer < 0)
		{
			scene_ = 4;
		}

		//ゲームクリア
	case 3:
#pragma region GAMECREAR
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = 0;
		}

		//ゲームオーバー
	case 4:
#pragma region GAMEOVER
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = 0;
		}
	}

	DebugText::GetInstance()->SetPos(1000,0);
	DebugText::GetInstance()->Printf("scene_:%d",scene_);

	DebugText::GetInstance()->SetPos(1000, 30);
	DebugText::GetInstance()->Printf("Timer:%d", Timer);

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//表示
	switch (scene_)
	{
	case 0:
		title_->Draw();
		break;
	case 1:
		GameScene_->Draw();
		break;
	case 2:
		GamePlay_->Draw();
		break;
	case 3:
		GameCrear_->Draw();
		break;
	case 4:
		GameOver_->Draw();
		break;

	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
