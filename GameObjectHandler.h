#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include "Vector.h"
#include "Functions.h"
#include "Objects.h"
#include <map>
#include <memory>
#include<algorithm>

class ObjectLayer{
    private:
        vector<unique_ptr<GameObject>> GameObjectsVector;
        vector<int> indexToRemove;
        float offsetPosX = 0;
        float offsetPosY = 0;
    public:
        vector<unique_ptr<GameObject>>& getVector(){
            return GameObjectsVector;
        }
        vector<int> getIndexToRemove(){
            return indexToRemove;
        }
        void setIndexToRemove(int i){
            indexToRemove.push_back(i);
        }
        void SetOffsetX(float x){
            offsetPosX = x;
        }
        void SetOffsetY(float y){
            offsetPosY = y;
        }
        void update();
        void draw();
        void AddObject(unique_ptr<GameObject> o){
            GameObjectsVector.emplace_back(move(o));
        }
        void Exit(){
            GameObjectsVector.clear();
        }
        int getSize(){
            return GameObjectsVector.size();
        }
};

#endif