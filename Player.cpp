#include "framework.h"
#include "Player.h"
#include "RenderManager.h"
#include "animationContainer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "CameraManager.h"

Player::Player() : currentState("Stand"), inven(nullptr)
{
}

Player::~Player()
{
	release();
}

void Player::init()
{
	worldPos = Vector2{ 600.0f, 600.0f };
	//sizeInfo = Vector2{ 32.0f, 48.0f };
	sizeInfo = Vector2{ 25.0f, 48.0f };
	imgInit();
	speed = 10.0f;
	maxSpeed = 1000.0f;
	onGround = true;

	hp = 73;
	maxHp = 100;
	mp = 20;
	maxMp = 20;

	inven = new PlayerInventory();
	inven->init();
}

void Player::update()
{
	keyInput();
	updateAni();
	aniCtrl->update();

	if (moveVec == Vector2::zero()) return;
	worldPos += moveVec * Time->deltaTime();
}

void Player::release()
{
	if (!aniCtrl) return;
	aniCtrl->release();
	delete aniCtrl;
	aniCtrl = nullptr;
	inven->release();
	delete inven;
}

void Player::CollisionWithEntity(Entity* _col)
{
}

void Player::keyInput()
{
	moveVec.x += (float)vhInput->horizontal() * speed;


	if (onGround)
	{
		moveVec.y = 0;
		if (Input->getButtonDown(KeyType::Space))
		{
			moveVec.y = 420.0f;
			onGround = false;
		}
	}
	else
	{
		if (Time->deltaTime() < 0.5f)
		{
			moveVec.y -= 1000.0f * Time->deltaTime();
		}
	}


	if (vhInput->horizontal() == 0)
	{
		if (moveVec != Vector2::zero())
			moveVec -= Vector2{ moveVec.normalize().x, 0.0f } * 1000.0f * Time->deltaTime();
		if (abs(moveVec.x) <= 10.0f) moveVec.x = 0;

	}

	//vertical();
	if (abs(moveVec.x) > maxSpeed / 3)
		moveVec.x /= abs(moveVec.x) / (maxSpeed / 3);
	if (abs(moveVec.y) > maxSpeed)
		moveVec.y /= abs(moveVec.y) / maxSpeed;


}

void Player::vertical()
{
	if (onGround)
	{
		if (Input->getButtonDown(KeyType::Space))
		{
			moveVec.y = 200.0f;
			onGround = false;
		}
	}
}

