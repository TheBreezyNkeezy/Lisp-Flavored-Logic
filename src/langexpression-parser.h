/**
 * File: sparser.h
 * --------------
 * This file acts as the interface to the S-expression parser module.
 */


#pragma once
#include <string>
#include "langexpressions.h"
#include "tokenscanner.h"

LangExpression *parseLangExp(SExpression *inputSExp);
