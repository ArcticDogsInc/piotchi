#pragma once

class Pet {
public:
  Pet(int initial_hunger, int initial_happiness, int initial_health);
  void feed(int amount);
  void play(int amount);
  void heal(int amount);
  void update();
  int getHunger() const;
  int getHappiness() const;
  int getHealth() const;
  bool isAlive() const;
private:
  void updateHunger();
  void updateHappiness();
  void updateHealth();
  int _hunger;
  int _happiness;
  int _health;
  unsigned long _last_update_hunger;
  unsigned long _last_update_happiness;
  unsigned long _last_update_health;
};

extern Pet my_pet;