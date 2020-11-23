/*
 * File: langexpression_parser.cpp
 * ----------------
 * This file implements the langexpression_parser.h interface.
 */


#include <iostream>
#include <string>
#include "error.h"
#include "linkedlist.h"
#include "langexpressions.h"
#include "langexpression-parser.h"
using namespace std;

static LangExpression *readLE(SExpression *inputSExp);
static LangExpression *readLEList(LinkedList<SExpression *> SExpList);
static bool operationIsNot(const string& operation);
static bool operationIsAnd(const string& operation);
static bool operationIsOr(const string& operation);
static bool operationIsImp(const string& operation);
static bool operationIsIff(const string& operation);
static bool operationIsSet(const string& operation);
static bool operationIsLet(const string& operation);

LangExpression *parseLangExp(SExpression *inputSExp) {
    LangExpression *lexp = readLE(inputSExp);
    return lexp;
}

LangExpression *readLE(SExpression *inputSExp) {
    LangExpression *lexp = new NullExp();
    if (inputSExp->getType() == SExpressionType::TRUE) return new BoolExp(true);
    if (inputSExp->getType() == SExpressionType::FALSE) return new BoolExp(false);
    if (inputSExp->getType() == SExpressionType::CONSTANT) {
        if (inputSExp->getConstantValue() == 1.0) return new BoolExp(true);
        if (inputSExp->getConstantValue() == 0.0) return new BoolExp(false);
    }
    if (inputSExp->getType() == SExpressionType::SYMBOL) return new RefExp(inputSExp->getSymbolName());
    if (inputSExp->getType() == SExpressionType::CONS) return readLEList(inputSExp->toList());
    return lexp;
}

LangExpression *readLEList(LinkedList<SExpression *> SExpList) {
    LangExpression *lexp = new NullExp();
    SExpression *firstTerm = SExpList.removeFront();
    if (firstTerm->getType() == SExpressionType::CONS) {
        if (SExpList.isEmpty()) return readLE(firstTerm);
        string operation;
        LinkedList<SExpression *> firstTermComponents = firstTerm->toList();
        for (const SExpression *component : firstTermComponents) {
            if (component->getType() != SExpressionType::SYMBOL)
                error("LangExpression PARSE ERROR >> Invalid operator component");
            operation += component->getSymbolName();
        }
        int numTerms = SExpList.size();
        if (numTerms == 1) {
            SExpression *SExpToNegate = SExpList.removeFront();
            if (operationIsNot(operation)) return new NotExp(readLE(SExpToNegate));
            else error("LangExpression PARSE ERROR >> Incorrect number of terms provided for operation " + operation);
        }
        else if (numTerms == 2) {
            SExpression *SExpFirst = SExpList.removeFront();
            SExpression *SExpSecond = SExpList.removeFront();
            if (operationIsAnd(operation)) return new AndExp(readLE(SExpFirst), readLE(SExpSecond));
            else if (operationIsOr(operation)) return new OrExp(readLE(SExpFirst), readLE(SExpSecond));
            else if (operationIsImp(operation)) return new ImpExp(readLE(SExpFirst), readLE(SExpSecond));
            else if (operationIsIff(operation)) return new IffExp(readLE(SExpFirst), readLE(SExpSecond));
            else if (operationIsSet(operation) && SExpFirst->getType() == SExpressionType::SYMBOL)
                return new SetExp(SExpFirst->getSymbolName(), readLE(SExpSecond));
            else error("LangExpression PARSE ERROR >> Incorrect number of terms provided for operation " + operation);
        }
        else if (numTerms == 3) {
            SExpression *SExpVar = SExpList.removeFront();
            SExpression *SExpBind = SExpList.removeFront();
            SExpression *SExpBody = SExpList.removeFront();
            if (operationIsLet(operation) && SExpVar->getType() == SExpressionType::SYMBOL)
                return new LetExp(SExpVar->getSymbolName(), readLE(SExpBind), readLE(SExpBody));
            else error("LangExpression PARSE ERROR >> Incorrect number of terms provided for operation " + operation);
        }
        else error("LangExpression PARSE ERROR >> Unknown operator provided: " + operation);
    }
    return lexp;
}

bool operationIsNot(const string& operation) {
    return operation == "not" ||
            operation == "N" ||
            operation == "~" ||
            operation == "[-]" ||
            operation == "!";
}

bool operationIsAnd(const string& operation) {
    return operation == "and" ||
            operation == "K" ||
            operation == "&" ||
            operation == "[*]";
}

bool operationIsOr(const string& operation) {
    return operation == "or" ||
            operation == "A" ||
            operation == "||" ||
            operation == "[+]";
}

bool operationIsImp(const string& operation) {
    return operation == "implies" ||
            operation == "imp" ||
            operation == "C" ||
            operation == "=>";
}

bool operationIsIff(const string& operation) {
    return operation == "iff" ||
            operation == "E" ||
            operation == "<=>";
}

bool operationIsSet(const string& operation) {
    return operation == "set";
}

bool operationIsLet(const string& operation) {
    return operation == "let";
}
