#include <SDL2/SDL.h>

#include "music_screen.h"

#include "framework/game.h"

int main(int, char**) {
  Game game(640, 360);
  game.loop(new MusicScreen());

  return 0;
}
