#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>


#include "JsonParser.hpp"
#include "Button.h"
#include "Semaphore.h"


class ButtonManager{
public:
    JsonParser _parsed;
    std::vector<Button> buttons;

    ButtonManager();
    void setupButtons();
    void buttonDown(std::string id);
    void buttonUp(std::string id);
    void ButtonManager::waitForButtons();
    
    class IButtonNotification{
    public:
        virtual void recallFunc(std::string func) = 0;
    };

    virtual inline void setButtonInterface(IButtonNotification *notif){
        _IButtonNotification = notif;
    }
protected:
    IButtonNotification *_IButtonNotification;
private:
    int findIndex(std::string id);
    bool running = true;
    std::thread _eventHandler;
    Semaphore _semSignal;
    std::recursive_mutex  _mtxButtonDataLock;
};