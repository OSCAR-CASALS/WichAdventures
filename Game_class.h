#include "Functions.h"
#include "GameStateMachine.h"
#include "Stages.h"

class Game{
    private:
        static Game* s_pInstance;
        //typedef Game TheGame;
    protected:
        //vector<GameObject *> m_gameobjects;
        GameStageMachine* m_pgameStatemachine;
    public:
        static Game* Instance(){
            if (s_pInstance == 0){
                s_pInstance = new Game();
                return s_pInstance;
            }
            return s_pInstance;
        }
        void start();
        void init();
        void update();
        void render();
        void end();
        void run();
        GameStageMachine* getStateMachine(){ return m_pgameStatemachine; }
};