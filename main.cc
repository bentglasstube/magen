#include <SDL2/SDL.h>

#include "music_screen.h"

#include "game.h"

int main(int, char**) {
  Game::Config config;

  config.graphics.title = "magen";
  config.graphics.width = 640;
  config.graphics.height = 360;
  config.graphics.fullscreen = false;

  config.audio.format = AUDIO_U8;
  config.audio.channels = 1;
  config.audio.frequency = 28160;
  config.audio.chunksize = 128;

  Game game(config);
  game.loop(new MusicScreen());

  return 0;
}
