#include "main.h"
#include "gui.h"
#include "pet.h"

bool button_prev_state_1 = true;
bool button_prev_state_2 = true;
bool button_prev_state_3 = true; 

bool button_pressed_1 = false;
bool button_pressed_2 = false;
bool button_pressed_3 = false;

uint32_t last_time_1 = 0;
uint32_t last_time_2 = 0;
uint32_t last_time_3 = 0;

Pet my_pet(100, 100, 100);

gui_state_t gui_state = PET_PAGE;

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);

  guiSetup();
}

void loop() {

  handleButtons();
  handleAlarm();

  my_pet.update();

  guiRender();
}