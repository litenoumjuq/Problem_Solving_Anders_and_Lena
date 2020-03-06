#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;


class Moon{
public:
    std::string name;
    int position_x;
    int position_y;
    int position_z;
    int velocity_x;
    int velocity_y;
    int velocity_z;

    Moon(std::string aName, int aPosition_x, int aPosition_y, int aPosition_z, int aVelocity_x, int aVelocity_y, int aVelocity_z){
        name = aName;
        position_x = aPosition_x;
        position_y = aPosition_y;
        position_z = aPosition_z;
        velocity_x = aVelocity_x;
        velocity_y = aVelocity_y;
        velocity_z = aVelocity_z;
    }

};




std::vector<std::string> getFileContent(std::string fileName, std::vector<std::string> indata)
{
    std::string str;

    std::ifstream in(fileName.c_str());

    if(!in)
    {
        std::cerr << "Cannot open the file: " << fileName << std::endl;
    };

    while(std::getline(in, str))
    {
        indata.push_back(str);
    }

    in.close();
    return indata;
}

void printIndata(std::vector<std::string> indata){
    std::cout << "Indata is: \n" << indata[0] << '\n';
    std::cout << indata[1] << '\n' << indata[2] << '\n' << indata[3] << '\n';

}

int main()
{
    std::vector<std::string> indata;
    indata = getFileContent("Input_day12.txt", indata);
    printIndata(indata);

    Moon io("io", 3, 2, -6, 0, 0, 0);
    //Moon ganymede("ganymede", -13, 18, 10, 0, 0, 0);
    //Moon callisto("callisto", -8, -1, 13, 0, 0, 0);
    //Moon europa("europa", 5, 10, 4, 0, 0, 0);

    return 0;
}
