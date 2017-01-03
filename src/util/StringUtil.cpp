//
// Created by jazula on 1/3/17.
//

#include "StringUtil.hpp"

string StringUtil::time_to_string(int current_time)
{
    std::stringstream health_min_ss;
    std::stringstream health_sec_ss;

    int seconds = current_time % 60;
    int minutes = current_time / 60;
    health_min_ss << std::setfill('0') << std::setw(2) << minutes; // 2 is size of total health (string size)
    health_sec_ss << std::setfill('0') << std::setw(2) << seconds; // 2 is size of total health (string size)<

    string min;
    string sec;
    string output;
    health_min_ss >> min;
    health_sec_ss >> sec;
    output = min + " : " + sec;
    return output;
}