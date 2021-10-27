#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

typedef struct Args {
    std::vector<std::string> flags;
    std::unordered_map<std::string, std::string> settings;
    std::vector<std::string> text;
} Args;

Args parseArgs(const std::vector<std::string>& input) {
    Args args;

    bool nextItemIsSetting = false;
    std::string settingName;

    for (auto item : input) {
        if (nextItemIsSetting) {
            args.settings[settingName] = item;
            nextItemIsSetting = false;
        }

        if (item.rfind("--", 0) == 0) {
            args.flags.push_back(item.substr(2));

        } else if (item.rfind("-", 0) == 0) {

            nextItemIsSetting = true;
            settingName = item.substr(1);
        } else {
            args.text.push_back(item);
        }
    }

    return args;
}