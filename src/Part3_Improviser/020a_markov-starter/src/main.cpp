#include "../../MarkovModelCPP/src/MarkovManager.h"
#include <iostream>

int main()
{
    MarkovManager mm{};
    mm.putEvent("A");
    mm.putEvent("B");
    mm.putEvent("C#");
    mm.putEvent("A");
    mm.putEvent("B");
    mm.putEvent("A");
    mm.putEvent("C#");
    mm.putEvent("-");
    mm.putEvent("G#");
    std::cout << mm.getModelAsString() << std::endl;

    for (auto i = 0; i < 50; ++i)
    {
        state_single next = mm.getEvent();
        int order = mm.getOrderOfLastEvent();
        std::cout << "Next state " << next << " order " << order << std::endl;
    }

    return 0;
}