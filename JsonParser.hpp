#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>



class JsonParser{
public:
    JsonParser(){};
    JsonParser(std::string name);
    std::vector<std::string> ids;
    struct buttonBehavior{
        std::string type;
        std::string id;
        std::string shortOp;
        std::string longOp;
        std::string clickDuration;
        std::string op;
        std::string downDuration;
    };
    std::vector<buttonBehavior> behaviors;
private:
    std::string content; 
    bool lineContains(int pos, std::string substring);
    
};