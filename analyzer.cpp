#include <iostream>
#include "StringData.h"

int linearSearch(std::vector<std::string> &container, std::string &element) {
    for (int i = 0; i < container.size(); i++) {
        if (element == container[i]) return i;
    }
    return -1;
}

int binarySearch(std::vector<std::string> &container, std::string &element) {
    int left = 0;
    int right = container.size() - 1;
    if (right < 0) return -1;
    int index;
    std::string cmp_element;
    while (right > left) {
        index = (int) ((left + right) / 2);
        cmp_element = container[index];
        if (element == cmp_element) return index;
        if (element.compare(cmp_element) < 0) right = index - 1;
        else left = index + 1;
    }
    if (element == container[left]) return left;
    return -1;
}

inline int timeSearch(
    std::vector<std::string> &container,
    std::string &element,
    long long &timeTaken,
    int (*searchFunc)(std::vector<std::string>&, std::string&)
) {
    long long initialTime = systemTimeNanoseconds();  // not as accurate as other clocks, but it was provided to me so i'm using this one
    int foundIndex = searchFunc(container, element);
    timeTaken = systemTimeNanoseconds() - initialTime;
    return foundIndex;
}

int main(void) {
    std::vector<std::string> &data = getStringData();
    long long timeTaken = -1;
    std::vector<std::string> indices = {"not_here", "mzzzz", "aaaaa"};
    for (std::string &str : indices) {
        std::cout << "Linear search for '" << str << "':\n"
                  << "\tindex found: " << timeSearch(data, str, timeTaken, linearSearch) << "\n"
                  << "\ttime taken: " << timeTaken << std::endl;
        std::cout << "Binary search for '" << str << "':\n"
                << "\tindex found: " << timeSearch(data, str, timeTaken, binarySearch) << "\n"
                << "\ttime taken: " << timeTaken << std::endl;
    }
}
