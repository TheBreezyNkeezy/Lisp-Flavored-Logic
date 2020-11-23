
#include <iostream>
#include <string>
#include "console.h"
#include "error.h"
#include "sexpressions.h"
#include "langexpressions.h"
#include "sexpression-parser.h"
#include "langexpression-parser.h"
#include "tokenscanner.h"

using namespace std;

int main() {
    LangEvaluationContext context;
    TokenScanner scanner;
    SExpression *sexp;
    scanner.ignoreWhitespace();
    while (true) {
        sexp = nullptr;
        try {
            string response;
            cout << endl << "LPL REPL >> ";
            getline(cin, response);
            if (response == "quit") break;
            scanner.setInput(response);
            SExpression *sexp = parseOneSExp(scanner);
            // Comment out the following line to skip viewing the parsed S-expression
            cout << sexp->toString() << endl;
            LangExpression *lexp = parseLangExp(sexp);
            // Comment out the following line to skip viewing the unevaluated logic expression
            cout << lexp->toString() << endl;
            bool value = lexp->eval(context);
            cout << boolToString(value) << endl;
        } catch (ErrorException ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }
        if (sexp != nullptr) delete sexp;
    }
    return 0;
}
