/*
 * File: sparser.cpp
 * ----------------
 * This file implements the sparser.h interface.
 */


#include <iostream>
#include <string>
#include "error.h"
#include "sexpressions.h"
#include "sexpression-parser.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

static bool isBalanced(const string& buffer);
static bool tokenIsParen(const string& token);
static bool isProperSyntax(const string& buffer);
static bool isOnlyOperators(const string& buffer);
static SExpression *readSE(TokenScanner& scanner);
static SExpression *readSEList(TokenScanner& scanner);
static SExpression *readST(const string& multTokenBuffer);
static SExpression *readST(TokenScanner& scanner, const string& token);

SExpression *parseOneSExp(TokenScanner& scanner) {
    SExpression *sexp = readSE(scanner);
    if (scanner.hasMoreTokens()) error("PARSE ERROR >> Unexpected token: \"" + scanner.nextToken() + "\"");
    return sexp;
}

SExpression *parseAllSExp(TokenScanner& scanner) {
    SExpression *sexp = readSEList(scanner);
    if (scanner.hasMoreTokens()) error("PARSE ERROR >> Unexpected token: \"" + scanner.nextToken() + "\"");
    return sexp;
}

bool isBalanced(const string& buffer) {
    int openParenValence = 0;
    for (const char& ch : buffer) {
        if (ch == '(') openParenValence++;
        if (ch == ')') openParenValence--;
    }
    return openParenValence == 0;
}

bool tokenIsParen(const string& token) {
    return token == "(" || token == ")";
}

bool isProperSyntax(const string& buffer) {
    // Check if there are parentheses surrounding the list given.
    for (const char& ch : buffer)
        if (ch == '(' || ch == ')') return true;
    // If there aren't, then assert that the buffer only consists of an atom.
    return !stringContains(buffer, " ");
}

bool isOnlyOperators(const string& buffer) {
    for (const char& ch : buffer)
        if (isalnum(ch) || tokenIsParen(charToString(ch))) return false;
    return buffer.size() > 1;
}

SExpression *readSE(TokenScanner& scanner) {
    SExpression *sexp = new SNil();
    if (!scanner.hasMoreTokens()) return sexp;
    string currentBuffer = scanner.getInput();
    if (!isProperSyntax(currentBuffer) || isOnlyOperators(currentBuffer))
        error("PARSE ERROR >> Invalid s-expression syntax.");
    if (!isBalanced(currentBuffer)) error("PARSE ERROR >> Unbalanced parentheses.");
    string token = scanner.nextToken();
    if (!tokenIsParen(token)) {
        if (!scanner.hasMoreTokens()) return readST(scanner, token);
        if (scanner.hasMoreTokens() && !stringContains(currentBuffer, " ")) {
            while (scanner.hasMoreTokens()) scanner.nextToken();
            return readST(currentBuffer);
        }
    }
    string SExpList;
    TokenScanner SExpListTokens;
    SExpListTokens.ignoreWhitespace();
    SExpListTokens.scanNumbers();
    while (scanner.hasMoreTokens()) {
        token = scanner.nextToken();
        if (token == ")" && !scanner.hasMoreTokens()) break;
        SExpList += token + " ";
    }
    SExpListTokens.setInput(trim(SExpList));
    return readSEList(SExpListTokens);
}

SExpression *readSEList(TokenScanner& scanner) {
    SExpression *sexp = new SNil();
    if (scanner.hasMoreTokens()) {
        TokenScanner CARToken;
        CARToken.ignoreWhitespace();
        CARToken.scanNumbers();
        string token = scanner.nextToken();
        if (token == "(") {
            string tokenList;
            int openInnerParens = 0;
            token = scanner.nextToken();
            while (true) {
                if (token == "(") openInnerParens++;
                if (token == ")") openInnerParens--;
                if (openInnerParens < 0) break;
                if (!scanner.hasMoreTokens()) error("SExpression PARSE ERROR >> Unbalanced parentheses.");
                tokenList += token + " ";
                token = scanner.nextToken();
            }
            CARToken.setInput(trim(tokenList));
            sexp = new SCons(readSEList(CARToken), readSEList(scanner));
        }
        else {
            CARToken.setInput(token);
            sexp = new SCons(readSE(CARToken), readSEList(scanner));
        }
    }
    return sexp;
}

SExpression *readST(const string& multTokenBuffer) {
    return new SSymbol(multTokenBuffer);
}

SExpression *readST(TokenScanner& scanner, const string& token) {
    TokenScanner::TokenType type = scanner.getTokenType(token);
    if (type == TokenScanner::NUMBER) return new SConstant(stringToReal(token));
    if (type == TokenScanner::WORD || type == TokenScanner::OPERATOR) {
        if (equalsIgnoreCase(token, "true") || equalsIgnoreCase(token, "T")) return new STrue();
        else if (equalsIgnoreCase(token, "false") || equalsIgnoreCase(token, "F")) return new SFalse();
        else return new SSymbol(token);
    }
    return new SNil();
}
