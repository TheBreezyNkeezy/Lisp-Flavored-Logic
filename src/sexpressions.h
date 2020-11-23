/**
 * File: sexpressions.h
 * -------------
 * This interface defines a class hierarchy for S-expressions.
 */

#ifndef SEXP_H
#define SEXP_H

#include <string>
#include "linkedlist.h"

enum SExpressionType {
    CONSTANT, SYMBOL, TRUE,
    FALSE, CONS, NIL
};

class SExpression {
public:
    SExpression();
    virtual ~SExpression();
    virtual std::string toString() const = 0;
    virtual SExpressionType getType() const = 0;
    virtual LinkedList<SExpression *> toList() const = 0;
    virtual bool isList() const = 0;

    virtual double getConstantValue() const;
    virtual std::string getSymbolName() const;
    virtual SExpression *getCAR() const;
    virtual SExpression *getCDR() const;
};

class SConstant : public SExpression {
public:
    SConstant(const double& value);
    virtual std::string toString() const override;
    virtual SExpressionType getType() const override;
    virtual LinkedList<SExpression *> toList() const override;
    virtual bool isList() const override;
    virtual double getConstantValue() const override;
private:
    double value;
};

class SSymbol : public SExpression {
public:
    SSymbol(const std::string& name);
    virtual std::string toString() const override;
    virtual SExpressionType getType() const override;
    virtual LinkedList<SExpression *> toList() const override;
    virtual bool isList() const override;
    virtual std::string getSymbolName() const override;
private:
    std::string name;
};

class STrue : public SExpression {
public:
    STrue();
    virtual std::string toString() const override;
    virtual SExpressionType getType() const override;
    virtual LinkedList<SExpression *> toList() const override;
    virtual bool isList() const override;
};

class SFalse : public SExpression {
public:
    SFalse();
    virtual std::string toString() const override;
    virtual SExpressionType getType() const override;
    virtual LinkedList<SExpression *> toList() const override;
    virtual bool isList() const override;
};

class SCons : public SExpression {
public:
    SCons(SExpression *car, SExpression *cdr);
    virtual ~SCons() override;
    virtual std::string toString() const override;
    virtual SExpressionType getType() const override;
    virtual LinkedList<SExpression *> toList() const override;
    virtual bool isList() const override;
    virtual SExpression *getCAR() const override;
    virtual SExpression *getCDR() const override;
private:
    SExpression *car, *cdr;
};

class SNil : public SExpression {
public:
    SNil();
    virtual std::string toString() const override;
    virtual SExpressionType getType() const override;
    virtual LinkedList<SExpression *> toList() const override;
    virtual bool isList() const override;
};

#endif // SEXP_H
