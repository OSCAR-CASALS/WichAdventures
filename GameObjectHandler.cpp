#include "GameObjectHandler.h"
#include<fstream>
//#include<nlohmann/json.hpp>

//using json = nlohmann::json;

void ObjectLayer::update(){
    // int i; i < GameObjectsVector.size(); i++
    if(!indexToRemove.empty()){
        sort(indexToRemove.begin(), indexToRemove.end(), greater<int>());
        for (auto &c : indexToRemove){
            GameObjectsVector.erase(GameObjectsVector.begin() + c);
        }
        indexToRemove.clear();
    }
    for(auto&Ob : GameObjectsVector){
        Ob->update();
    }
}

void ObjectLayer::draw(){
    for(auto&Ob : GameObjectsVector){
        Vector2D newPos = Ob->getRealPos() + Vector2D(offsetPosX, offsetPosY);
        Ob->setPosition(newPos.getX(), newPos.getY());
        Ob->draw();
    }
}