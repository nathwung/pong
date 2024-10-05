#include "Ball.h"
#include "Globals.h"
#include "Player.h"
#include "Screen.h"

Ball::Ball()
    : x(0), y(0), velocity_x(0), velocity_y(0), id(0), width(1), height(1) {}

Ball::Ball(double init_x, double init_y, double vel_x, double vel_y,
           int ball_id)
    : x(init_x),
      y(init_y),
      velocity_x(vel_x),
      velocity_y(vel_y),
      id(ball_id),
      width(1),
      height(1) {}

double Ball::getX() { return x; }

int Ball::getID() { return id; }

void Ball::update() {
  x += velocity_x * timeStep;
  y += velocity_y * timeStep;

  if (y <= 0 || y + height >= HEIGHT) {
    velocity_y = -velocity_y;
  }
  velocity_y = velocity_y - 0.02 * timeStep;
}

void Ball::draw(Screen& screen_to_draw_to) {
  screen_to_draw_to.addPixel(static_cast<int>(x), static_cast<int>(y), 'o');
}

int Ball::overlap(Ball& b) {
  bool x_overlap = (x + width >= b.getX()) && (x <= b.getX() + b.width);
  bool y_overlap = (y + height >= b.y) && (y <= b.y + b.height);

  if (x_overlap && y_overlap) {
    return (x_overlap > y_overlap) ? HORIZONTAL_OVERLAP : VERTICAL_OVERLAP;
  }
  return NO_OVERLAP;
}

int Ball::overlap(Player& player) {
  bool x_overlap = (x + width >= player.getX() + 1) &&
                   (x <= player.getX() + player.getWidth());
  bool y_overlap = (y + height >= player.getY()) &&
                   (y <= player.getY() + player.getHeight());

  if (x_overlap && y_overlap) {
    return HORIZONTAL_OVERLAP;
  }
  return NO_OVERLAP;
}

void Ball::bounce(Ball arr[], int ballCount, Player player) {
  if (x <= 0 || x + width >= WIDTH) {
    velocity_x = -velocity_x;
  }

  if (overlap(player) == HORIZONTAL_OVERLAP) {
    velocity_x = -velocity_x;
  }
}
