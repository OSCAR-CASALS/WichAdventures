#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
#include<typeinfo>

using json = nlohmann::json;
using namespace std;

int main(){
    fstream file("Sprites/test.json");
    json data = json::parse(file);
    file.close();

    vector<int> d = data["layers"][0]["data"].get<vector<int>>();
    for(int value : d){
        cout << value << endl;
    }

    return 0;
}