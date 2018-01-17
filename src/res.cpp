#include "res.h"

namespace res
{
	Resources ui;

	void load()
	{
		ui.loadXML("resources.xml");
	}

	void free()
	{
		ui.free();
	}
}