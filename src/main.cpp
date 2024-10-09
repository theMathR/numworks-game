#include "eadkpp.h"
#include "math.h"

using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Test";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

double delta = 100;

struct Vec2 {
  double x;
  double y;
};

void draw_monochrome_sprite(Vec2 coord, Color color, const uint16_t * sprite){
    uint16_t pixels[sprite[0]*sprite[1]];
    const Rect sprite_rect(coord.x, coord.y, sprite[0], sprite[1]);
    Display::pullRect(sprite_rect, pixels);
    
    int x = 0;
    int y = 0;
    int pixels_until_switch = sprite[2];
    int index = 2;
    bool coloring = false;
    while (y<sprite_rect.height()) {
      if (!pixels_until_switch) {
        index++;
        coloring = !coloring;
        pixels_until_switch = sprite[index];
      }
      pixels_until_switch--;
      
      if (coloring) {
        pixels[x+sprite_rect.width()*y] = color;
      }
      
      x++;
      if (x == sprite_rect.width()) {
        x = 0;
        y++;
      }
    }
    
    Display::pushRect(sprite_rect, pixels);
}

const uint16_t spr_toriel[864] = {72,102,171,2,13,2,54,2,15,2,53,2,15,2,53,3,2,9,2,3,53,3,1,11,1,3,54,2,1,11,1,2,52,2,3,13,3,2,48,25,46,27,45,27,44,4,1,1,5,7,5,1,1,4,43,4,1,6,2,3,2,6,1,4,43,4,1,3,1,1,1,8,1,1,1,2,1,4,42,5,1,1,6,5,6,1,1,5,41,5,1,2,1,1,2,7,2,1,1,2,1,5,41,5,1,4,2,7,2,4,1,5,41,5,2,2,1,11,1,2,2,5,41,5,2,17,2,5,41,5,2,17,2,5,41,6,2,15,2,6,41,6,2,5,1,3,1,5,2,6,41,6,2,15,2,6,42,5,3,13,3,5,43,5,4,11,4,5,43,6,3,3,5,3,3,6,43,6,4,9,4,6,39,2,3,5,5,7,5,5,3,2,33,3,4,5,17,5,4,3,30,4,5,3,19,3,5,4,28,4,37,4,26,5,37,5,25,5,5,6,15,6,5,5,25,4,5,1,6,2,11,2,6,1,5,4,24,5,4,1,9,11,9,1,4,5,23,5,4,1,29,1,4,5,23,5,4,1,3,2,19,2,3,1,4,5,22,6,4,1,3,6,11,6,3,1,4,6,21,6,4,1,6,4,3,3,3,4,6,1,4,6,21,6,4,1,5,6,1,5,1,6,5,1,4,6,20,6,5,1,7,4,1,5,1,4,7,1,5,6,19,6,4,1,1,1,8,2,2,3,2,2,8,1,1,1,4,6,19,6,4,1,1,1,27,1,1,1,4,6,19,6,4,1,2,1,25,1,2,1,4,6,19,6,4,1,2,1,25,1,2,1,4,6,18,7,4,1,3,1,23,1,3,1,4,7,17,7,4,1,3,1,7,1,7,1,7,1,3,1,4,7,16,8,4,1,4,1,5,3,5,3,5,1,4,1,4,8,15,7,5,1,4,1,5,3,5,3,5,1,4,1,5,7,14,8,5,1,5,1,19,1,5,1,5,8,13,8,5,1,5,1,19,1,5,1,5,8,13,8,5,1,6,1,7,3,7,1,6,1,5,8,12,9,5,1,6,1,7,3,7,1,6,1,5,9,11,9,4,1,8,1,7,1,7,1,8,1,4,9,10,10,4,1,9,1,13,1,9,1,4,10,9,10,4,1,10,1,11,1,10,1,4,10,8,11,4,1,11,1,9,1,11,1,4,11,7,10,5,1,12,2,5,2,12,1,5,10,7,10,5,1,14,5,14,1,5,10,6,11,4,1,35,1,4,11,5,11,4,1,35,1,4,11,5,11,4,1,35,1,4,11,6,10,4,1,35,1,4,10,8,9,4,1,35,1,4,9,7,1,2,8,4,1,35,1,4,8,2,1,5,2,2,7,4,1,35,1,4,7,2,2,5,3,1,7,4,1,35,1,4,7,1,3,4,4,2,6,4,1,35,1,4,6,2,4,3,5,2,5,4,1,35,1,4,5,2,5,2,6,2,5,4,1,35,1,4,5,2,6,1,6,2,5,4,1,35,1,4,5,2,6,1,4,1,2,2,4,4,1,35,1,4,4,2,2,1,4,1,4,1,2,2,4,4,1,35,1,4,4,2,2,1,4,1,4,2,1,3,3,4,1,35,1,4,3,3,1,2,4,2,3,8,1,4,1,35,1,4,1,8,3,4,1,1,1,12,1,35,1,12,1,1,1,20,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,34,1,37,1,33,1,37,1,33,1,37,1,33,1,37,1,34,2,33,2,37,4,10,5,10,4,43,10,5,10,261,1,27,1,43,12,5,12,42,13,5,13,36,18,5,18,30,19,5,19,28,19,7,19,27,2,1,3,1,10,11,10,1,3,1,2,27,2,1,3,1,3,25,3,1,3,1,2,28,1,1,3,1,2,27,2,1,3,1,1};



int main(int argc, char * argv[]) {
  double hue = 0;
  uint64_t time = Timing::time();
  Vec2 position = {0,0};
  Vec2 velocity = {5,5};
  double speed = 1;
  
  while (1) {
    Keyboard::State keyboardState = Keyboard::scan();
    
    int h = hue/60;
    if (h*60 > hue) {
      h-=1;
    }
    h%=6;
    double f = (hue/60 - h)*255;
    uint8_t r,g,b;
    switch (h) {
      case 0:
        r = 255;
        g = f;
        b = 0;
        break;
      case 1:
        r = 255-f;
        g = 255;
        b = 0;
        break;
      case 2:
        r = 0;
        g = 255;
        b = f;
        break;
      case 3:
        r = 0;
        g = 255-f;
        b = 255;
        break;
      case 4:
        r = f;
        g = 0;
        b = 255;
        break;
      case 5:
        r = 255;
        g = 0;
        b = 255-f;
        break;
    }
    
    Display::pushRectUniform(Screen::Rect, 0);//Color(0xffffff-(r<<16|g<<8|b)));
    draw_monochrome_sprite(position, Color(r<<16|g<<8|b), spr_toriel);
    hue += delta/50;
    if (hue > 360) hue -= 360;
    
    position.x += velocity.x * delta/100 * speed;
    position.y += velocity.y * delta/100 * speed;
    bool collision = false;
    if (position.y < 0) {
      position.y = 0;
      velocity.y *= -1;
      collision = true;
    }
    if (position.y > Screen::Height-102) {
      position.y = Screen::Height-103;
      velocity.y *= -1;
      collision = true;
    }
    if (position.x < 0) {
      position.x = 0;
      velocity.x *= -1;
      collision = true;
    }
    if (position.x > Screen::Width/2-72) {
      position.x = Screen::Width/2-73;
      velocity.x *= -1;
      collision = true;
    }
    if (collision) {
      speed = ((random()&0b1111)/0b11110) + .75;
    }
    
    if (keyboardState.keyDown(Keyboard::Key::Shift)) {
      break;
    }
    
    Display::waitForVBlank();
    uint64_t new_time = Timing::time();
    delta = new_time - time;
    time = new_time;
  }
}
