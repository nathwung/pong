#include <string>
#include "Ball.h"
#include "Globals.h"
#include "Player.h"
#include "Screen.h"
#include "io.h"

int main() {
  int score = 0;
  bool gameEnded = false;
  std::string messageToPutOnScreen;

  std::chrono::steady_clock::time_point begin_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point now_time;
  Screen screen = Screen();

  int ballCount = 0;
  const int maxBallCount = 5;

  Ball balls_array[maxBallCount];
  balls_array[0] = Ball(30.0, 30.0, 1.7, 0, ballCount);
  ballCount++;

  Player player = Player(0, 5, 10);

  while (!gameEnded) {
    for (int tick = 0; tick < simulation_fps; tick++) {
      char userinput = get_input();
      if (userinput == 'q') {
        gameEnded = true;
      }
      if (userinput == 'A') {
        player.update('A');
      }
      if (userinput == 'B') {
        player.update('B');
      }

      for (int i = 0; i < ballCount; i++) {
        balls_array[i].update();

        if (balls_array[i].overlap(player) == HORIZONTAL_OVERLAP) {
          score++;
          if (score % 2 == 0) {
            player.decreaseHeight(1);
          }
          if (score % 5 == 0 && ballCount < maxBallCount) {
            balls_array[ballCount] = Ball(30.0, 30.0, 0.9, 0, ballCount);
            ballCount++;
          }
        }

        if (balls_array[i].getX() <= 0) {
          gameEnded = true;
        }
        balls_array[i].bounce(balls_array, ballCount, player);
      }
    }

    player.draw(screen);
    for (int j = 0; j < ballCount; j++) {
      balls_array[j].draw(screen);
    }

    messageToPutOnScreen = "Your score is: " + std::to_string(score);
    screen.update(messageToPutOnScreen);

    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin_time)
               .count() < (long int)milliseconds_per_frame) {
    }

    begin_time = std::chrono::steady_clock::now();
  }

  messageToPutOnScreen = "Game over. Your score is: " + std::to_string(score);
  screen.update(messageToPutOnScreen);

  return 0;
}
