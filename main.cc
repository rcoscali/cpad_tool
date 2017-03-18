/*
 * Copyright ©2017 NagraFrance
 */

#include "Cpad.h"

int
main(int argc, char **argv)
{
	cpad::Cpad cpad_tool(argc, argv);
	return (cpad_tool.do_tool_processing());
}
