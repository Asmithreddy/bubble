#include <simplecpp>

class Shooter {
public:
    Circle body;
    Rectangle barrel;
    double speed;

    Shooter(double x, double y, double size, double speed) 
        : body(x, y, size), barrel(x, y - size/2, size/2, size), speed(speed) {
        body.setColor(COLOR(0, 0, 255));
        body.setFill(true);
        barrel.setColor(COLOR(0, 0, 255));
        barrel.setFill(true);
    }

    void moveLeft() {
        body.move(-speed, 0);
        barrel.move(-speed, 0);
    }

    void moveRight() {
        body.move(speed, 0);
        barrel.move(speed, 0);
    }

    void shoot(vector<Rectangle> &bullets) {
        Rectangle bullet(body.getX(), barrel.getY() - barrel.getHeight()/2, 5, 10);
        bullet.setColor(COLOR(0, 255, 0));
        bullet.setFill(true);
        bullets.push_back(bullet);
    }
};

class Bubble {
public:
    Circle bubble;
    double speed;

    Bubble(double x, double y, double size, double speed) 
        : bubble(x, y, size), speed(speed) {
        bubble.setColor(COLOR(255, 0, 0));
        bubble.setFill(true);
    }

    void move() {
        bubble.move(0, speed);
    }

    bool hitBottom(double height) {
        return bubble.getY() + bubble.getRadius() >= height;
    }
};

int main() {
    initCanvas("Bubble Shooter", 800, 600);

    Shooter shooter(400, 550, 50, 10);
    vector<Rectangle> bullets;
    vector<Bubble> bubbles;

    // Adding initial bubbles
    for (int i = 0; i < 5; ++i) {
        bubbles.push_back(Bubble(rand() % 800, 0, 20, 2));
    }

    XEvent event;
    while (true) {
        if (checkEvent(event)) {
            if (keyPressEvent(event)) {
                char c = charFromEvent(event);
                if (c == 'a') {
                    shooter.moveLeft();
                } else if (c == 'd') {
                    shooter.moveRight();
                } else if (c == ' ') {
                    shooter.shoot(bullets);
                }
            }
        }

        // Move bullets
        for (size_t i = 0; i < bullets.size(); ++i) {
            bullets[i].move(0, -5);
            if (bullets[i].getY() <= 0) {
                bullets.erase(bullets.begin() + i);
                --i;
            }
        }

        // Move bubbles
        for (size_t i = 0; i < bubbles.size(); ++i) {
            bubbles[i].move();
            if (bubbles[i].hitBottom(600)) {
                bubbles.erase(bubbles.begin() + i);
                --i;
            }
        }

        // Collision detection
        for (size_t i = 0; i < bubbles.size(); ++i) {
            for (size_t j = 0; j < bullets.size(); ++j) {
                if (bubbles[i].bubble.getX() - bubbles[i].bubble.getRadius() <= bullets[j].getX() &&
                    bubbles[i].bubble.getX() + bubbles[i].bubble.getRadius() >= bullets[j].getX() &&
                    bubbles[i].bubble.getY() - bubbles[i].bubble.getRadius() <= bullets[j].getY() &&
                    bubbles[i].bubble.getY() + bubbles[i].bubble.getRadius() >= bullets[j].getY()) {
                    bubbles.erase(bubbles.begin() + i);
                    bullets.erase(bullets.begin() + j);
                    --i;
                    break;
                }
            }
        }

        // Add new bubbles
        if (rand() % 100 < 2) {
            bubbles.push_back(Bubble(rand() % 800, 0, 20, 2));
        }

        wait(0.02);
    }

    return 0;
}
