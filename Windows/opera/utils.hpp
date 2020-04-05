// utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include <string>

void delcom(std::string& line);
void outspaces(std::string& line);
void firstspaces(std::string& line);
void premiermot(std::string& line);
bool isname0(const std::string& nom);
bool isname(const std::string& nom);
bool isnumb(const std::string& nbr);
bool isdecim(const std::string& nbr);
bool instr(std::string& cmde, std::string& ligne, std::string keyw);
bool keywd(std::string& line, std::string& ligne, std::string keyw);

#endif // UTILS_HPP
