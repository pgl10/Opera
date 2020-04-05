// eval.hpp
#ifndef EVAL_HPP
#define EVAL_HPP

#include <limits.h>
#include <string>

#include "listera.hpp"
#include "bigRa.hpp"
#include "utils.hpp"
#include "systm.hpp"

bool vval(std::string& name, bigRa& r);
bool eval(std::string ligne, bigRa& r);
bool rval(std::string& name, double& r);
bool nval(std::string& name, Integer& r);
bool ival(std::string& name, int& r);

#endif // EVAL_HPP
