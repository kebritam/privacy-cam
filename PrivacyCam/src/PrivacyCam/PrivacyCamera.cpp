#include <iostream>
#include "Setting/Setting.h"
#include "Pipeline/Pipeline.h"

#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>

int main()
{
	try
	{
		pricam::Setting config;
		pricam::Pipeline pipeline(config);
		pipeline.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
