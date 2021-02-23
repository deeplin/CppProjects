#pragma once
#include "Command.h"
#include <iostream>
#include <vector>
using namespace std;
class MacroCommand :
    public Command
{
private:
	vector<Command*> commands;
public:
	void addCommand(Command* command) {
		commands.push_back(command);
	}
	virtual void execute() override {
		for (auto& c : commands) {
			c->execute();
		}
	}
};

