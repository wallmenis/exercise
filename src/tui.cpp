#include "tui.h"

TUI::TUI() {}
TUI::~TUI() {}

std::vector<std::string> TUI::pageize(std::string contString, int pageLines)
{
    std::vector<std::string> pages;
    std::string currentPage;
    int lineCount = 0;

    for (int i = 0; i < contString.size(); ++i) {
        currentPage += contString[i];
        if (contString[i] == '\n') {
            lineCount++;
            if (lineCount >= pageLines) {
                pages.push_back(currentPage);
                currentPage.clear();
                lineCount = 0;
            }
        }
    }

    if (!currentPage.empty()) {
        pages.push_back(currentPage);
    }

    return pages;
}

std::string TUI::displayAndSelectPage(std::vector<std::string> pages)
{
    int pageIndex = 0;
    std::string input;
    input = "";
    while (input[0] != 'q')
    {
        std::cout << "Page " << (pageIndex + 1) << "/" << pages.size() << ":\n";
        std::cout << pages[pageIndex] << "\n";
        std::cout << "Enter 'n' for next page, 'p' for previous page, or 'q' or qStringToQuit to quit.\n";
        std::cout << "You may also enter /thingToSearchFor to search for a specific thing.\n";
        std::cin >> input;
        if (input == "n" && pageIndex < pages.size() - 1) {
            pageIndex++;
        } else if (input == "p" && pageIndex > 0) {
            pageIndex--;
        }
        else if (input[0] == '/') {
            std::string searchTerm = input.substr(1);
            bool found = false;
            for (int i = 0; i < pages.size(); ++i) {
                if (pages[i].find(searchTerm) != std::string::npos) {
                    pageIndex = i;
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cout << "Search term not found in any page.\n";
            }
        }
    }
    return input.substr(1);
}