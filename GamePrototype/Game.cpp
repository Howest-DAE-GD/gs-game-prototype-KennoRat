#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_ptrPlayer = new Player(Point2f{GetViewPort().width/2.f, GetViewPort().height/2.f}, 20.f);

	m_ptrPit = new SacrificialPit(Point2f{ GetViewPort().width / 2.f, GetViewPort().height / 2.f }, 100.f);

	for(int CivilianIndex{0}; CivilianIndex < 3; ++CivilianIndex)
	{
		float RandomXPosition{ float(rand() % int(GetViewPort().width)) };
		float RandomYPosition{ float(rand() % int(GetViewPort().height)) };

		m_ptrCivilian.push_back(new Civilian(Point2f(RandomXPosition, RandomYPosition), m_PEOPLE_WIDTH));
	}
	float RandomRangeX{ float(rand() % 200 - 100) };
	float RandomRangeY{ float(rand() % 200 - 100) };
	m_ptrCivilian.push_back(new Civilian(Point2f(m_ptrPlayer->GetPosition().x + RandomRangeX, m_ptrPlayer->GetPosition().y + RandomRangeY), m_PEOPLE_WIDTH));
	m_ptrText = new Text(Point2f{200.f, 600.f}, 900.f, 80.f, m_ShowText);

	m_ptrUpgrade1 = new Upgrades(Point2f{ GetViewPort().width / 2.f - 300.f, GetViewPort().height / 2.f - 50.f }, 100.f);
	m_ptrUpgrade2 = new Upgrades(Point2f{ GetViewPort().width / 2.f + 200.f, GetViewPort().height / 2.f - 50.f }, 100.f, m_ptrUpgrade1->GetUpgradeChoice());
}

void Game::Cleanup( )
{
	delete m_ptrPlayer;
	m_ptrPlayer = nullptr;
}

