//
// Created by webdev on 21.09.2018.
//

#include "OptionsProcessor.h"


void OptionsProcessor::Process(Options &options, json &j_options)
{
	auto optionParser = std::make_unique<OptionParser>();
	optionParser->Parse(options, j_options);
}