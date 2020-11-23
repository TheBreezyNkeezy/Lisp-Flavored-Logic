/**
 * File: sexpressions.cpp
 * -------------
 * This file implements the sexpressions.h interface.
 */

#include <string>
#include "sexpressions.h"
#include "strlib.h"
#include "error.h"
using namespace std;

SExpression::SExpression() {
    /* Empty */
}

SExpression::~SExpression() {
    /* Empty */
}

double SExpression::getConstantValue() const {
    error("getConstantValue: Illegal S-expression type.");
    return 0.0;
}

string SExpression::getSymbolName() const {
    error("getSymbolName: Illegal S-expression type.");
    return "";
}

SExpression *SExpression::getCAR() const {
    error("getCAR: Illegal S-expression type.");
    return nullptr;
}

SExpression *SExpression::getCDR() const {
    error("getCAR: Illegal S-expression type.");
    return nullptr;
}

/**
 * Implementation notes: SConstant
 * -------------------------------
 * TODO
 */

SConstant::SConstant(const double& value) {
    this->value = value;
}

string SConstant::toString() const {
    return "SConstant(" + realToString(value) + ")";
}

SExpressionType SConstant::getType() const {
    return CONSTANT;
}

LinkedList<SExpression *> SConstant::toList() const {
    error("toList: Inconvertible type to list form.");
    return LinkedList<SExpression *>();
}

bool SConstant::isList() const {
    return false;
}

double SConstant::getConstantValue() const {
    return value;
}

/**
 * Implementation notes: SSymbol
 * -------------------------------
 * TODO
 */

SSymbol::SSymbol(const string& name) {
    this->name = name;
}

string SSymbol::toString() const {
    return "SSymbol(" + name + ")";
}

SExpressionType SSymbol::getType() const {
    return SYMBOL;
}

LinkedList<SExpression *> SSymbol::toList() const {
    error("toList: Inconvertible type to list form.");
    return LinkedList<SExpression *>();
}

bool SSymbol::isList() const {
    return false;
}

string SSymbol::getSymbolName() const {
    return name;
}

/**
 * Implementation notes: STrue
 * -------------------------------
 * TODO
 */

STrue::STrue() {
    /* Empty */
}

string STrue::toString() const {
    return "STrue()";
}

SExpressionType STrue::getType() const {
    return TRUE;
}

LinkedList<SExpression *> STrue::toList() const {
    error("toList: Inconvertible type to list form.");
    return LinkedList<SExpression *>();
}

bool STrue::isList() const {
    return false;
}

/**
 * Implementation notes: SFalse
 * -------------------------------
 * TODO
 */

SFalse::SFalse() {
    /* Empty */
}

string SFalse::toString() const {
    return "SFalse()";
}

SExpressionType SFalse::getType() const {
    return FALSE;
}

LinkedList<SExpression *> SFalse::toList() const {
    error("toList: Inconvertible type to list form.");
    return LinkedList<SExpression *>();
}

bool SFalse::isList() const {
    return false;
}

/**
 * Implementation notes: SCons
 * -------------------------------
 * TODO
 */

SCons::SCons(SExpression *car, SExpression *cdr) {
    this->car = car;
    this->cdr = cdr;
}

SCons::~SCons() {
    delete car;
    delete cdr;
}

string SCons::toString() const {
    string stringifiedList;
    LinkedList<SExpression *> expressionList = toList();
    for (const SExpression *exp : expressionList) stringifiedList += exp->toString() + " ";
    return "SCons(" + trimEnd(stringifiedList) + ")";
}

SExpressionType SCons::getType() const {
    return CONS;
}

LinkedList<SExpression *> SCons::toList() const {
    LinkedList<SExpression *> returnList;
    returnList.add(car);
    returnList.addAll(cdr->toList());
    return returnList;
}

bool SCons::isList() const {
    return true;
}

SExpression *SCons::getCAR() const {
    return car;
}

SExpression *SCons::getCDR() const {
    return cdr;
}

/**
 * Implementation notes: SNil
 * -------------------------------
 * TODO
 */

SNil::SNil() {
    /* Empty */
}

string SNil::toString() const {
    return "SNil()";
}

SExpressionType SNil::getType() const {
    return NIL;
}

LinkedList<SExpression *> SNil::toList() const {
    return LinkedList<SExpression *>();
}

bool SNil::isList() const {
    return true;
}
