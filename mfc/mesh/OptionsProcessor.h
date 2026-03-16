//
// Created by webdev on 21.09.2018.
//

#ifndef MFC_OPTIONSPROCESSOR_H
#define MFC_OPTIONSPROCESSOR_H

#include "options.h"
#include "OptionParser.h"
#include "../nlohmann/json.hpp"
#include <iostream>


using json = nlohmann::json;


class OptionsProcessor
{
public:
	OptionsProcessor() = default;
	void Process(Options &, json &);
};


#endif //MFC_OPTIONSPROCESSOR_H
