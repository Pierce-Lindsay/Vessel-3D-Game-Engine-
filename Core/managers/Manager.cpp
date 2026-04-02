#include "Manager.h"

using namespace ve;

Manager::Manager() {}

Manager::~Manager() 
{
	//if we havn't been shutdown, do it now
	if (!is_shutdown)
		shutDown();
}

void Manager::setType(const std::string& type)
{
	this->type = type;
}

const std::string& Manager::getType() const
{
	return type;
}

int Manager::startUp()
{
	//default startup succeeds every time
	is_started = true;
	return 0;
}

void Manager::shutDown()
{
	//default shutdown
	is_shutdown = true;
	is_started = false;
}

bool Manager::isStarted() const
{
	return is_started;
}
