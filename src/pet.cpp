#include "pet.h"
#include "main.h"

Pet::Pet(int initial_hunger, int initial_happiness, int initial_health)
  : _hunger(initial_hunger), _happiness(initial_happiness), _health(initial_health) {
  _last_update_happiness = millis();
  _last_update_health = millis();
  _last_update_hunger = millis();
}

void Pet::feed(int amount) {
  _hunger += amount;
  if (_hunger > 100) {
    _hunger = 100;
  }
}

void Pet::play(int amount) {
  _happiness += amount;
  if (_happiness > 100) {
    _happiness = 100;
  }
}

void Pet::heal(int amount) {
  _health += amount;
  if (_health > 100) {
    _health = 100;
  }
}

void Pet::update() {
  uint32_t current_time = millis();

  uint32_t t1 = current_time - _last_update_hunger; 
  if (t1 > 5e3) { 
    _hunger -= (t1) / 5e3;
    if (_hunger < 0) _hunger = 0;
    if (_hunger == 0) _health--;
    if (_health < 0) _health = 0;
    _last_update_hunger = current_time;
  }

  uint32_t t2 = current_time - _last_update_happiness; 
  if (t2 > 10e3) { 
    _happiness -= (t2) / 10e3;
    if (_happiness < 0) _happiness = 0;
    _last_update_happiness = current_time;
  }

  uint32_t t3 = current_time - _last_update_health; 
  if (t3 > 20e3) { 
    _health -= (t3) / 20e3;
    if (_health < 0) _health = 0;
    _last_update_health = current_time;
  }

  if (_health < _happiness) _happiness = _health;
  if (_hunger < _happiness) _happiness = _hunger;
}

int Pet::getHunger() const {
  return _hunger;
}

int Pet::getHappiness() const {
  return _happiness;
}

int Pet::getHealth() const {
  return _health;
}

bool Pet::isAlive() const {
  return _health > 0;
}

extern Pet my_pet;