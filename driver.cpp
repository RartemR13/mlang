#include "driver.hh"
#include "parser.hh"

#include "visitors/PrintVisitor.h"
#include "visitors/Interpreter.h"

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
}


int Driver::parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();

    scan_end();
    return res;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    stream.open(file);
    // std::cout << file << std::endl;
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end()
{
    stream.close();
}

void Driver::PrintTree(const std::string& filename) {
    SymbolTreeVisitor visitor(filename);
    visitor.Visit(program);
}

void Driver::Execute() {
    Interpreter interpreter;
    interpreter.GetResult(program);
}