void Game::Update( float elapsedSec )
{
	if(m_ptrPlayer->GetIsDead() == false)
	{

		// Check keyboard state
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);

		const bool isUp{ bool(pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W]) };
		const bool isDown{ bool(pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_S]) };
		const bool isLeft{ bool(pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A]) };
		const bool isRight{ bool(pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D]) };

		m_ptrPlayer->Update(elapsedSec, isLeft, isUp, isRight, isDown);

		int CivilianNumber{ 0 };

		for (Civilian* Civilians : m_ptrCivilian)
		{
			if(Civilians->GetIsDead() == false)
			{
				if (IsPointInRect(m_ptrPlayer->GetPosition(), Civilians->GetHitbox()) && Civilians->GetIsCultMemeber() == false)
				{
					Civilians->SetIsCultMember(true);
					m_ptrPlayer->IncrementCultMembers();
				}
				Civilians->Update(elapsedSec, m_ptrPlayer->GetPosition(), m_ptrPlayer->m_Direction);

				if (m_ptrPlayer->GetSacrificeAvailable() && (m_ptrPlayer->GetCultMembers() >= 0))
				{
					//std::cout << "Player can Sacrifice" << std::endl;
					if (IsPointInRect(m_ptrPlayer->GetPosition(), m_ptrPit->GetSacrificeBox()) && m_ptrCivilian[Civilians->GetCultId()]->GetIsCultMemeber() && m_ptrCivilian[Civilians->GetCultId()]->GetIsDead() == false)
					{
						m_ptrPit->IncrementSacrificedCultMembers();
						m_ptrCivilian[Civilians->GetCultId()]->SetIsDead(true);
						std::cout << "CultId:" << Civilians->GetCultId() << std::endl;
						m_ptrPlayer->DecrementCultMembers();
						m_ptrPlayer->SetSacrificeAvailable(false);
						/*	delete Civilians;
							m_ptrCivilian.erase(m_ptrCivilian.begin() + CivilianNumber);*/
					}
				}

			}
			++CivilianNumber;
		}

		for (int Enemyindex = 0; Enemyindex < m_ptrEnemyCultMembers.size(); ++Enemyindex) {
			EnemyCultMember* enemy = m_ptrEnemyCultMembers[Enemyindex];
			enemy->Update(elapsedSec, m_ptrPlayer->GetPosition());

			if (IsPointInRect(m_ptrPlayer->GetPosition(), enemy->GetHitbox()) && !enemy->GetIsDead()) {
				m_ptrPlayer->SetIsDead(true);
			}

			if (enemy->GetIsDead()) {
				delete enemy;
				m_ptrEnemyCultMembers.erase(m_ptrEnemyCultMembers.begin() + Enemyindex);
				--Enemyindex; // Adjust index after erasing
			}
		}

		for (int i = 0; i < m_ptrBullets.size(); ++i) {
			Bullet* bullet = m_ptrBullets[i];
			bullet->Update(elapsedSec, m_ptrEnemyCultMembers);

			if (!bullet->GetIsActivated()) {
				delete bullet;
				m_ptrBullets.erase(m_ptrBullets.begin() + i);
				--i; // Adjust index after erasing
			}
		}

		m_SpawnTimerCounter += elapsedSec;
		SpawnCivilians();

		SpawnEnemyCultMembers(elapsedSec);

		m_ptrText->Update(elapsedSec);
	}

	BulletDelay(elapsedSec);

	ShootBullet();

	GetUpgrades(m_ptrPlayer->GetHitbox());
	if(m_ptrPit->GetSacrificedCultMembers() >= 90 && m_ptrText->GetGameEnd() == false)
	{
		m_ShowText = std::string("MUAHAHA, THE WORLD IS MINE!");
		m_ptrText->ChangeText(m_ShowText);
		m_ptrText->SetGameEnd(true);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	for (Civilian* Civilians : m_ptrCivilian)
	{
		Civilians->Draw();
	}

	for(EnemyCultMember* Enemies: m_ptrEnemyCultMembers)
	{
		Enemies->Draw();
	}

	for (Bullet* Bullets : m_ptrBullets)
	{
		Bullets->Draw();
	}

	m_ptrPit->Draw();

	m_ptrPlayer->Draw();

	m_ptrText->Draw();

	if(m_ChooseUpgrades)
	{
		m_ptrUpgrade1->Draw();
		m_ptrUpgrade2->Draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_MousePosition = Point2f{ float(e.x), float(e.y) };
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_IsShooting = true;
		break;
	case SDL_BUTTON_RIGHT:
		std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << " middle button " << std::endl;
		break;
	}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_IsShooting = false;
		break;
	case SDL_BUTTON_RIGHT:
		std::cout << " right button " << std::endl;
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << " middle button " << std::endl;
		break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::SpawnCivilians()
{
	if(m_SpawnTimerCounter >= m_SPAWN_TIMER_MAX)
	{
		float RandomXPosition{ float(rand() % int(GetViewPort().width)) };
		float RandomYPosition{ float(rand() % int(GetViewPort().height)) };

		m_ptrCivilian.push_back(new Civilian(Point2f(RandomXPosition, RandomYPosition), m_PEOPLE_WIDTH));
		m_SpawnTimerCounter -= m_SPAWN_TIMER_MAX;
	}
}

void Game::SpawnEnemyCultMembers(float elapsedSec)
{
	m_GameTimer += elapsedSec;
	if(m_GameTimer >= 10.f) m_EnemySpawnTimerCounter += elapsedSec;

	if (m_ptrPlayer->GetTotalCultMembers() >= 30) m_ENEMY_SPAWN_TIMER_MAX = rand() % 4 + 1;


	if(m_EnemySpawnTimerCounter >= m_ENEMY_SPAWN_TIMER_MAX)
	{
		if(m_GameTimer >= 150.f)
		{
			m_ptrEnemyCultMembers.push_back(new EnemyCultMember(Point2f(RandomEnemyPosition()), m_PEOPLE_WIDTH, true));
		}

		if (m_GameTimer >= 60.f)
		{
			m_ptrEnemyCultMembers.push_back(new EnemyCultMember(Point2f(RandomEnemyPosition()), m_PEOPLE_WIDTH, false, true));
		}
		else m_ptrEnemyCultMembers.push_back(new EnemyCultMember(Point2f(RandomEnemyPosition()), m_PEOPLE_WIDTH));

		m_EnemySpawnTimerCounter -= m_ENEMY_SPAWN_TIMER_MAX;
	}
}

void Game::BulletDelay(float elapsedSec)
{
	if(m_AbleToShoot == false)
	{
		m_AbleToShootCounter += elapsedSec;
		if(m_AbleToShootCounter >= m_Time_AbleToShoot)
		{
			m_AbleToShootCounter -= m_Time_AbleToShoot;
			m_AbleToShoot = true;
		}
	}
}

void Game::ShootBullet()
{
	if (m_AbleToShoot && m_IsShooting)
	{
		for(int IndexArms{}; IndexArms < m_PlayerArms; ++IndexArms)
		{
			float RandomXposition{};
			float RandomYPosition{};
			float ExtraDistance{};
			if(IndexArms >= 1)
			{
				if(IndexArms == 1) ExtraDistance = 35;
				else if (IndexArms == 2) ExtraDistance = -55;
				else if (IndexArms == 3) ExtraDistance = 65;
				RandomXposition = rand() % 100 + ExtraDistance;
				RandomYPosition = rand() % 100 + ExtraDistance;
			}
			m_ptrBullets.push_back(new Bullet(5.f, 10.f, GetViewPort(), Point2f{ m_MousePosition.x + RandomXposition, m_MousePosition.y + RandomYPosition}, m_ptrPlayer->GetPosition(), m_BulletDamage));
		}
		
		m_AbleToShoot = false;
	}
}

void Game::GetUpgrades(Rectf player)
{
	if(m_ptrPit->GetSacrificedCultMembers() >= (10 * m_UpgradeAmount + 5) && m_ChooseUpgrades == false)
	{
		m_ChooseUpgrades = true;
		m_ptrUpgrade1->NewUpgrades();
		m_ptrUpgrade2->NewUpgrades(m_ptrUpgrade1->GetUpgradeChoice());
	}

	if (m_ChooseUpgrades)
	{
		m_ptrUpgrade1->Update(player);
		m_ptrUpgrade2->Update(player);
		if (m_ptrUpgrade1->GetIsPicked() || m_ptrUpgrade2->GetIsPicked())
		{
			m_ChooseUpgrades = false;
			++m_UpgradeAmount;
			if(m_ptrUpgrade1->GetIsPicked())
			{
				if (m_ptrUpgrade1->GetUpgradeChoice() == 0) m_Time_AbleToShoot -= 0.1f;
				else if (m_ptrUpgrade1->GetUpgradeChoice() == 1) ++m_BulletDamage;
				else if (m_ptrUpgrade1->GetUpgradeChoice() == 2) m_ptrPlayer->PlusSpeed();
				else if (m_ptrUpgrade1->GetUpgradeChoice() == 3) ++m_PlayerArms;
			}
			else
			{
				if (m_ptrUpgrade2->GetUpgradeChoice() == 0) m_Time_AbleToShoot -= 0.1f;
				else if (m_ptrUpgrade2->GetUpgradeChoice() == 1) ++m_BulletDamage;
				else if (m_ptrUpgrade2->GetUpgradeChoice() == 2) m_ptrPlayer->PlusSpeed();
				else if (m_ptrUpgrade2->GetUpgradeChoice() == 3) ++m_PlayerArms;
			}
		}
	}
}

Point2f Game::RandomEnemyPosition()
{
	float RandomXPosition{ float(rand() % 2) };
	float RandomYPosition{ float(rand() % 2) };

	int RandomBorder2{ rand() % 2 };

	if (RandomBorder2 == 0)
	{
		if (RandomXPosition == 0) RandomXPosition = GetViewPort().left;
		else RandomXPosition = GetViewPort().width;

		RandomYPosition = float(rand() % int(GetViewPort().height));
	}
	else
	{
		if (RandomYPosition == 0) RandomYPosition = GetViewPort().bottom;
		else RandomYPosition = GetViewPort().height;

		RandomXPosition = float(rand() % int(GetViewPort().width));
	}

	return Point2f(RandomXPosition, RandomYPosition);
}
