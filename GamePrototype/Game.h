#pragma once
#pragma once
#include <utils.h>
#include "BaseGame.h"
#include "Player.h"
#include "Civilian.h"
#include "SacrificialPit.h"
#include "EnemyCultMember.h"
#include "Bullet.h"
#include "Text.h"
#include "Upgrades.h"
#include "UI.h"
#include "Camera.h"

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
	void BulletDelay(float elapsedSec);
	void ShootBullet();
	void GetUpgrades(Rectf player);

	Point2f RandomEnemyPosition();

	Player* m_ptrPlayer;
	std::vector<Civilian*> m_ptrCivilian{};
	std::vector<EnemyCultMember*> m_ptrEnemyCultMembers{};
	std::vector<Bullet*> m_ptrBullets{};
	
	SacrificialPit* m_ptrPit;

	std::string m_ShowText{"Feed Me and thou shall receive my power!!!"};
	Text* m_ptrText;

	Upgrades* m_ptrUpgrade1;
	Upgrades* m_ptrUpgrade2;
	UI* m_ptrUI;
	Camera* m_ptrCamera;

	bool m_AbleToShoot{ false };
	bool m_IsShooting{ false };
	bool m_ChooseUpgrades{false};
	bool m_DashReset{ true };
	bool m_CheatUpgrade{false};
	bool m_CheatEnemies{ false };
	int m_UpgradeAmount{0};
	int m_BulletDamage{ 1 };
	int m_PlayerArms{ 1 };
	int m_PlayerDashAmount{ 0 };
	int m_DashAmount{ 1 };
	float m_GameTimer{};
	float m_SpawnTimerCounter{};
	float m_DashPressCounter{};
	float m_DASH_MAX{ 2.f };
	const float m_SPAWN_TIMER_MAX{ 4.f };
	float m_EnemySpawnTimerCounter{};
	float m_ENEMY_SPAWN_TIMER_MAX{ 3.f };
	const float m_PEOPLE_WIDTH{20.f};
	float m_AbleToShootCounter{0.f};
	float m_Time_AbleToShoot{0.5f};

	Point2f m_MousePosition{};
	
	void DashCounter( float elapsedSec );
};