#include "GameManager.h"
#include "GameClock.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "SynthManager.h"
#include "ObjectList.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

#include <windows.h>
#include <tchar.h>
#include <conio.h>
#include <strsafe.h>

namespace dsr {
    GameManager::GameManager() {
        m_game_over = false;
    }
    GameManager& dsr::GameManager::getInstance()
    {
        static GameManager gameManager;
        return gameManager;
    }
    int GameManager::startUp()
    {
        printf("DragonShouryo v%s\nCopryight (c)LovelyA72 2023  All rights reserved.\n", DSR_VERSION.c_str());
        LM.startUp();
        RM.startUp();
        WM.startUp();
        SM.startUp();
        DM.startUp();
        IM.startUp();
        m_is_started = true;
        TCHAR szNewTitle[MAX_PATH];
        StringCchPrintf(szNewTitle, MAX_PATH, TEXT("DragonShouryo 1.2 - Debug Console"));
        SetConsoleTitle(szNewTitle);
        return 0;
    }
    void GameManager::shutDown()
    {
        m_is_started = false;
        IM.shutDown();
        DM.shutDown();
        SM.shutDown();
        WM.shutDown();
        RM.shutDown();
        LM.shutDown();
    }
    void GameManager::run()
    {
        GameClock clock;
        while ((!m_game_over) && DM.isOpen()) {
            clock.delta();
            //Do actual stuff here
            m_frame_counter++;
            EventStep step(m_frame_counter);
            onEvent(&step);
            IM.getInput();
            WM.update();
            DM.update();
            //FPS limiter
            int m_frame_time_spent = clock.split();
            
            if (m_frame_time_spent < (FRAME_TIME_DEFAULT)) {
                Sleep(std::max(FRAME_TIME_DEFAULT - m_frame_time_spent - 3,0));
            }
            else {
                //printf("!!! Can't keep up!\n");
                DM.setOverload();
            }
            //printf("Frame %d time: %dms\n", m_frame_counter, m_frame_time_spent);
        }
        printf("GameManager exiting...");
    }
    void GameManager::setGameOver(bool game_over)
    {
        m_game_over = game_over;
    }
    bool GameManager::getGameOver() const
    {
        return m_game_over;
    }
    int GameManager::getFrameCounter() const
    {
        return m_frame_counter;
    }
    int GameManager::getFrameTime() const
    {
        return m_frame_time_spent;
    }
}