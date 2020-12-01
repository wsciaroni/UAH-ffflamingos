#include "npwelcometoroom.h"

NPWelcomeToRoom::NPWelcomeToRoom(/* args */) {}

NPWelcomeToRoom::~NPWelcomeToRoom() {}

void NPWelcomeToRoom::setPositionId(int positionIn) { position = positionIn; }

int NPWelcomeToRoom::getPositionId() { return position; }

void NPWelcomeToRoom::setNames(QString names[6]) {
  for (int i = 0; i < 6; i++) {
    playerNames[i] = names[i];
  }
}

QString* NPWelcomeToRoom::getNames() { return playerNames; }