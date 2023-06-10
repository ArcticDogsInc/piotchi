#include "main.h"
#include "gui.h"
#include "pet.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint8_t circle_radius = 8;
uint8_t x = circle_radius;
uint8_t y = circle_radius;
int8_t vx = 1;
int8_t vy = 1;


void renderCircle() {

  static uint32_t last_circle_move = millis();

  uint32_t current_time = millis();

  uint16_t move_interval = (100-my_pet.getHappiness()); // 0 --> 100
  if (move_interval >= 100) move_interval = 1e3;

  if (!my_pet.getHealth()) {
    vx = 0;
    vy = 0;
    display.drawCircle(x, y, circle_radius, WHITE);
    display.drawLine(x-2 -5, y-2 +5, x+2-5, y+2 +5, WHITE);
    display.drawLine(x-2 -5, y+2 +5, x+2-5, y-2 +5, WHITE);
    display.drawLine(x+2 -5, y-2 +5, x-2-5, y+2 +5, WHITE);
    display.drawLine(x+2 -5, y+2 +5, x-2-5, y-2 +5, WHITE);

    display.drawLine(x-2 +5, y-2 +5, x+2+5, y+2 +5, WHITE);
    display.drawLine(x-2 +5, y+2 +5, x+2+5, y-2 +5, WHITE);
    display.drawLine(x+2 +5, y-2 +5, x-2+5, y+2 +5, WHITE);
    display.drawLine(x+2 +5, y+2 +5, x-2+5, y-2 +5, WHITE);
    return;
  } 

  if (current_time - last_circle_move > move_interval) {
    last_circle_move = current_time;
    x += vx;
    y += vy;

    if (x + circle_radius >= display.width() || x - circle_radius <= 0) {
      vx = -vx;
      x += vx;
    }
    if (y + circle_radius >= display.height() - 1 || y - circle_radius <= 0) {
      vy = -vy;
      y += vy;
    }
  }


  display.drawCircle(x, y, circle_radius, WHITE);
  display.drawLine(x+vx-2, y+vy-2, x+vx-2, y+vy+2, WHITE);
  display.drawLine(x+vx+2, y+vy-2, x+vx+2, y+vy+2, WHITE);

  // display.drawLine(x-3, y+5, x+3, y+5, WHITE);
}

void guiSetup() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }
    digitalWrite(LED_BUILTIN, HIGH);
    tone(BUZZER_PIN, 1688, 100);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);

    display.setTextSize(2);
    display.setTextColor(WHITE); 
    display.cp437(true);

    display.clearDisplay();
    display.display();
}

void renderBtns() {
    if (button_pressed_1) 
    display.fillRect(BTNS_M, BTNS_Y, BTN_W, BTN_H, WHITE); 
  else 
    display.drawRect(BTNS_M, BTNS_Y, BTN_W, BTN_H, WHITE);

  if (button_pressed_2) 
    display.fillRect(BTNS_M + BTN_W + BTNS_DX, BTNS_Y, BTN_W, BTN_H, WHITE); 
  else 
    display.drawRect(BTNS_M + BTN_W + BTNS_DX, BTNS_Y, BTN_W, BTN_H, WHITE);

  if (button_pressed_3) 
    display.fillRect(BTNS_M + 2*(BTN_W + BTNS_DX), BTNS_Y, BTN_W, BTN_H, WHITE); 
  else 
    display.drawRect(BTNS_M + 2*(BTN_W + BTNS_DX), BTNS_Y, BTN_W, BTN_H, WHITE);
}

const unsigned char star [] PROGMEM = {
	// 'star, 16x16px
	0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x08, 0x80, 0xf8, 0xf8, 0x45, 0x10, 0x05, 0x00, 
	0x25, 0x20, 0x20, 0x20, 0x00, 0x00, 0x42, 0x10, 0x4d, 0x90, 0xb0, 0x68, 0x00, 0x00, 0x00, 0x00
};

const unsigned char hearth [] PROGMEM = {
	// 'png-transparent-pixel-heart, 15x15px
	0x00, 0x00, 0x3c, 0x70, 0x7e, 0xfc, 0xcf, 0xfe, 0xcf, 0xfe, 0xff, 0xfe, 0x7f, 0xfc, 0x3f, 0xf0, 
	0x1f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char food [] PROGMEM = {
	// 'fried-chicken-pixel-art-vector_553915-56, 25x25px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x10, 0x30, 0x00, 
	0x00, 0x10, 0x30, 0x00, 0x00, 0x20, 0x30, 0x00, 0x00, 0x20, 0x70, 0x00, 0x00, 0x40, 0xf0, 0x00, 
	0x00, 0x4f, 0xe0, 0x00, 0x00, 0x4f, 0xc0, 0x00, 0x00, 0x9f, 0x80, 0x00, 0x03, 0x1c, 0x00, 0x00, 
	0x04, 0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x06, 0x40, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

void renderStats() {
  uint8_t bar_width = 100;
  uint8_t bar_height = 6;
  uint8_t bar_spacing = 15;

  display.drawBitmap(5, 0, star, 15, 15, WHITE);
  display.drawBitmap(5, 21, hearth, 15, 15, WHITE);
  display.drawBitmap(0, 36, food, 25, 25, WHITE);

  for (int i = 0; i < 3; i++) {
    int x = (SCREEN_WIDTH - bar_width) / 2;
    int y = (SCREEN_HEIGHT - (3 * bar_height + 2 * bar_spacing)) / 2 + i * (bar_height + bar_spacing);
    display.drawRect(x + 10, y - 3, bar_width, bar_height, WHITE);
  }

  int values[] = {my_pet.getHappiness(), my_pet.getHealth(), my_pet.getHunger()};
  for (int i = 0; i < 3; i++) {
    int x = (SCREEN_WIDTH - bar_width) / 2;
    int y = (SCREEN_HEIGHT - (3 * bar_height + 2 * bar_spacing)) / 2 + i * (bar_height + bar_spacing);
    display.fillRect(x + 10, y - 3, bar_width * values[i]/100, bar_height, WHITE);
  }
}

action_t selected_action = HAPPYNESS;

void renderActions() {

  uint8_t bar_width = 125;
  uint8_t bar_height = 15;
  uint8_t bar_spacing = 5;

  char action_label[3][5];
  
  strcpy(action_label[0], "Play");
  strcpy(action_label[1], "Heal");
  strcpy(action_label[2], "Feed");

  display.setTextSize(2);
  for (int i = 0; i < 3; i++) {
    int x = (SCREEN_WIDTH - bar_width) / 2;
    int y = (SCREEN_HEIGHT - (3 * bar_height + 2 * bar_spacing)) / 2 + i * (bar_height + bar_spacing) - 3;
    // display.drawRect(x, y, bar_width, bar_height, WHITE);
    display.setCursor(x+35, y);
    display.println(action_label[i]);
    if (i == selected_action) {
      display.fillCircle(x+20, y+5, 3, WHITE);
    }
  }
}

void guiRender() {
  display.clearDisplay();

  switch (gui_state) {
    default:
      renderCircle();
      break;
    case STATS_PAGE:
      renderStats();
      break;
    case ACTIONS_PAGE:
      renderActions();
      break;
  }

  renderBtns();

  display.display();
}