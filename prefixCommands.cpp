#include "prefixCommands.h"

std::unordered_map<std::string, Command> commandsList;

ParsedCommand parseCommand(const std::string& message) {
    ParsedCommand result;

    // Check if the message starts with the prefix
    if (message.rfind(prefix, 0) != 0)
        return result; // empty name = not a command

    // Remove prefix
    std::string withoutPrefix = message.substr(prefix.size());

    // Split by spaces
    std::istringstream iss(withoutPrefix);
    iss >> result.name; // first word = command name

    std::string arg;
    while (iss >> arg)
        result.args.push_back(arg); // remaining words = parameters

    return result;
}

Command Command::addParam(const commandParam param) {
    params.push_back(param);
    return *this;
}

bool addCommand(const Command cmd) {
    if (commandsList.find(cmd.name) != commandsList.end()) {
        return false; 
    }
    commandsList.emplace(cmd.name, cmd);
    return true;
}

bool bulkAddCommands(const std::unordered_set<Command, CommandHash> cmds) {
    for (const auto& cmd : cmds) {
        if (!addCommand(cmd)) {
            return false; // If any command fails to add, return false
        }
    }
    return true;
}

int checkCommandValidity(const ParsedCommand& parsed) {
    size_t requiredCount = 0;

	auto it = commandsList.find(parsed.name); // Only one commandsList, no need to pass it as a parameter

    if (it == commandsList.end())
		return -1; // Command not found
    // Count how many required parameters the command has
    for (const auto& c : it->second.params) { // Realistically, average-worst case time complexity is O(n+3), most commands don't exceed this many params
        if (c.required)
            requiredCount++;
    }

    // Must provide at least all required parameters
    if (parsed.args.size() < requiredCount)
        return requiredCount-parsed.args.size();

    // Optionally, you can check that parsed.args.size() <= command.params.size()
    if (parsed.args.size() > it->second.params.size())
        return -1;

    return 0;
}

Command getCommand(const std::string& name) {
    auto it = commandsList.find(name);
    if (it != commandsList.end()) {
        return it->second;
    }
    else {
        return Command({"", "", dpp::p_send_messages});
    }
}

std::string getVal(Command cmd, std::string name) {
    auto it = std::find_if(cmd.params.begin(), cmd.params.end(),
        [&](const commandParam& p) {
            return p.name == name;
        }
    );

    if (it != cmd.params.end()) {
        return it->val; // found
    }
    return ""; // not found
}
