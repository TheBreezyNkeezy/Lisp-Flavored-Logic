/**
 * File: sparser.h
 * --------------
 * This file acts as the interface to the S-expression parser module.
 */


#pragma once
#include <string>
#include "sexpressions.h"
#include "tokenscanner.h"

/**
 * Function: parseExp
 * Usage: SExpression *sexp = parseExp(scanner);
 * -------------------------------------------
 * Parses a complete S-expression from the specified TokenScanner object,
 * making sure that there are no tokens left in the scanner at the end.
 */

SExpression *parseOneSExp(TokenScanner& scanner);
SExpression *parseAllSExp(TokenScanner& scanner);
