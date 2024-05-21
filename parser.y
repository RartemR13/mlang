%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <memory>

    class Scanner;
    class Driver;
    class Expression;
    class NumberExpression;
    class AddExpression;
    class SubstractExpression;
    class DivExpression;
    class IdentExpression;
    class Assignment;
    class StatementList;
    class Program;
    class Print;
    class Condition;
    class If;
    enum class CompareOperators;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    #include "expressions/NumberExpression.h"
    #include "expressions/AddExpression.h"
    #include "expressions/MulExpression.h"
    #include "expressions/DivExpression.h"
    #include "expressions/SubstractExpression.h"
    #include "expressions/IdentExpression.h"
    #include "assignments/Assignment.h"
    #include "statements/StatementList.h"
    #include "Program.h"

    #include "statements/Print.h"
    #include "statements/If.h"
    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    ASSIGN ":="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    LPAREN "("
    RPAREN ")"
    POW "**"
    LBRACKET "{"
    RBRACKET "}"
    SEMICOLON ";"
    EQUAL           "=="
    NOT_EQUAL        "!="
    LOWER           "<"
    GREATER         ">"
    LOWER_OR_EQ     "<="
    GREATER_OR_EQ   ">="
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%token       MAIN "main"
%token       FUNCTION "function"
%token       PRINT    "print"

%token       IF         "if"
%token       ELSE       "else"

%nterm <Expression*> exp
%nterm <Assignment*> assignment
%nterm <StatementList*> assignments
%nterm <Program*> main_function
%nterm <Program*> scope

%nterm <Print*> print_statement 
%nterm <If*> if_statement
%nterm <Condition*> condition

// %printer { yyo << $$; } <*>;

%%
%start main_function;

main_function: FUNCTION MAIN LBRACKET scope RBRACKET {
    driver.result = 0;
    $$ = $4;
    driver.program = $$;
}

scope: assignments {
    // std::cout << $1->getStatements().size() << std::endl;
    $$ = new Program($1);
    // std::cout << $$->getStatements()->getStatements().size() << std::endl;
}

/*
unit: FUNCTION MAIN LBRACKET assignments exp RBRACKET {
        $$ = new Program($3, $4);
        driver.program = $$;
    };
*/

assignments:
    %empty {
        $$ = new StatementList();
    }
    | assignments assignment {
        $1->AddStatement($2);
        $$ = $1;
    }
    | assignments print_statement {
        $1->AddStatement($2);
        $$ = $1;
    }
    | assignments if_statement {
        $1->AddStatement($2);
        $$ = $1;
    };

print_statement: "print" "(" exp ")" ";" {
    $$ = new Print($3);
};

if_statement: 
    IF "(" condition ")" "{" assignments "}" "else" "{" assignments "}" {
        $$ = new If($3, $6, $10);
    }
    | IF "(" condition ")" "{" assignments "}" {
        $$ = new If($3, $6, nullptr);
    };

condition : exp "==" exp { $$ = new Condition($1, $3, CompareOperators::EQUAL);}
    | exp "!=" exp { $$ = new Condition($1, $3, CompareOperators::NOT_EQUAL);}
    | exp "<" exp { $$ = new Condition($1, $3, CompareOperators::LOWER);}
    | exp ">" exp { $$ = new Condition($1, $3, CompareOperators::GREATER);}
    | exp "<=" exp { $$ = new Condition($1, $3, CompareOperators::LOWER_OR_EQ);}
    | exp ">=" exp { $$ = new Condition($1, $3, CompareOperators::GREATER_OR_EQ);}
    ;

assignment:
    "identifier" ":=" exp ";" {
        $$ = new Assignment($1, $3);
        driver.variables[$1] = $3->eval(driver);
    };

%left "+" "-";
%left "*" "/";

exp:
    "number" {$$ = new NumberExpression($1); }
    | "identifier" {$$ = new IdentExpression($1); }
    | exp "+" exp { $$ = new AddExpression($1, $3); }
    | exp "-" exp { $$ = new SubstractExpression($1, $3); }
    | exp "*" exp { $$ = new MulExpression($1, $3); }
    | exp "/" exp { $$ = new DivExpression($1, $3); }
    | "(" exp ")" { $$ = $2; }
    ;

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
