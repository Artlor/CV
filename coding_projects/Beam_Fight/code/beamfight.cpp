#include <iostream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <string>

#include "player.h"
#include "globalsettings.h"
#include "endscreen.h"
#include "canupdate.h"
#include "setuppolewalki.h"
#include "updateenum.h"
#include "drawborders.h"
#include "drawbeamfight.h"
#include "drawspacesonarena.h"
#include "clear.h"
#include "playersinput.h"
#include "whichplayerenum.h"
#include "movebulletonpolewalki.h"
#include "collisiondetector.h"
#include "bulletcollisiontype.h"
#include "collide.h"
#include "statystyki.h"
#include "collisiontype.h"
#include "hitplayer.h"
#include "readsettingsfromfile.h"
#include "showpositionoflastbullet.h"
#include "punishfortoomanybulletchanges.h"

int main()
{
	srand(time(NULL));
	readSettingsFromFile();
	Player p1(0, playerHp, playerMana, playerName1, WhichPlayerEnum::Left);
	Player p2(distanceBetweenPlayers-1, playerHp, playerMana, playerName2, WhichPlayerEnum::Right);
	char poleWalki[distanceBetweenPlayers];
	setupPoleWalki(poleWalki, distanceBetweenPlayers, p1, p2);

	while (p1.isAlive() && p2.isAlive())
	{
		if (canUpdate(UpdateEnum::Input, inputUpdateTime))	//CHECKING INPUT
		{
			playersInput(&p1, &p2);
		}

		if (canUpdate(UpdateEnum::Events, eventsUpdateTime))	//EVENTS (MOVING BULLETS, CHECKING BULETTS COLLISION, BULLET COLLISION WITH PLAYER, END OF GAME)
		{
			//SHOOTING BULLET
			if (p1.doesPlayerWantToShoot())
			{
				if (!(p2.pociskManager.getBulletPositionX(0) == 1))
				{
					if (p1.pociskManager.isVectorEmpty()) //DOES SOME BULLET ALREADY EXIST?
					{
						if (p1.manaCheck())
						{
							p1.shoot();
							placeBulletOnPoleWalki(poleWalki, p1);
						}
					}
					else if (p1.pociskManager.getBulletPositionX(p1.pociskManager.getNumberOfBullets() - 1) > 1)
					{
						if (p1.manaCheck())
						{
							p1.shoot();
							placeBulletOnPoleWalki(poleWalki, p1);
						}
					}
				}
				p1.setAllWantsToShootToFalse();
			}

			if (p2.doesPlayerWantToShoot())
			{
				if (!(p1.pociskManager.getBulletPositionX(0) == distanceBetweenPlayers - 2))
				{
					if (p2.pociskManager.isVectorEmpty())
					{
						if (p2.manaCheck())
						{
							p2.shoot();
							placeBulletOnPoleWalki(poleWalki, p2);
						}
					}
					else if (p2.pociskManager.getBulletPositionX(p2.pociskManager.getNumberOfBullets() - 1) < distanceBetweenPlayers - 2)
					{
						if (p2.manaCheck())
						{
							p2.shoot();
							placeBulletOnPoleWalki(poleWalki, p2);
						}
					}

				}
				p2.setAllWantsToShootToFalse();
			}
			//MOVING ALREADY SHOT BULLET
			int p1_iterator = 0;
			if (p1.pociskManager.getNumberOfBullets() != 0)
			{
				if (p1.pociskManager.canMoveTimer(0))
				{
					CollisionType collisionType = collisionDetector(p1,p2);
					if(collisionType == CollisionType::BulletHitsBullet)
					{
						if (!collideAndCheckIsFatal(getBulletCollisionType(p1, p2), poleWalki, p1, p2))
						{
							p1.pociskManager.moveBullet(0);
							moveBulletOnPoleWalki(poleWalki, p1, 0);
							p1_iterator = 1;
						}
					}
					else if (collisionType == CollisionType::BulletHitsPlayer)
					{
						hitPlayer(poleWalki, p1, p2);
					}
					else if(collisionType == CollisionType::NONE)
					{
						p1.pociskManager.moveBullet(0);
						moveBulletOnPoleWalki(poleWalki, p1, 0);
						p1_iterator = 1;
					}
				}
			}


			for (p1_iterator; p1_iterator < p1.pociskManager.getNumberOfBullets(); p1_iterator++)
			{
				if (p1.pociskManager.canMoveTimer(p1_iterator))
				{
					p1.pociskManager.moveBullet(p1_iterator);
					moveBulletOnPoleWalki(poleWalki, p1, p1_iterator);
				}
			}

			int p2_iterator = 0;
			if (p2.pociskManager.getNumberOfBullets() != 0)
			{
				if (p2.pociskManager.canMoveTimer(0))
				{
					CollisionType collisionType = collisionDetector(p2, p1);
					if (collisionType == CollisionType::BulletHitsBullet)
					{

						if (!collideAndCheckIsFatal(getBulletCollisionType(p2, p1), poleWalki, p2, p1))
						{
							p2.pociskManager.moveBullet(0);
							moveBulletOnPoleWalki(poleWalki, p2, 0);
							p2_iterator = 1;
						}
					}
					else if (collisionType == CollisionType::BulletHitsPlayer)
					{
						hitPlayer(poleWalki, p2, p1);
					}
					else if (collisionType == CollisionType::NONE)
					{
						p2.pociskManager.moveBullet(0);
						moveBulletOnPoleWalki(poleWalki, p2, 0);
						p2_iterator = 1;
					}
				}
			}

			for (p2_iterator; p2_iterator < p2.pociskManager.getNumberOfBullets(); p2_iterator++)
			{
				if (p2.pociskManager.canMoveTimer(p2_iterator))
				{
					p2.pociskManager.moveBullet(p2_iterator);
					moveBulletOnPoleWalki(poleWalki, p2, p2_iterator);
				}
			}
			
			if (canUpdate(UpdateEnum::CanPunishForTooManyBulletChanges, 250))
			{
				punishForTooManyBulletChanges(p1, p2);
			}

			if (canUpdate(UpdateEnum::PeriodicallyAddMana, 200))
			{
				p1.periodicallyAddMana(1);
				p2.periodicallyAddMana(1);
			}
		}

		if (canUpdate(UpdateEnum::RefreshRate, refreshRateUpdateTime))	//DISPLAYING REFRESHED GAME
		{
			clearConsole();
			std::cout << "\n\n\n\n\n\n\n\n\n\n";
			drawUpBorder(distanceBetweenPlayers);
			drawBeamFight(poleWalki, distanceBetweenPlayers);
			drawDownBorder(distanceBetweenPlayers);
			showPositionOfLastBullet(p1, p2);

			//STATISTICS
			statystyki(p1,p2);
			//DIAGNOSTICS
			std::cout << std::endl << std::endl;
			p1.pociskManager.countBullets();
			std::cout << std::endl << std::endl;
			p2.pociskManager.countBullets();
			std::cout << std::endl << std::endl;
			if (p1.pociskManager.getNumberOfBullets() > 1)
			p1.pociskManager.getTimeBetweenBullets();
			std::cout << std::endl;
			if (p2.pociskManager.getNumberOfBullets() > 1)
			p2.pociskManager.getTimeBetweenBullets();
		}
	}
	statystykiEnd(p1,p2);
	endScreen(p1,p2);
	std::cout << "\n\n\n\n\n\n\n\n\n\n";
	getchar();
	getchar();
}