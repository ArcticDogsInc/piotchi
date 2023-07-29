#pragma once

#include "main.h"

#define BTN_W 20
#define BTN_H 3
#define BTNS_Y 59
#define BTNS_DX 5
#define BTNS_M ((SCREEN_WIDTH - 3*BTN_W - 2*BTNS_DX)/2)

// GUI Pages
typedef enum {
    PET_PAGE,
    STATS_PAGE,
    ACTIONS_PAGE
} gui_state_t;

// Pet stats modifiers actions
typedef enum {
  HAPPYNESS,
  HEALTH,
  HUNGER
} action_t;

extern gui_state_t gui_state;
extern action_t selected_action;

void guiRender();
void guiSetup();
void renderPet();
void renderBtns();
void renderPet();
void renderAtions();
void renderStats();
void switchPage();
void switchSelectedAction();
void applyAction();
void handleAlarm();