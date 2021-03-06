#ifndef WXBASIC_PARSER_H
#define WXBASIC_PARSER_H

#include "code.h"
#include "literal.h"
#include "symbol.h"
#include "tokenizer.h"
#include <memory>

namespace wxbasic {

class ParserError;

class Parser {
private:
    Tokenizer tokenizer;

    std::string source_name;
    std::string source;

    SymbolTable &sym_table;
    LiteralTable &lit_table;

    std::shared_ptr<Code> parse_expression(int);
    std::shared_ptr<Code> parse_operand();
    std::shared_ptr<Code> parse_statement();
    void parse_seperator(bool must_exist = true);
    std::shared_ptr<Code> parse_print();

    void join_operands(std::shared_ptr<Code> lhs, std::shared_ptr<Code> rhs,
                       std::shared_ptr<Token> token);
    void expect(TokenType, const std::string &, bool skip_token = true);
    bool is_seperator();
    void skip();

    TokenType skip_line();
    void skip_expression();
    void check_abstract(std::shared_ptr<ClassSymbol>);
    friend ParserError;

public:
    Parser(const std::string &sourcecode, const std::string &file_name,
           SymbolTable &symbol_table, LiteralTable &literal_table);
    Parser(const std::string &filename, SymbolTable &symbol_table,
           LiteralTable &literal_table);

    void scan_routines();
    std::shared_ptr<Code> parse();
    void print_tokens();
};

class ParserError : public Error {
public:
    ParserError(const std::string &error, const Parser &parser)
        : Error(error, parser.tokenizer.get_pos(), parser.source,
                parser.source_name){};
};

} // namespace wxbasic
#endif // WXBASIC_PARSER_H
