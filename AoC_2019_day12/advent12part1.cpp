/*
Day 12: The N-Body Problem
Io, Europa, Ganymede, and Callisto
<x=1, y=-4, z=3>
<x=-14, y=9, z=-4>
<x=-4, y=-6, z=7>
<x=6, y=-9, z=-11>
1. update velocity by applying gravity  +-1
2. update position by applying velocity +=velocity
potential energy = abs x + abs y + abs z
kinetic energy = abs vx + abs vy + abs vz
*/
#include <iostream>
#include <vector>
#include <cstdio>  // printf

using namespace std;

class Moon {
public:

    // Constructor
    Moon(int x, int y, int z, int vx, int vy, int vz) :
        x(x), y(y), z(z), vx(vx), vy(vy), vz(vz) {}

    // To apply gravity, consider every pair of moons. On each axis (x, y, and z),
    // the velocity of each moon changes by exactly +1 (if x<neighbour.x), -1
    // (if x<neighbour.x).
    // If the positions on a given axis are the same, the velocity does not change
    void updateVelocity(Moon& neighbour) {
        int xdiff = x - neighbour.x;
        int ydiff = y - neighbour.y;
        int zdiff = z - neighbour.z;
        if (xdiff > 0) {
            vx -= 1;
        } else if (xdiff < 0) {
            vx += 1;
        }
        if (ydiff > 0) {
            vy -= 1;
        } else if (ydiff < 0) {
            vy += 1;
        }
        if (zdiff > 0) {
            vz -= 1;
        } else if (zdiff < 0) {
            vz += 1;
        }
    }

    // Once all gravity has been applied, apply velocity: simply add the velocity
    // of each moon to its own position
    void updatePosition() {
        x += vx;
        y += vy;
        z += vz;
    }

    void printPosVel() const {
        printf("pos=<x=%3d, y=%3d, z=%3d>, vel=<x=%3d, y=%3d, z=%3d>\n",
               x, y, z, vx, vy, vz);
    }

    // A moon's potential energy is the sum of the absolute values of its x, y,
    // and z position coordinates
    int calculatePotentialEnergy() const {
       return abs(x) + abs(y) + abs(z);
    }

    // A moon's kinetic energy is the sum of the absolute values of its velocity
    // coordinates
    int calculateKineticEnergy() const {
       return abs(vx) + abs(vy) + abs(vz);
    }

    // The total energy for a single moon is its potential energy multiplied (not added??)
    // by its kinetic energy.
    int calculateTotalEnergy() const {
        return calculatePotentialEnergy() * calculateKineticEnergy();
    }

private:
    int x;
    int y;
    int z;
    int vx;
    int vy;
    int vz;
};


int main() {

    Moon Io       (  1, -4,   3, 0, 0, 0);
    Moon Europa   (-14,  9,  -4, 0, 0, 0);
    Moon Ganymede ( -4, -6,   7, 0, 0, 0);
    Moon Callisto (  6, -9, -11, 0, 0, 0);
    vector<Moon> moons;

    moons.push_back(Io);
    moons.push_back(Europa);
    moons.push_back(Ganymede);
    moons.push_back(Callisto);

    // run simulation 1000 steps
    const int maxsteps = 1000;
    for (int count = 0; count < maxsteps; ++count) {

        // first update the velocity of every moon by applying gravity
        // for (vector<Moon>::iterator it1 = moons.begin(); it1 != moons.end(); ++it1)
        for (auto it1 = moons.begin(); it1 != moons.end(); ++it1)
            for (auto it2 = moons.begin(); it2 != moons.end(); ++it2)
                if (it2 != it1)
                    it1->updateVelocity(*it2);

        // Once all gravity has been applied, update position by applying velocity
        for (auto it1 = moons.begin(); it1 != moons.end(); ++it1)
            it1->updatePosition();
    }

    // The total energy for all moons
    int TotalSystemEnergy = 0;
    for (const auto moon: moons)
        TotalSystemEnergy += moon.calculateTotalEnergy();

    // 14606
    cout << "The total energy in the system after simulating the moons given "
            "in my scan for " << maxsteps << " steps is " << TotalSystemEnergy << endl;

    return 0;
}


