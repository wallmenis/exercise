#ifndef TUI_H
#define TUI_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "control_classes.h"

class TUI {
public:
    TUI();
    ~TUI();
    static std::vector<std::string> pageize(std::string contString, int pageLines);
    static std::string displayAndSelectPage(std::vector<std::string> pages);
};



#endif