void Player::imgInit()
{
	aniCtrl = new AnimationController;
	animationContainer* newAni = new animationContainer();
	newAni->setRawImg(rendering->findImage("Entity_Player", "headR", 0, 0)[0]);
	newAni->setBlank({ 2,2 });
	newAni->init({
		{"standR",{ false, {{0,1}}} }, //10
		{"jumpR", { false, {{0,5}}} },
		{"walkR", { false, {{0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11},
		{0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}}}} },
		"standR" , & worldPos, {40, 54}, {0,0});
	aniCtrl->addAnimation("head", newAni);
	aniCtrl->changeAnimationContianer("00.head", "head");

	newAni = new animationContainer();
	newAni->setRawImg(rendering->findImage("Entity_Player", "eye1R", 0, 0)[0]);
	newAni->setBlank({ 2,2 });
	newAni->init(
		{
		{"standR",{ false, {{0,1}} }}, //10
		{"jumpR", { false, {{0,5}} }},
		{"walkR", { false, {{0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11},
		{0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}}}}
		},
		"standR" , & worldPos, {40, 54}, {0,0});
	aniCtrl->addAnimation("eye", newAni);
	aniCtrl->changeAnimationContianer("06.eye", "eye");

	newAni = new animationContainer();
	newAni->setRawImg(rendering->findImage("Entity_Player", "armsR", 0, 0)[0]);
	newAni->setBlank({ 0,2 });
	newAni->init(
		{
		{"standR",{ false, {{2,2}} }},
		{"jumpR", { false, {{2,3}} }},
		{"walkR", { false, {{3,3}, {5,3}, {6,3}, {6,3}, {5,3}, {3,3}, {4,3}} }},
		{"swingR",{ true,  {{3,2}, {4,2}, {5,2}, {6,2}} }},
		{"useTopR",{ true, {{4,2}} }},
		{"useMiddleR",{ true,{{5,2}} }},
		{"useBottomR",{ true,{{6,2}} }}
		},
		"standR" , & worldPos, {40, 54}, {0,0});
	aniCtrl->addAnimation("armRR", newAni);
	aniCtrl->changeAnimationContianer("01.armR", "armRR");

	newAni = new animationContainer();
	newAni->setRawImg(rendering->findImage("Entity_Player", "armsR", 0, 0)[0]);
	newAni->setBlank({ 0,2 });
	newAni->init(
		{
		{"standR",{ false, {{2,0}} }},
		{"jumpR", { false, {{3,0}} }},
		{"walkR", { false, {{3,1}, {5,1}, {6,1}, {6,1}, {5,1}, {3,1}, {4,1}} }},
		{"swingR",{ true,  {{3,0}, {4,0}, {5,0}, {6,0}} }},
		{"useTopR",{ true, {{4,0}} }},
		{"useMiddleR",{ true,{{5,0}} }},
		{"useBottomR",{ true,{{6,0}} }}
		},
		"standR" , & worldPos, {40, 54}, {0,0});
	aniCtrl->addAnimation("armFR", newAni);
	aniCtrl->changeAnimationContianer("05.armF", "armFR");

	newAni = new animationContainer();
	newAni->setRawImg(rendering->findImage("Entity_Player", "torsoR", 0, 0)[0]);
	newAni->setBlank({ 2,2 });
	newAni->init(
		{
		{ "jumpR", { false, {{ 0,0 }} }},
		{ "standR",{ false, {{ 0,0 }} }},
		{ "walkR", { false, {{ 0,0 }, { 1,0 }} }}
		},
		"standR" , & worldPos, {40, 54}, {0,0});
	aniCtrl->addAnimation("torsoR", newAni);
	aniCtrl->changeAnimationContianer("02.torso", "torsoR");

	newAni = new animationContainer();
	newAni->setRawImg(rendering->findImage("Entity_Player", "clothesR", 0, 0)[0]);
	newAni->setBlank({ 2,2 });
	newAni->init(
		{
		{ "standR",{ false, {{ 0,0 }} }},
		{ "jumpR", { false, {{ 0,0 }} }},
		{ "walkR", { false, {{ 0,0 }, { 1,0 }} }}
		},
		"standR" , & worldPos, {40, 54}, {0,0});
	aniCtrl->addAnimation("clothesR", newAni);
	aniCtrl->changeAnimationContianer("03.clothes", "clothesR");

	newAni = new animationContainer();
	newAni->setRawImg(rendering->findImage("Entity_Player", "legR", 0, 0)[0]);
	newAni->setBlank({ 2,2 });
	newAni->init(
		{
		{"standR",{ false, {{0,1}} }},//10
		{"jumpR", { false, {{0,5}} }},
		{"walkR", { false, {{0,12}, {0,13}, {0,14}, {0,15}, {0,16}, {0,17}, {0,18}, {0,19}, {0,6}, {0,7}, {0,8}, {0,9} ,{0,10}, {0,11}} }}
		},
		"standR" , & worldPos, {40, 54}, {0,0});
	aniCtrl->addAnimation("legR", newAni);
	aniCtrl->changeAnimationContianer("04.leg", "legR");


}

void Player::updateAni()
{
	if (moveVec == Vector2::zero())
	{
		if (currentState == "Stand") return;
		aniCtrl->changeAnimation("00.head", "standR");
		aniCtrl->changeAnimation("01.armR", "standR");
		aniCtrl->changeAnimation("02.torso", "standR");
		aniCtrl->changeAnimation("03.clothes", "standR");
		aniCtrl->changeAnimation("04.leg", "standR");
		aniCtrl->changeAnimation("05.armF", "standR");
		aniCtrl->changeAnimation("06.eye", "standR");
		currentState = "Stand";
		return;
	}

	if (moveVec.y != 0)
	{
		if (currentState == "Jump") return;
		aniCtrl->changeAnimation("00.head", "jumpR");
		aniCtrl->changeAnimation("01.armR", "jumpR");
		aniCtrl->changeAnimation("02.torso", "jumpR");
		aniCtrl->changeAnimation("03.clothes", "jumpR");
		aniCtrl->changeAnimation("04.leg", "jumpR");
		aniCtrl->changeAnimation("05.armF", "jumpR");
		aniCtrl->changeAnimation("06.eye", "jumpR");
		currentState = "Jump";
		return;
	}

	if (moveVec.x > 0)
	{
		aniCtrl->reverseImg(false);
		if (currentState == "WalkR") return;
		aniCtrl->changeAnimation("00.head", "walkR");
		aniCtrl->changeAnimation("01.armR", "walkR");
		aniCtrl->changeAnimation("02.torso", "walkR");
		aniCtrl->changeAnimation("03.clothes", "walkR");
		aniCtrl->changeAnimation("04.leg", "walkR");
		aniCtrl->changeAnimation("05.armF", "walkR");
		aniCtrl->changeAnimation("06.eye", "walkR");
		currentState = "WalkR";
		return;
	}
	else if (moveVec.x < 0)
	{
		aniCtrl->reverseImg(true);
		if (currentState == "WalkL") return;
		aniCtrl->changeAnimation("00.head", "walkR");
		aniCtrl->changeAnimation("01.armR", "walkR");
		aniCtrl->changeAnimation("02.torso", "walkR");
		aniCtrl->changeAnimation("03.clothes", "walkR");
		aniCtrl->changeAnimation("04.leg", "walkR");
		aniCtrl->changeAnimation("05.armF", "walkR");
		aniCtrl->changeAnimation("06.eye", "walkR");
		currentState = "WalkL";
		return;
	}

	if (currentSubState != aniCtrl->checkCurrentState("01.armR"))
	{
		currentSubState = aniCtrl->checkCurrentState("01.armR");
	}
}

