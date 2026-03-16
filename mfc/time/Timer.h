//
// Created by webdev on 21.09.2018.
//

#ifndef MFC_TIME_H
#define MFC_TIME_H

#include <chrono>
#include <iostream>


using namespace std::chrono;
typedef std::chrono::high_resolution_clock::time_point timestamp;


class Timer
{
private:
	timestamp start;
	timestamp now();
public:
	void Note();
	long long Duration();
	std::string Now();
};


#endif //MFC_TIME_H
