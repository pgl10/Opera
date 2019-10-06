// utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

void espaces(std::string& line);
void outspaces(std::string& line);
void delcom(std::string& line);
bool isname(const char* nom);
bool isnumb(const char* nbr);
bool isdecim(const char* nbr);

#endif // UTILS_HPP