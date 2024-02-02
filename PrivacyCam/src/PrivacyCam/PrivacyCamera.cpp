#include <iostream>

#include "Setting/Setting.h"
#include "Pipeline/Pipeline.h"

int main()
{
	try
	{
		const pricam::Setting config;
		pricam::Pipeline pipeline(config);
		pipeline.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
