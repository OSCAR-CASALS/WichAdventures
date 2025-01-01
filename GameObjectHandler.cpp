#include "GameObjectHandler.h"
#include<fstream>
//#include<nlohmann/json.hpp>

//using json = nlohmann::json;

void ObjectLayer::update(){
    // int i; i < GameObjectsVector.size(); i++
    if(!indexToRemove.empty()){
        sort(indexToRemove.begin(), indexToRemove.end(), greater<int>());
        for (auto &c : indexToRemove){
            GameObjectsVector[c] = nullptr;
            //GameObjectsVector.erase(GameObjectsVector.begin() + rem);
        }

        GameObjectsVector.erase(
        remove_if(
            GameObjectsVector.begin(), 
            GameObjectsVector.end(),
            [](const std::unique_ptr<GameObject>& ptr) { return ptr == nullptr; }
        ), 
        GameObjectsVector.end()
        );

        indexToRemove.clear();
    }
    for(int g = 0; g < GameObjectsVector.size(); g++){
        GameObjectsVector[g]->update();
    }
}

void ObjectLayer::draw(){
    for(auto&Ob : GameObjectsVector){
        Vector2D newPos = Ob->getRealPos() + Vector2D(offsetPosX, offsetPosY);
        Ob->setPosition(newPos.getX(), newPos.getY());
        Ob->draw();
    }
}