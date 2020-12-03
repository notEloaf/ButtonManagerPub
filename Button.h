#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <chrono>
#include <cinttypes>

class Button{
public:
    
    std::string _id;
    uint64_t _timeLastPressed;
    

    Button(std::string id);
    uint64_t timeSincePressed();
    void buttonDown();

    float _shortClick;
    int _heldDuration;

    bool _locked;
    enum STATE{
        isDOWN,
        isUP,
        isPending
    };

    STATE _state;

    bool _timedClickEnabled;
    bool _buttonDownEnabled;
    bool _buttonUpEnabled;
    bool _clickedEnabled;
    bool _heldEnabled;

    std::string _shortPressOp;
    std::string _longPressOp;
    std::string _downPressOp;
    std::string _upPressOp;
    std::string _clickedOp;
    std::string _heldOp;
};


#endif