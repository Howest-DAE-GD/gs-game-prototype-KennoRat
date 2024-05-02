#pragma once
#pragma once
#include <utils.h>
#include "BaseGame.h"
#include "Player.h"
#include "Civilian.h"
#include "SacrificialPit.h"
#include "EnemyCultMember.h"
#include "Bullet.h"

using namespace utils;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void SpawnCivilians();
	void SpawnEnemyCultMembers(float elapsedSec);

	Player* m_ptrPlayer;
	std::vector<Civilian*> m_ptrCivilian{};
	std::vector<EnemyCultMember*> m_ptrEnemyCultMembers{};
	std::vector<Bullet*> m_ptrBullets{};
	
	SacrificialPit* m_ptrPit;

	float m_GameTimer{};
	float m_SpawnTimerCounter{};
	const float m_SPAWN_TIMER_MAX{ 4.f };
	float m_EnemySpawnTimerCounter{};
	float m_ENEMY_SPAWN_TIMER_MAX{ 3.f };
	const float m_PEOPLE_WIDTH{20.f};
	
};