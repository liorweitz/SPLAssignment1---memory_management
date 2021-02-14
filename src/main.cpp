#include <iostream>
#include "Session.h"
#include "json.hpp"

using json=nlohmann::json;
using namespace std;

int main(int argc, char** argv){
    std::string path="/home/spl211/CLionProjects/Assignment1-11.11.20/config3.json";
    Session s=Session(path);
//    int arr1({1,2,3});

//    if(argc != 2){
//        cout << "usage cTrace <config_path>" << endl;
//        return 0;
//    }
//    Session sess(argv[1]);
//    sess.simulate();
    return 0;

}
