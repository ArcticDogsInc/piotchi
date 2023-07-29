#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1

// Pin definitions
#define BUTTON_PIN_1 9
#define BUTTON_PIN_2 10
#define BUTTON_PIN_3 11
#define BUZZER_PIN 8

extern bool button_prev_state_1;
extern bool button_prev_state_2;
extern bool button_prev_state_3;

extern bool button_pressed_1;
extern bool button_pressed_2;
extern bool button_pressed_3;

extern uint32_t last_time_1;
extern uint32_t last_time_2;
extern uint32_t last_time_3;

void buttonHandler1(uint8_t press_mode);
void buttonHandler2(uint8_t press_mode);
void buttonHandler3(uint8_t press_mode);

// Button handling buttons
void handleButtons();
uint8_t pollButton(bool state, bool* prev_state, uint32_t* last_time);