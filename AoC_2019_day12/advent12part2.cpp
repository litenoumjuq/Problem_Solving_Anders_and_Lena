/*****************************************************************************************
Day 12: The N-Body Problem Part 2
https://adventofcode.com/2019/day/12
Io, Europa, Ganymede, and Callisto
<x=1, y=-4, z=3>
<x=-14, y=9, z=-4>
<x=-4, y=-6, z=7>
<x=6, y=-9, z=-11>
1. update velocity by applying gravity  +-1
2. update position by applying velocity +=velocity
potential energy = abs x + abs y + abs z
kinetic energy = abs vx + abs vy + abs vz

The key insights are:
1) The axes (x,y,z) are totally independent. So it suffices to find the period for each
   axis separately. Then the answer is the lcm of these.
2) Each axis will repeat "relatively quickly" (fast enough to brute force)
3) Since each state has a unique parent, the first repeat must be a repeat of state 0
   This could not be possible: 0,3,6,27,3,6,27,3,6,27,... because parent of 3 is unique
*****************************************************************************************/

#include <iostream>
#include <vector>
#include <cstdio>  // printf
#include <cmath>
#include <climits>

using namespace std;

using ll = long long;

class Moon {
public:

    // Constructor
    Moon(int x, int y, int z, int vx, int vy, int vz) :
        x(x), y(y), z(z), vx(vx), vy(vy), vz(vz) {}

    // getters (used if implementing comparison operator as non-friend function and
    // for equalX, equalY, equalZ functions)
    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }
    int getVx() const { return vx; }
    int getVy() const { return vy; }
    int getVz() const { return vz; }

    // To apply gravity, consider every pair of moons. On each axis (x, y, and z),
    // the velocity of each moon changes by exactly +1 (if x<neighbour.x), -1
    // (if x<neighbour.x).
    // If the positions on a given axis are the same, the velocity does not change
    void updateVelocity(const Moon& neighbour) {
        int xdiff = x - neighbour.x; // x - neighbour.getX();
        int ydiff = y - neighbour.y;
        int zdiff = z - neighbour.z;
        if (xdiff > 0)
            vx -= 1;
        else if (xdiff < 0)
            vx += 1;

        if (ydiff > 0)
            vy -= 1;
        else if (ydiff < 0)
            vy += 1;

        if (zdiff > 0)
            vz -= 1;
        else if (zdiff < 0)
            vz += 1;
    }

    // Once all gravity has been applied, apply velocity: simply add the velocity
    // of each moon to its own position
    void updatePosition() {
        x += vx;
        y += vy;
        z += vz;
    }

    void printPosVel() {
        printf("pos=<x=%3d, y=%3d, z=%3d>, vel=<x=%3d, y=%3d, z=%3d>\n",
               x, y, z, vx, vy, vz);
    }

    // A moon's potential energy is the sum of the absolute values of its x, y,
    // and z position coordinates
    int calculatePotentialEnergy() {
       return abs(x) + abs(y) + abs(z);
    }

    // A moon's kinetic energy is the sum of the absolute values of its velocity
    // coordinates
    int calculateKineticEnergy() {
       return abs(vx) + abs(vy) + abs(vz);
    }

    // The total energy for a single moon is its potential energy multiplied
    // by its kinetic energy.
    int calculateTotalEnergy() {
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

// not used
// can implement as normal function, friend, or member function
// bool operator==(const Moon& lhs, const Moon& rhs) {
//     // friend can access private members
//     return lhs.getX()  == rhs.getX()  && lhs.getY()  == rhs.getY()  && lhs.getZ()  == rhs.getZ()  &&
//            lhs.getVx() == rhs.getVx() && lhs.getVy() == rhs.getVy() && lhs.getVz() == rhs.getVz();
// }

// check that all four moons are identical in X an Vx in moons and in moonsOrig
bool equalXall(const vector<Moon*>& moons, const vector<Moon*>& moonsOrig) {
    bool ret = true;
    int size = moons.size();
    for (int i = 0; i < size; ++i) {
        ret = ret && moons.at(i)->getX()  == moonsOrig.at(i)->getX()
                  && moons.at(i)->getVx() == moonsOrig.at(i)->getVx();
        if (!ret)
            break;
    }
    return ret;
}

// Y and Vy
bool equalYall(const vector<Moon*>& moons, const vector<Moon*>& moonsOrig) {
    bool ret = true;
    int size = moons.size();
    for (int i = 0; i < size; ++i) {
        ret = ret && moons.at(i)->getY()  == moonsOrig.at(i)->getY()
                  && moons.at(i)->getVy() == moonsOrig.at(i)->getVy();
        if (!ret)
            break;
    }
    return ret;
}

// Z and Vz
bool equalZall(const vector<Moon*>& moons, const vector<Moon*>& moonsOrig) {
    bool ret = true;
    int size = moons.size();
    for (int i = 0; i < size; ++i) {
        ret = ret && moons.at(i)->getZ()  == moonsOrig.at(i)->getZ()
                  && moons.at(i)->getVz() == moonsOrig.at(i)->getVz();
        if (!ret)
            break;
    }
    return ret;
}

// declared, used by checkPart
void printAllStates(const vector<Moon*>& moons);

// check all moons per axis (X, Y, Z) using equalXall, equalYall, or equalZall
// set foundDir to true and countDir to count when all X and Vx become true
// (or Y/Vy, Z/Vz if checking y or z)
// Not really necessary to use this, but originally I made 12 checks (4 moons X 3 directions)
void checkDir(const vector<Moon*>& moons, const vector<Moon*>& moonsOrig,
               bool& foundDir, ll& countDir, const ll& countall, const string& part,
               bool (*equalDir)(const vector<Moon*>& moons,
                                const vector<Moon*>& moonsOrig)) {
    if (equalDir(moons, moonsOrig)) {
        if (!foundDir) {  // only need first time compp is true
            countDir = countall;
            foundDir = true;
            cout << "got " << part << " after count " << countDir + 1 << endl;
            printAllStates(moons);
        }
    }
}

void printAllStates(const vector<Moon*>& moons) {
    for (const auto moon_ptr: moons)
        moon_ptr->printPosVel();
    cout << endl;
}

// copied from https://www.geeksforgeeks.org/lcm-of-given-array-elements/
// Least common multiple of given array elements
// Utility function to find  GCD of 'a' and 'b'
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Returns least common multiple of array elements
//ll findlcm(ll arr[], int n)
ll findlcm(ll (&arr)[3], int n)
{
    // Initialize result
    ll ans = arr[0];

    // ans contains LCM of arr[0], ..arr[i]
    // after i'th iteration,
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));

    return ans;
}

