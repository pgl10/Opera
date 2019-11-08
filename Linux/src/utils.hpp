// utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include <string>

void espaces(std::string& line);
void outspaces(std::string& line);
void delcom(std::string& line);
bool isname(const char* nom);
bool isnumb(const char* nbr);
bool isdecim(const char* nbr);
bool instr(std::string cmde, std::string ligne, std::string keyw);
bool keywd(std::string line, std::string ligne, std::string keyw);

#endif // UTILS_HPP
