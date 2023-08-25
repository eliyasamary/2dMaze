#pragma once

#include <string>
#include <map>
#include <memory>

#include "Command.h"
#include "Controller.h"
#include <iterator>

//class Controller;

using namespace std;

// CLI Invoker
class CLI {
private:
    istream& input;
    ostream& output;
    Controller* controller;

public:
    CLI(istream& in, ostream& out, Controller* c) : input(in), output(out) , controller(c) {}

    void list_commands() {
        //map<string, unique_ptr<Command>>::iterator it;
        map<string, Command*> list = controller->getCommands();
        map<string, Command*>::iterator it;
        output << "Available commands:" << endl;
        for(it = list.begin(); it != list.end(); ++it){
        //for (const pair<string, unique_ptr<Command>> pair : c.commands) {
            output << it->first << ": " << endl;
        }
    }

    void start() {
        map<string, Command*> list = controller->getCommands();
        while (true) {
            string user_input;
            output << "Enter a command (type 'menu' for available commands): ";
            //input >> user_input;
            getline(input, user_input);

            map<string, Command*>::iterator it;
            it = list.find(user_input);

            if (user_input == "exit") {
                output << "Exiting the CLI." << endl;
                break;
            }
            else if (user_input == "menu") {
                list_commands();
            }
            else if (it != list.end()) {
                list[user_input]->execute();
            }
            else {
                output << "Command not found. Type 'menu' to see available commands." << endl;
            }
        }
    }
};