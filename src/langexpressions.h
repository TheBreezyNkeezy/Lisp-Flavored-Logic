/**
 * File: langexpressions.h
 * -------------
 * This interface defines a class hierarchy for translating S-expressions
 * into expressions evaluable according to the language gramamr.
 */

#ifndef LANGEXPRESSIONS_H
#define LANGEXPRESSIONS_H

#include <string>
#include "sexpressions.h"
#include "linkedlist.h"
#include "vector.h"
#include "map.h"

class LangEvaluationContext;

enum LangExpressionType {
    RefEXP, BoolEXP, NotEXP,
    AndEXP, OrEXP, ImpEXP,
    IffEXP, LetEXP, SetEXP, NullEXP
};

class LangExpression {
public:
    LangExpression();
    virtual ~LangExpression();
    virtual std::string toString() const = 0;
    virtual LangExpressionType getType() const = 0;
    virtual bool eval(LangEvaluationContext& context) const = 0;
};

class RefExp : public LangExpression {
public:
    RefExp(const std::string& name);
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    std::string name;
};

class BoolExp : public LangExpression {
public:
    BoolExp(const bool& value);
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    bool value;
};

class NotExp : public LangExpression {
public:
    NotExp(LangExpression *toNegate);
    virtual ~NotExp() override;
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    LangExpression *toNegate;
};

class AndExp : public LangExpression {
public:
    AndExp(LangExpression *first, LangExpression *second);
    virtual ~AndExp() override;
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    LangExpression *first, *second;
};

class OrExp : public LangExpression {
public:
    OrExp(LangExpression *first, LangExpression *second);
    virtual ~OrExp() override;
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    LangExpression *first, *second;
};

class ImpExp : public LangExpression {
public:
    ImpExp(LangExpression *first, LangExpression *second);
    virtual ~ImpExp() override;
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    LangExpression *first, *second;
};

class IffExp : public LangExpression {
public:
    IffExp(LangExpression *first, LangExpression *second);
    virtual ~IffExp() override;
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    LangExpression *first, *second;
};

class LetExp : public LangExpression {
public:
    LetExp(const std::string& variable,
           LangExpression *binding,
           LangExpression *body);
    virtual ~LetExp() override;
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    std::string variable;
    LangExpression *binding;
    LangExpression *body;
};

class SetExp : public LangExpression {
public:
    SetExp(const std::string& variable, LangExpression *binding);
    virtual ~SetExp() override;
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
private:
    std::string variable;
    LangExpression *binding;
};

//class ConsExp : public LangExpression {
//public:
//    ConsExp(LangExpression *car, LangExpression *cdr);
//    virtual ~ConsExp() override;
//    virtual std::string toString() const override;
//    virtual LangExpressionType getType() const override;
//    virtual bool eval(LangEvaluationContext& context) const override;
//private:
//    LangExpression *car, *cdr;
//};

//class CarExp : public LangExpression {
//public:
//    CarExp(LangExpression *toGetCAR);
//    virtual ~CarExp() override;
//    virtual std::string toString() const override;
//    virtual LangExpressionType getType() const override;
//    virtual bool eval(LangEvaluationContext& context) const override;
//private:
//    LangExpression *toGetCAR;
//};

//class CdrExp : public LangExpression {
//public:
//    CdrExp(LangExpression *toGetCDR);
//    virtual ~CdrExp() override;
//    virtual std::string toString() const override;
//    virtual LangExpressionType getType() const override;
//    virtual bool eval(LangEvaluationContext& context) const override;
//private:
//    LangExpression *toGetCDR;
//};

class NullExp : public LangExpression {
public:
    NullExp();
    virtual std::string toString() const override;
    virtual LangExpressionType getType() const override;
    virtual bool eval(LangEvaluationContext& context) const override;
};

class LangEvaluationContext {
public:
    void setValue(const std::string& var, bool value);
    bool getValue(const std::string& var) const;
    void removeValue(const std::string& var);
    bool isDefined(const std::string& var) const;
private:
    Map<std::string, bool> symbolTable;
};

#endif // LANGEXPRESSIONS_H
