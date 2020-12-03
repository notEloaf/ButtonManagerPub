#include "ButtonManager.hpp"

ButtonManager::ButtonManager(){
    std::string s = "config.txt";
    _parsed = JsonParser(s);
    for(int i = 0; i < _parsed.ids.size(); i++){
        buttons.push_back(Button(_parsed.ids[i]));
    }

    setupButtons();
    _eventHandler = std::thread(&ButtonManager::waitForButtons, this);
}

void ButtonManager::setupButtons(){
    for(int i = 0; i < _parsed.behaviors.size(); i++){
        std::string type = _parsed.behaviors[i].type;

        int index = findIndex(_parsed.behaviors[i].id);

        if(index == -1){
            std::cerr << "No button with id: " << index << std::endl;
        }
    
        if(type.compare("timedClick") == 0){
            buttons[index]._shortClick = std::stoi(_parsed.behaviors[i].clickDuration);
            buttons[index]._shortPressOp = _parsed.behaviors[i].shortOp;
            buttons[index]._longPressOp = _parsed.behaviors[i].longOp;
            buttons[index]._timedClickEnabled = true;
        }else if(type.compare("buttonDown") == 0){
            buttons[index]._downPressOp = _parsed.behaviors[i].op;
            buttons[index]._buttonDownEnabled = true;
        }else if(type.compare("buttonUp") == 0){
            buttons[index]._upPressOp = _parsed.behaviors[i].op;
            buttons[index]._buttonUpEnabled = true;
        }else if(type.compare("clicked") == 0){
            buttons[index]._clickedOp = _parsed.behaviors[i].op;
            buttons[index]._clickedEnabled = true;
        }else if(type.compare("held") == 0){
            buttons[index]._heldOp = _parsed.behaviors[i].op;
            buttons[index]._heldDuration = std::stoi(_parsed.behaviors[i].downDuration);
            buttons[index]._heldEnabled = true;
        }
    }
}

int ButtonManager::findIndex(std::string id){
    for(int i = 0; i < buttons.size(); i++){
        if(id == buttons[i]._id){
            return i;
        }
    }
    return -1;
}

void ButtonManager::buttonDown(std::string id){

    int index = findIndex(id);

    if(index != -1){
        buttons[index]._state = Button::STATE::isDOWN;
        buttons[index].buttonDown();
        _semSignal.notify();
    }else{
        std::cerr << "No button with id: " << index << std::endl;
    }

}

void ButtonManager::buttonUp(std::string id){


    int index = findIndex(id);

    if(index != -1){
        buttons[index]._state = Button::STATE::isUP;
        _semSignal.notify();
    }else{

    }
}

void ButtonManager::waitForButtons(){
    bool timingNeeded = false;
    while(running){
        if(timingNeeded)
        {
            _semSignal.waitFor(10);
        }
        else
        {
            _semSignal.wait();
        }

        if(!running)
        {
            break;
        }
    
        _mtxButtonDataLock.lock();
        {
            for(int i = 0; running && i < buttons.size(); i++){
                
                if(buttons[i]._state == Button::STATE::isDOWN){
                    //Button down
                    if(buttons[i]._buttonDownEnabled){
                        _IButtonNotification->recallFunc(buttons[i]._downPressOp);
                        buttons[i]._state = Button::STATE::isPending;
                    }

                    //Held event
                    if(buttons[i]._heldEnabled){
                        timingNeeded = true;
                        
                        float durationDown = buttons[i].timeSincePressed();
                        
                        if(durationDown > buttons[i]._heldDuration){
                            _IButtonNotification->recallFunc(buttons[i]._heldOp);
                            buttons[i]._state = Button::STATE::isPending;
                            buttons[i]._locked = true;
                            continue;
                        }
                    }
                }

                if(buttons[i]._state == Button::STATE::isUP && !buttons[i]._locked){
                    //Button Up Event
                    if(buttons[i]._buttonUpEnabled){
                        _IButtonNotification->recallFunc(buttons[i]._upPressOp);
                    }

                    //Button Clicked Event
                    if(buttons[i]._clickedEnabled){
                        _IButtonNotification->recallFunc(buttons[i]._clickedOp);
                    }

                    //Timed button Event
                    if(buttons[i]._timedClickEnabled){

                        float durationDown = buttons[i].timeSincePressed();

                        if(durationDown <= buttons[i]._shortClick ){
                            _IButtonNotification->recallFunc(buttons[i]._shortPressOp);
                        }else if(durationDown > buttons[i]._shortClick && buttons[i]._timedClickEnabled){
                            _IButtonNotification->recallFunc(buttons[i]._longPressOp);
                        }
                    }

                    buttons[i]._state = Button::STATE::isPending;

                }else if(buttons[i]._state == Button::STATE::isUP && buttons[i]._locked){
                    //Resets button if held for this button has occured
                    buttons[i]._locked = false;
                    timingNeeded = false;
                    buttons[i]._state = Button::STATE::isPending;
                }
            } 
        }
        _mtxButtonDataLock.unlock();
    }
}