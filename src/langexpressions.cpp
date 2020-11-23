/**
 * File: langexpressions.cpp
 * -------------
 * This file implements the langexpressions.h interface.
 */

#include <string>
#include "langexpressions.h"
#include "strlib.h"
#include "error.h"
using namespace std;

/**
 * Implementation notes: LangExpression
 * -------------------------------
 * TODO
 */

LangExpression::LangExpression() {
    /* Empty */
}

LangExpression::~LangExpression() {
    /* Empty */
}

/**
 * Implementation notes: RefExp
 * -------------------------------
 * TODO
 */

RefExp::RefExp(const string& name) {
    this->name = name;
}

string RefExp::toString() const {
    return "RefExp(" + name + ")";
}

LangExpressionType RefExp::getType() const {
    return LangExpressionType::RefEXP;
}

bool RefExp::eval(LangEvaluationContext& context) const {
    if (!context.isDefined(name)) error("EVALUATION ERROR >> undefined symbol: " + name);
    return context.getValue(name);
}



/**
 * Implementation notes: BoolExp
 * -------------------------------
 * TODO
 */

BoolExp::BoolExp(const bool& value) {
    this->value = value;
}

string BoolExp::toString() const {
    return "BoolExp(" + boolToString(value) + ")";
}

LangExpressionType BoolExp::getType() const {
    return LangExpressionType::BoolEXP;
}

bool BoolExp::eval(LangEvaluationContext& context) const {
    return value;
}

/**
 * Implementation notes: NotExp
 * -------------------------------
 * TODO
 */

NotExp::NotExp(LangExpression *toNegate) {
    this->toNegate = toNegate;
}

NotExp::~NotExp() {
    delete toNegate;
}

string NotExp::toString() const {
    return "NotExp(" + toNegate->toString() + ")";
}

LangExpressionType NotExp::getType() const {
    return LangExpressionType::NotEXP;
}

bool NotExp::eval(LangEvaluationContext& context) const {
    return !(toNegate->eval(context));
}

/**
 * Implementation notes: AndExp
 * -------------------------------
 * TODO
 */

AndExp::AndExp(LangExpression *first, LangExpression *second) {
    this->first = first;
    this->second = second;
}

AndExp::~AndExp() {
    delete first;
    delete second;
}

string AndExp::toString() const {
    return "AndExp(" + first->toString() + ", " + second->toString() + ")";
}

LangExpressionType AndExp::getType() const {
    return LangExpressionType::AndEXP;
}

bool AndExp::eval(LangEvaluationContext& context) const {
    bool firstValue = first->eval(context);
    bool secondValue = second->eval(context);
    return firstValue && secondValue;
}

/**
 * Implementation notes: OrExp
 * -------------------------------
 * TODO
 */

OrExp::OrExp(LangExpression *first, LangExpression *second) {
    this->first = first;
    this->second = second;
}

OrExp::~OrExp() {
    delete first;
    delete second;
}

string OrExp::toString() const {
    return "OrExp(" + first->toString() + ", " + second->toString() + ")";
}

LangExpressionType OrExp::getType() const {
    return LangExpressionType::OrEXP;
}

bool OrExp::eval(LangEvaluationContext& context) const {
    bool firstValue = first->eval(context);
    bool secondValue = second->eval(context);
    return firstValue || secondValue;
}

/**
 * Implementation notes: ImpExp
 * -------------------------------
 * TODO
 */

ImpExp::ImpExp(LangExpression *first, LangExpression *second) {
    this->first = first;
    this->second = second;
}

ImpExp::~ImpExp() {
    delete first;
    delete second;
}

string ImpExp::toString() const {
    return "ImpExp(" + first->toString() + ", " + second->toString() + ")";
}

LangExpressionType ImpExp::getType() const {
    return LangExpressionType::ImpEXP;
}

bool ImpExp::eval(LangEvaluationContext& context) const {
    bool firstValue = first->eval(context);
    bool secondValue = second->eval(context);
    return (!firstValue) || secondValue;
}

/**
 * Implementation notes: IffExp
 * -------------------------------
 * TODO
 */

IffExp::IffExp(LangExpression *first, LangExpression *second) {
    this->first = first;
    this->second = second;
}

IffExp::~IffExp() {
    delete first;
    delete second;
}

string IffExp::toString() const {
    return "IffExp(" + first->toString() + ", " + second->toString() + ")";
}

LangExpressionType IffExp::getType() const {
    return LangExpressionType::IffEXP;
}

bool IffExp::eval(LangEvaluationContext& context) const {
    bool firstValue = first->eval(context);
    bool secondValue = second->eval(context);
    return (firstValue || (!secondValue)) && ((!firstValue) || secondValue);
}

/**
 * Implementation notes: LetExp
 * -------------------------------
 * TODO
 */

LetExp::LetExp(const string& variable,
               LangExpression * binding,
               LangExpression *body) {
    this->variable = variable;
    this->binding = binding;
    this->body = body;
}

LetExp::~LetExp() {
    delete binding;
    delete body;
}

string LetExp::toString() const {
    return "LetExp((" + variable + " = " +
            binding->toString() + ") in (" +
            body->toString() + "))";
}

LangExpressionType LetExp::getType() const {
    return LangExpressionType::LetEXP;
}

bool LetExp::eval(LangEvaluationContext& context) const {
    bool bindingValue = binding->eval(context);
    context.setValue(variable, bindingValue);
    bool bodyValue = body->eval(context);
    context.removeValue(variable);
    return bodyValue;
}

/**
 * Implementation notes: SetExp
 * -------------------------------
 * TODO
 */

SetExp::SetExp(const std::string& variable, LangExpression *binding) {
    this->variable = variable;
    this->binding = binding;
}

SetExp::~SetExp() {
    delete binding;
}

string SetExp::toString() const {
    return "SetExp(" + variable + " = " +
            binding->toString() + ")";
}

LangExpressionType SetExp::getType() const {
    return LangExpressionType::SetEXP;
}

bool SetExp::eval(LangEvaluationContext& context) const {
    bool bindingValue = binding->eval(context);
    context.setValue(variable, bindingValue);
    return bindingValue;
}


/**
 * Implementation notes: NullExp
 * -------------------------------
 * TODO
 */

NullExp::NullExp() {
    /* Empty */
}

string NullExp::toString() const {
    return "NullExp()";
}

LangExpressionType NullExp::getType() const {
    return LangExpressionType::NullEXP;
}

bool NullExp::eval(LangEvaluationContext& context) const {
    error("EVALUATION ERROR >> Attempted null evaluation.");
}

/**
 * Implementation notes: LangEvaluationContext
 * ---------------------------------------
 * The methods in the LangEvaluationContext class simply call the appropriate
 * method on the map used to represent the symbol table.
 */

void LangEvaluationContext::setValue(const string& var, bool value) {
   symbolTable.put(var, value);
}

bool LangEvaluationContext::getValue(const string& var) const {
   return symbolTable.get(var);
}

void LangEvaluationContext::removeValue(const std::string& var) {
    symbolTable.remove(var);
}

bool LangEvaluationContext::isDefined(const string& var) const {
   return symbolTable.containsKey(var);
}