void Player::useItem()
{
	std::string currentState = aniCtrl->checkCurrentState("01.armR");
	if (currentState == "swingR" || currentState == "useTopR" || currentState == "useMiddleR" || currentState == "useBottomR") return;
	Item* item;
	if (inven->pickedItem()->item())
	{
		Vector2 mousePos = cam->calculateWorldPosition({ (float)Input->getMousePos().x, (float)Input->getMousePos().y });
		item = inven->pickedItem()->item();
		UsingState state = item->usingState();
		float angle = Vector2::angle(mousePos - worldPos);
		switch (state)
		{
		case UsingState::Swing:
			aniCtrl->changeAnimation("01.armR", "swingR");
			aniCtrl->changeAnimation("05.armF", "swingR");
			break;
		case UsingState::Use:
			aniCtrl->changeAnimation("01.armR", "useTopR");
			aniCtrl->changeAnimation("05.armF", "useTopR");
			break;
		case UsingState::Directinal:
			if (angle >= 45.0f && angle < 135.0f)
			{
				aniCtrl->changeAnimation("01.armR", "useTopR");
				aniCtrl->changeAnimation("05.armF", "useTopR");
			}
			else if ((angle < 45.0f && angle >= 330.0f) || (angle >= 135.0f && angle < 225.0f))
			{
				aniCtrl->changeAnimation("01.armR", "useMiddleR");
				aniCtrl->changeAnimation("05.armF", "useMiddleR");
			}
			else if (angle >= 225.0f && angle < 330.0f)
			{
				aniCtrl->changeAnimation("01.armR", "useBottomR");
				aniCtrl->changeAnimation("05.armF", "useBottomR");
			}
			break;
		default:
			break;
		}
		inven->pickedItem()->useItem();
	}
	else if (inven->selectedAtHotBar()->item())
	{
		Vector2 mousePos = cam->calculateWorldPosition({ (float)Input->getMousePos().x, (float)Input->getMousePos().y });
		item = inven->selectedAtHotBar()->item();
		UsingState state = item->usingState();
		float angle = Vector2::angle(mousePos - worldPos);
		switch (state)
		{
		case UsingState::Swing:
			aniCtrl->changeAnimation("01.armR", "swingR");
			aniCtrl->changeAnimation("05.armF", "swingR");
			aniCtrl->changeAnimationSlpeed("01.armR", 3.0f);
			aniCtrl->changeAnimationSlpeed("05.armF", 3.0f);
			break;
		case UsingState::Use:
			aniCtrl->changeAnimation("01.armR", "useTopR");
			aniCtrl->changeAnimation("05.armF", "useTopR");
			aniCtrl->changeAnimationSlpeed("01.armR", 3.0f);
			aniCtrl->changeAnimationSlpeed("05.armF", 3.0f);
			break;
		case UsingState::Directinal:
			if (angle >= 45.0f && angle < 135.0f)
			{
				aniCtrl->changeAnimation("01.armR", "useTopR");
				aniCtrl->changeAnimation("05.armF", "useTopR");
				aniCtrl->changeAnimationSlpeed("01.armR", 3.0f);
				aniCtrl->changeAnimationSlpeed("05.armF", 3.0f);
			}
			else if ((angle < 45.0f && angle >= 330.0f) || (angle >= 135.0f && angle < 225.0f))
			{
				aniCtrl->changeAnimation("01.armR", "useMiddleR");
				aniCtrl->changeAnimation("05.armF", "useMiddleR");
				aniCtrl->changeAnimationSlpeed("01.armR", 3.0f);
				aniCtrl->changeAnimationSlpeed("05.armF", 3.0f);
			}
			else if (angle >= 225.0f && angle < 330.0f)
			{
				aniCtrl->changeAnimation("01.armR", "useBottomR");
				aniCtrl->changeAnimation("05.armF", "useBottomR");
				aniCtrl->changeAnimationSlpeed("01.armR", 3.0f);
				aniCtrl->changeAnimationSlpeed("05.armF", 3.0f);
			}
			break;
		default:
			break;
		}
		inven->selectedAtHotBar()->useItem();
	}
}