int main() {

    Moon Io       (  1, -4,   3, 0, 0, 0);
    Moon Europa   (-14,  9,  -4, 0, 0, 0);
    Moon Ganymede ( -4, -6,   7, 0, 0, 0);
    Moon Callisto (  6, -9, -11, 0, 0, 0);

    // note: probably better to use vector<Moon>
    vector<Moon*> moons;
    vector<Moon*> moons_initial;

    moons.push_back(&Io);
    moons.push_back(&Europa);
    moons.push_back(&Ganymede);
    moons.push_back(&Callisto);

    // create a copy of the initial state
    Moon Io1 = Io;
    Moon Europa1 = Europa;
    Moon Ganymede1 = Ganymede;
    Moon Callisto1 = Callisto;

    moons_initial.push_back(&Io1);
    moons_initial.push_back(&Europa1);
    moons_initial.push_back(&Ganymede1);
    moons_initial.push_back(&Callisto1);

    cout << endl << "after 0 steps the position and velocities are:" << endl;
    for (const auto moon_ptr: moons)
        moon_ptr->printPosVel();
    cout << endl;

    ll countX = 0, countY = 0, countZ = 0;
    bool foundX = false, foundY = false, foundZ = false;

    for (ll count = 0;; ++count) {

        // first update the velocity of every moon by applying gravity
        for (auto it1 = moons.begin(); it1 != moons.end(); ++it1)
            for (auto it2 = moons.begin(); it2 != moons.end(); ++it2)
                if (it2 != it1)
                    (*it1)->updateVelocity(**it2);

        // Once all gravity has been applied, update position by applying velocity
        for (auto& moon : moons)
            moon->updatePosition();

          // naive approach, too slow
//        if (Io == Io1 && Europa == Europa1 && Ganymede == Ganymede1
//            && Callisto == Callisto1) {
//            cout << "found a state that matches the initial state! count is " << count + 1 << endl;
//            break;
//        }

        // all directions are independent, so can check them independently and find
        // the least common multiple
        // must check both position and speed... only one is not a multiple of total count
        checkDir(moons, moons_initial, foundX, countX, count, "X and Vx", equalXall);
        checkDir(moons, moons_initial, foundY, countY, count, "Y and Vy", equalYall);
        checkDir(moons, moons_initial, foundZ, countZ, count, "Z and Vz", equalZall);

        if (foundX && foundY && foundZ) {
            cout << "all directions found, count is " << count + 1 << endl;
            break;
        }
    }

    cout << "The positions and velocities are:" << endl;
    printAllStates(moons);

    cout << "All counts x, y, z:" << endl
         << countX + 1 << ", " << countY + 1 << ", " << countZ + 1 << endl;

    const int ncounts = 3;

    ll counts[ncounts] = {countX + 1, countY + 1, countZ + 1};
    int size = sizeof (counts) / sizeof (counts[0]);

    // 543673227860472 (5.43e14)
    cout << "It takes " << findlcm(counts, size) << " steps to reach the first "
            "state that exactly matches a previous state" << endl;


    return 0;
}
