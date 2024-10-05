#include "Player.h"
#include "Screen.h"
#include <iostream>
using namespace std;

Player::Player() : x(0), y(0), height(10), width(1) {}

Player::Player(double init_x, double init_y, int init_height)
    : x(init_x), y(init_y), height(init_height), width(1) {}

double Player::getX() {
    return x;
}

double Player::getY() {
    return y;
}

int Player::getHeight() {
    return height;
}

int Player::getWidth() {
    return width;
}

void Player::decreaseHeight(int decrease) {
    if (height < 3) {
        // do not decrease
    } else {
        height -= decrease;
    }
}

void Player::update(char c) {
    if (c == 'A' && getY() + getHeight() < HEIGHT) {  
        y += 2; 
    } else if (c == 'B' && getY() > 0) {  
        y -= 2; 
    }

    if (y + height > HEIGHT) {
        y = HEIGHT - height;  
    }
    if (y < 0) {
        y = 0; 
    }
}

void Player::draw(Screen& screen_to_draw_to) {
    for (int i = 0; i < height; ++i) {
        screen_to_draw_to.addPixel(x, y + i, '#');
    }
}
