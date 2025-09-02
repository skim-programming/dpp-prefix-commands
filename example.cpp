// example.cpp
// I wrote this in school so there might be errors, this is just rough code
#include "prefixCommands.h"
#include <string>

std::string prefix = "."

void addCommands(){
  addCommand(Command("Test", "Test command", dpp::p_send_messages).addParam("x"));
}

void setup_prefix_cmds(dpp::cluster& bot){
  bot.on_message_create([&bot](message_create_t event){
    if(event.msg.author.is_bot() || event.msg.content.empty() || event.msg.content.size() == prefix.size()){
      return;
    }
    ParsedCommand pcmd = parseCommand(event.msg.content());
    
  });
}
