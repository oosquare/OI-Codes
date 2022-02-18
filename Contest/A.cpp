#include <iostream>
using namespace std;

struct Vector {
    int x, y;
    
    Vector(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    Vector operator+(const Vector & rhs) const {
        return Vector(x + rhs.x, y + rhs.y);
    }

    Vector operator-(const Vector & rhs) const {
        return Vector(x - rhs.x, y - rhs.y);
    }

    int dot(const Vector & rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    int cross(const Vector & rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    Vector rotate() const {
        return Vector(-y, x);
    }
};

int main() {

}