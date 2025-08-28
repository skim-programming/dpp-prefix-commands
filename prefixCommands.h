#include <dpp/dpp.h>
#include <unordered_map>

struct commandParam {
    std::string name;
    bool required;
    std::string val = "";

};

struct Command {
    std::string name;
    std::string description;
    int perm;
    std::vector<commandParam> params;

    Command(std::string n, std::string d, int p)
        : name(std::move(n)), description(std::move(d)), perm(p) {
    }

    Command addParam(const commandParam param);
    bool operator==(const Command& other) const {
        return name == other.name; // uniqueness by name
    }
};

// Hash functor
struct CommandHash {
    size_t operator()(const Command& c) const noexcept {
        return std::hash<std::string>()(c.name);
    }
};

extern std::unordered_map<std::string, Command> commandsList;

struct ParsedCommand {
    std::string name;
    std::vector<std::string> args;
};

bool addCommand(const Command cmd);

ParsedCommand parseCommand(const std::string& message);

bool bulkAddCommands(const std::unordered_set<Command, CommandHash> cmds);

int checkCommandValidity(const ParsedCommand& parsed);

Command getCommand(const std::string& name);

std::string getVal(Command cmd, std::string name);
