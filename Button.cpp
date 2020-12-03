#include "Button.h"

Button::Button(std::string id){
    _id = id;
    _timeLastPressed = -500;
    
    _shortClick = 1000;
    _heldDuration = 3000;

    _timedClickEnabled = false;
    _buttonDownEnabled = false;
    _buttonUpEnabled = false;
    _clickedEnabled = false;
    _heldEnabled = false;
    _locked = false;
    

    _shortPressOp = "";
    _longPressOp = "";
    _downPressOp = "";
    _upPressOp = "";
    _clickedOp = "";
    _heldOp = "";

    _state = isPending;
}

void Button::buttonDown(){
    _timeLastPressed = static_cast<uint64_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())
                                     .time_since_epoch()
                                     .count());
}

uint64_t Button::timeSincePressed(){
    if(_timeLastPressed < 0){
        return -1;
    }
    
    uint64_t now = static_cast<uint64_t>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())
                                     .time_since_epoch()
                                     .count());
    uint64_t td = now - _timeLastPressed;
    return now - _timeLastPressed;
}

