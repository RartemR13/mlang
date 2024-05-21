cmake_minimum_required(VERSION 3.6)

project(mlang)
set(
    HEADERS
    driver.hh
    parser.hh
    )

find_package(FLEX  2.6 REQUIRED)
find_package(BISON 2.6 REQUIRED)

BISON_TARGET(
    MyParserWithAst
    parser.y
    ${mlang_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${mlang_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScannerWithAst
    scanner.l
    ${mlang_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScannerWithAst MyParserWithAst)

add_executable(
    mlang
    main.cpp
    driver.cpp
    ${BISON_MyParserWithAst_OUTPUTS}
    ${FLEX_MyScannerWithAst_OUTPUTS}
    expressions/NumberExpression.cpp
    expressions/MulExpression.cpp
    expressions/AddExpression.cpp
    expressions/SubstractExpression.cpp
    expressions/DivExpression.cpp
    expressions/IdentExpression.cpp
    assignments/Assignment.cpp
    statements/StatementList.cpp
    statements/Print.cpp
    statements/If.cpp
    expressions/Condition.cpp
    visitors/PrintVisitor.cpp
    visitors/Interpreter.cpp
    Program.cpp
)

target_include_directories(
    mlang PRIVATE ${mlang_SOURCE_DIR}
)



