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

	for(int CivilianIndex{0}; CivilianIndex < 5; ++CivilianIndex)
	{
		float RandomXPosition{ float(rand() % int(GetViewPort().width)) };
		float RandomYPosition{ float(rand() % int(GetViewPort().height)) };

		m_ptrCivilian.push_back(new Civilian(Point2f(RandomXPosition, RandomYPosition), m_PEOPLE_WIDTH));
	}
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

		int EnemyNumber{ 0 };

		for (EnemyCultMember* Enemies : m_ptrEnemyCultMembers)
		{
			Enemies->Update(elapsedSec, m_ptrPlayer->GetPosition());

			if (IsPointInRect(m_ptrPlayer->GetPosition(), Enemies->GetHitbox()) && Enemies->GetIsDead() == false)
			{
				m_ptrPlayer->SetIsDead(true);
			}

			if (Enemies->GetIsDead())
			{
				//delete m_ptrEnemyCultMembers[EnemyNumber];

				delete Enemies;
				m_ptrEnemyCultMembers.erase(m_ptrEnemyCultMembers.begin() + EnemyNumber);
			}

			++EnemyNumber;
		}	

		int BulletNumber{ 0 };

		for (Bullet* Bullets : m_ptrBullets)
		{
			Bullets->Update(elapsedSec, m_ptrEnemyCultMembers);

			if (Bullets->GetIsActivated() == false)
			{
				delete Bullets;
				m_ptrBullets.erase(m_ptrBullets.begin() + BulletNumber);
			}

			++BulletNumber;
		}

		m_SpawnTimerCounter += elapsedSec;
		SpawnCivilians();

		SpawnEnemyCultMembers(elapsedSec);
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
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_ptrBullets.push_back(new Bullet(5.f, 10.f, GetViewPort(), Point2f{ float(e.x), float(e.y) }, m_ptrPlayer->GetPosition()));
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
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
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

	if (m_ptrPlayer->GetTotalCultMembers() >= 15) m_ENEMY_SPAWN_TIMER_MAX = 2.f;


	if(m_EnemySpawnTimerCounter >= m_ENEMY_SPAWN_TIMER_MAX)
	{
		float RandomXPosition{ float(rand() % 2) };
		float RandomYPosition{ float(rand() % 2) };

		float RandomBorder{ float(rand() % 2) };

		if(RandomBorder == 0)
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

		float RandomBorder2{ float(rand() % 2) };

		if(m_GameTimer >= 30.f)
		{
			m_ptrEnemyCultMembers.push_back(new EnemyCultMember(Point2f(RandomXPosition, RandomYPosition), m_PEOPLE_WIDTH));

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
		}

		m_ptrEnemyCultMembers.push_back(new EnemyCultMember(Point2f(RandomXPosition, RandomYPosition), m_PEOPLE_WIDTH));

		m_EnemySpawnTimerCounter -= m_ENEMY_SPAWN_TIMER_MAX;
	}
}
