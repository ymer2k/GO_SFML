#pragma once
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0; // 0 means this method HAS to exist in subclasses of Command.

};

