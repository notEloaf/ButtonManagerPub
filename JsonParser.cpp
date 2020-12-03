#include "JsonParser.hpp"

JsonParser::JsonParser(std::string name){
    std::ifstream myFile;
    myFile.open(name);

    std::string line;

    bool isCreatingIDs = false;

    

    if(myFile.is_open())
    {
        while ( getline (myFile,line) )
        {
            if(line.compare("ButtonIds:")==0){
                isCreatingIDs = true;
                getline (myFile,line);
            }else if(line.compare("Behaviors:")==0){
                isCreatingIDs = false;
            }
            
            if(isCreatingIDs && line.compare("")!=0){
                ids.push_back(line);
            }else{

                while(getline(myFile, line)){
                    //cout << line << " -> " << line.compare("") << endl;
                    if(line.compare("START")==0){
                        behaviors.push_back(buttonBehavior());
                    }

                    std::stringstream tmp(line);
                    std::string segment;
                    std::vector<std::string> seglist;
                    while(getline(tmp,segment,':')){
                        seglist.push_back(segment);
                    }

                    if(seglist.size()<2){continue;}

                    if(seglist[0].compare("type")==0){
                        behaviors[behaviors.size()-1].type = seglist[1];
                    }else if(seglist[0].compare("buttonId")==0){
                        behaviors[behaviors.size()-1].id = seglist[1];
                    }else if(seglist[0].compare("shortOp")==0){
                        behaviors[behaviors.size()-1].shortOp = seglist[1];
                    }else if(seglist[0].compare("longOp")==0){
                        behaviors[behaviors.size()-1].longOp = seglist[1];
                    }else if(seglist[0].compare("clickDuration")==0){
                        behaviors[behaviors.size()-1].clickDuration = seglist[1];
                    }else if(seglist[0].compare("op")==0){
                        behaviors[behaviors.size()-1].op = seglist[1];
                    }else if(seglist[0].compare("downDuration")==0){
                        behaviors[behaviors.size()-1].downDuration = seglist[1];
                    }
                    
                }
            }
            
        }
    }

    myFile.close();
}
