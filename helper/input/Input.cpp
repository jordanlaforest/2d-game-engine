#include <vector>
#include <unordered_map>
#include <iostream>
#include "Input.h"

namespace Input
{
  namespace
  {
    //"Enhanced" private members
    bool keys[NUM_KEYS];
    std::unordered_map<std::string, std::vector<int> > keyMap;
    void GLFWCALL setKey(int key, int action)
    {
      //std::cout << "Key " << (action ? "Pressed" : "Released") << ": " << key << "(" << static_cast<char>(key & 0xFF) << ")" << std::endl;
      keys[key] = static_cast<bool>(action);
    }
  }

  

  void initInput()
  {
    glfwSetKeyCallback(setKey);
  }

  bool getKeyState(std::string key)
  {
    auto it = keyMap.find(key);
    if(it != keyMap.end()){
      auto vecIt = it->second.begin();
      while(vecIt != it->second.end()){
        if(keys[*vecIt])
          return true;
        vecIt++;
      }
    }
    return false;
  }
  void addMapping(std::string name, int key)
  {
    auto it = keyMap.find(name);
    if(it == keyMap.end()){
      std::vector<int> keyVec;
      keyVec.push_back(key);
      keyMap.insert(std::make_pair(name, keyVec));
    }else{
      it->second.push_back(key);
    }
  }
}
