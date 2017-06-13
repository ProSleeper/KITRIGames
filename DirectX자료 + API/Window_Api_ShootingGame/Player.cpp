#include "GameCommon.h"

Player::Player()
{
	m_bSpaceKey = false;
	m_pEnemy = NULL;
	strcpy_s(m_szLayer, "Player");
}

Player::~Player()
{
}

bool Player::Update()
{
	if (GETKEY(VK_RIGHT))
	{
		if (GETKEY(VK_UP) || GETKEY(VK_DOWN))
			m_fPosX += m_fSpeed / ROOT2;
		else
			m_fPosX += m_fSpeed;
	}

	if (GETKEY(VK_LEFT))
	{
		if (GETKEY(VK_UP) || GETKEY(VK_DOWN))
			m_fPosX -= m_fSpeed / ROOT2;
		else
			m_fPosX -= m_fSpeed;
	}

	if (GETKEY(VK_UP))
	{
		if (GETKEY(VK_LEFT) || GETKEY(VK_RIGHT))
			m_fPosY -= m_fSpeed / ROOT2;
		else
			m_fPosY -= m_fSpeed;
	}

	if (GETKEY(VK_DOWN))
	{
		if (GETKEY(VK_LEFT) || GETKEY(VK_RIGHT))
			m_fPosY += m_fSpeed / ROOT2;
		else
			m_fPosY += m_fSpeed;
	}

	if (m_fPosX < 0)
		m_fPosX = 0;
	if (m_fPosX + m_iWidth > WINMGR->GetWidth())
		m_fPosX = WINMGR->GetWidth() - m_iWidth;

	if (m_fPosY < 0)
		m_fPosY = 0;
	if (m_fPosY + m_iHeight > WINMGR->GetHeight())
		m_fPosY = WINMGR->GetHeight() - m_iHeight;


	GETKEYDOWN(VK_SPACE, m_bSpaceKey, FireBullet)

	return true;
}

void Player::Render(HDC _backDC)
{
	BaseImageObject::Render(_backDC);
}

void Player::FireBullet()
{
	// 동적할당
	Bullet* _pBullet = new Bullet;

	// Init
	_pBullet->Init(0, 0, 16, 22, IT_BULLET);

	 //ResetBullet
	_pBullet->ResetBullet(
			m_fPosX + m_iWidth / 2 
			- _pBullet->GetWidth(),
			m_fPosY + _pBullet->GetHeight());

	// PushBack
	_pBullet->SetTag(TAG_PLAYER_BULLET);
	_pBullet->SetLayer("Player_Bullet");
	_pBullet->SetSpeed(5.0f);

	GAMEMGR->CreateObject(_pBullet,true);
}

void Player::OnCollisionEnter(BaseTransform* _pCollObj)
{
	OnHit();
	GAMEMGR->ChangeScene(ST_ENDING);
}