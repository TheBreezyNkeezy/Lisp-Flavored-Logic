# Lisp Flavored Logic
This project, which I called Lisp Flavored Logic, was my final project for Stanford's CS 106X (Programming Abstractions Accelerated) in fall 2019. I aimed to explore (1) my love for programming languages, especially S-expression based languages like Common Lisp and Clojure that I had learned the summer before, and (2) applications of what I'd learned in logic classes to creating a simple interpreter for propositional (sentential) logic.

The foundation of the project essentially required coding in C++ (in Qt) a parser for S-expressions which was inspired by [this Scala implementation from Mark Might](http://matt.might.net/articles/parsing-s-expressions-scala/), which would then feed into another parser/lexer for propositional logic keywords and variables in each S-expression. These two parsers were then connected into a minimal REPL.

In all, this little REPL can evaluate any well-formed formula (WFF) in the language of propositional logic (L<sup>bool</sup>) --- here showing the pretty print of the double parsing at the S-expression and "Lang-expression" levels respectively (see my poster "slides" in the PDF above for more detailed info) --- with the extra features of:
* utilizing various alternates for the possible set of operators, including a subset of [Polish notations](https://en.wikipedia.org/wiki/Polish_notation#Polish_notation_for_logic) for negation `N` (alternatively `not`, `~`, `[-]`, or `!`), conjunction `K` (alternatively `and`, `&`, or `[*]`), disjunction `A` (alternatively `or`, `||`, or `[+]`), conditional `C` (alternatively `implies`, `imp`, or `==>`), and finally biconditional `E` (alternatively `iff` or `<=>`), as well as multiple encodings for `true` (alternatively `t` or `1`) and `false` (alternatively `f` or `0`):
```
LPL REPL >> ((and) true false)
SCons(SCons(SSymbol(and)) STrue() SFalse())
AndExp(BoolExp(true), BoolExp(false))
false

LPL REPL >> ((K) t f)
SCons(SCons(SSymbol(K)) STrue() SFalse())
AndExp(BoolExp(true), BoolExp(false))
false
```
* local bindings in the form of let statements:
```
LPL REPL >> ((let) p t ((and) p f))
SCons(SCons(SSymbol(let)) SSymbol(p) STrue() SCons(SCons(SSymbol(and)) SSymbol(p) SFalse()))
LetExp((p = BoolExp(true)) in (AndExp(RefExp(p), BoolExp(false))))
false
```
* global bindings in the form of set statements:
```
LPL REPL >> ((set) Q 1)
SCons(SCons(SSymbol(set)) SSymbol(Q) SConstant(1))
SetExp(Q = BoolExp(true))
true

LPL REPL >> Q
SSymbol(Q)
RefExp(Q)
true

LPL REPL >> ((let) R 0 ((and) Q R))
SCons(SCons(SSymbol(let)) SSymbol(R) SConstant(0) SCons(SCons(SSymbol(and)) SSymbol(Q) SSymbol(R)))
LetExp((R = BoolExp(false)) in (AndExp(RefExp(Q), RefExp(R))))
false
```
* and basic error passing back from parser to REPL:
```
LPL REPL >> ((let) R () ((and) ((and) P Q)
Error: PARSE ERROR >> Unbalanced parentheses.

LPL REPL >> ((let) P t)
SCons(SCons(SSymbol(let)) SSymbol(P) STrue())
Error: LangExpression PARSE ERROR >> Incorrect number of terms provided for operation let

LPL REPL >> ((set) constant constant)
SCons(SCons(SSymbol(set)) SSymbol(constant) SSymbol(constant))
SetExp(constant = RefExp(constant))
Error: EVALUATION ERROR >> undefined symbol: constant
```

Future plans for and from this project include:
* adding abilities to convert L<sup>bool</sup> WFFs into conjunctive and disjunctive normal forms, as well as analyzing their validity or satisfiability,
* adding more Prolog-like first-order logic capabilities with SLD resolution of provided rules and facts, and Skolemization of WFFs in the language of first order logic (L<sup>FOL</sup>),
* and translating from C++ to a functional language with powerful pattern matching, like Haskell or F# or Scala (in order of my proficiency).



