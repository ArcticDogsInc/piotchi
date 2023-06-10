#include "main.h"
#include "gui.h"
#include "pet.h"

void handleButtons() {
  buttonHandler1(pollButton(digitalRead(BUTTON_PIN_1), &button_prev_state_1, &last_time_1));
  buttonHandler2(pollButton(digitalRead(BUTTON_PIN_2), &button_prev_state_2, &last_time_2));
  buttonHandler3(pollButton(digitalRead(BUTTON_PIN_3), &button_prev_state_3, &last_time_3));
}

#define BUONCHE_INTERVAL 15

uint8_t pollButton(bool state, bool* prev_state, uint32_t* last_time) {
  if (state != *prev_state) {
    if (millis() - *last_time > BUONCHE_INTERVAL) {
      // Valid edge
      *prev_state = state;
      *last_time = millis();
      if (state) return 2; // rising
      return 1; // falling
    }
    // Invalid edge
    *prev_state = state;
  }
  return 0;
}

void switchPage() {
    tone(BUZZER_PIN, 1688, 100);
    switch (gui_state)
    {
    case PET_PAGE:
      gui_state = STATS_PAGE;
      break;
    case STATS_PAGE:
      gui_state = ACTIONS_PAGE;
      break;
    case ACTIONS_PAGE:
      gui_state = PET_PAGE;
      break;
    default:
      gui_state = PET_PAGE;
      break;
    }
}

void switchSelectedAction() {

    switch (selected_action)
    {
    case HAPPYNESS:
      selected_action = HEALTH;
      break;
    case HEALTH:
      selected_action = HUNGER;
      break;
    case HUNGER:
      selected_action = HAPPYNESS;
      break;
    default:
      selected_action = HAPPYNESS;
      break;
    }

}

void buttonHandler1(uint8_t press_mode) {
  switch (press_mode )
  {
  case 1:
    button_pressed_1 = true;
    switchPage();
    break;
  case 2:
    button_pressed_1 = false;
  default:
    break;
  }
}
 
void buttonHandler2(uint8_t press_mode) {
  switch (press_mode )
  {
  case 1:
    button_pressed_2 = true;
    switch (gui_state)
    {
    case ACTIONS_PAGE:
      switchSelectedAction();
      break;
    default:
      break;
    }
    break;
  case 2:
    button_pressed_2 = false;
  default:
    break;
  }
}

void applyAction() {
  switch (selected_action)
    {
    case HAPPYNESS:
      my_pet.play(10);
      break;
    case HEALTH:
      my_pet.heal(10);
      break;
    case HUNGER:
      my_pet.feed(10);
      break;
    default:
      break;
  }
}

void buttonHandler3(uint8_t press_mode) {
  switch (press_mode)
  {
  case 1:
    button_pressed_3 = true;

    switch (gui_state)
    {
    case ACTIONS_PAGE:
      applyAction();
      break;
    default:
      break;
    }

    break;
  case 2:
    button_pressed_3 = false;
  default:
    break;
  }
}