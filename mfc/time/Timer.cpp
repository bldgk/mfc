//
// Created by webdev on 21.09.2018.
//

#include "Timer.h"


void Timer::Note()
{
	this->start = this->now();
}

timestamp Timer::now()
{
	return std::chrono::high_resolution_clock::now();
}

long long Timer::Duration()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(this->now() - this->start).count();
}

std::string Timer::Now()
{
	auto time_t = system_clock::to_time_t(system_clock::now());
	auto time = std::string(std::ctime(&time_t));
	return time.substr(0, time.length() - 1) + " ";
}