#include "main.h"
#include "gui.h"
#include "pet.h"

void handleAlarm() {
    static uint32_t last_alarm_update = millis();
    static bool alarm_on = false;

    uint32_t current_time = millis();

    uint32_t happyness = my_pet.getHappiness();
    uint32_t health = my_pet.getHealth();
    uint32_t hunger = my_pet.getHunger();
    bool alive = my_pet.isAlive();

    // if (happyness < 25 || health < 25 || hunger < 25 || !alive) {
    if (!alive) {
        alarm_on = true;
    } else {
        alarm_on = false;
    }

    if (alarm_on) {
        if (current_time - last_alarm_update > 200) {
            last_alarm_update = current_time;
            tone(BUZZER_PIN, 1688, 200);
        }
    };
}