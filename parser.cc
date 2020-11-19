#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "lexer.hh"
#include "spl_automata.hh"
#include "spl_recursive_descent.hh"
#include "parser.hh"

auto parse_spl_program(std::vector<token> &tokens) -> bool {
  // spl_program = block, "."
  std::size_t idx = 0;

  bool all = true;
  all = all && parse_block(tokens, idx);
  all = all && parse_terminal_period(tokens, idx);
  all = all && (idx == tokens.size());
  return all;
}

auto parse_block(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // block = "begin", {dcl, ";"}, st_list, "end"

  bool all = true;
  all = all && parse_terminal_begin(tokens, idx);
  while (all && parse_dcl(tokens, idx)) {
    all = all && parse_terminal_semicolon(tokens, idx);
  }
  all = all && parse_st_list(tokens, idx);
  all = all && parse_terminal_end(tokens, idx);
  return all;
}

auto parse_dcl(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // dcl = ("label"|"integer"), id, {",", id}
  bool all = true;
  all = all && (parse_terminal_label(tokens, idx) || parse_terminal_integer(tokens, idx));
  all = all && parse_terminal_id(tokens, idx);
  while (all && parse_terminal_comma(tokens, idx)) {
    all = all && parse_terminal_id(tokens, idx);
  }
  return all;
}

auto parse_st_list(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // st_list = st, {";", st}
  bool all = true;
  all = all && parse_st(tokens, idx);
  while (all && parse_terminal_semicolon(tokens, idx)) {
    all = all && parse_st(tokens, idx);
  }
  return all;
}

auto parse_st(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // st = [id, ":"], statement
  bool all = true;
  auto store = idx;
  if (all && parse_terminal_id(tokens, idx) && parse_terminal_colon(tokens, idx)) {
  } else {
    idx = store;
  }
  all = all && parse_statement(tokens, idx);
  return all;
}

auto parse_statement(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // statement = assignment
  //           | goto_st
  //           | if_st
  //           | write_st
  //           | block
  bool all = true;
  all = all && (
      parse_assignment(tokens, idx) ||
      parse_goto_st(tokens, idx) ||
      parse_if_st(tokens, idx) ||
      parse_write_st(tokens, idx) ||
      parse_block(tokens, idx));
  return all;
}

auto parse_assignment(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // assignment = exp, "=>", id, {"=>", id}
  bool all = true;
  auto store = idx;
  all = all && parse_exp(tokens, idx);
  all = all && parse_terminal_assign(tokens, idx);
  all = all && parse_terminal_id(tokens, idx);
  while (all && parse_terminal_assign(tokens, idx)) {
    all = all && parse_terminal_id(tokens, idx);
  }
  if (!all) {
    idx = store;
  }
  return all;
}

auto parse_goto_st(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // goto_st = "goto", id
  bool all = true;
  auto store = idx;
  all = all && parse_terminal_goto(tokens, idx);
  all = all && parse_terminal_id(tokens, idx);
  if (!all) {
    idx = store;
  }
  return all;
}

auto parse_if_st(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // if_st = "if", condition, "then, st_list, ["else", st_list], "fi"
  bool all = true;
  auto store = idx;
  all = all && parse_terminal_if(tokens, idx);
  all = all && parse_condition(tokens, idx);
  all = all && parse_terminal_then(tokens, idx);
  all = all && parse_st_list(tokens, idx);
  if (all && parse_terminal_else(tokens, idx)) {
    all = all && parse_st_list(tokens, idx);
  }
  all = all && parse_terminal_fi(tokens, idx);
  if (!all) {
    idx = store;
  }
  return all;
}

auto parse_write_st(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // write_st = "output", "(", exp, {",", exp}, ")"
  bool all = true;
  auto store = idx;
  all = all && parse_terminal_output(tokens, idx);
  all = all && parse_terminal_open_paren(tokens, idx);
  all = all && parse_exp(tokens, idx);
  while (all && parse_terminal_comma(tokens, idx)) {
    all = all && parse_exp(tokens, idx);
  }
  all = all && parse_terminal_close_paren(tokens, idx);
  if (!all) {
    idx = store;
  }
  return all;
}

auto parse_condition(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // condition = exp, ("<"|">"|"="), exp
  bool all = true;
  auto store = idx;
  all = all && parse_exp(tokens, idx);
  all = all && (
      parse_terminal_less(tokens, idx) ||
      parse_terminal_greater(tokens, idx) ||
      parse_terminal_equal(tokens, idx));
  all = all && parse_exp(tokens, idx);
  if (!all) {
    idx = store;
  }
  return all;
}

auto parse_exp(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // exp = term, {("+"|"-"), term}
  bool all = true;
  auto store = idx;
  all = all && parse_term(tokens, idx);
  while (all && (parse_terminal_plus(tokens, idx) || parse_terminal_minus(tokens, idx))) {
    all = all && parse_term(tokens, idx);
  }
  if (!all) {
    idx = store;
  }
  return all;
}

auto parse_term(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // term = factor, {("*"|"/"), factor}
  bool all = true;
  auto store = idx;
  all = all && parse_factor(tokens, idx);
  while (all && (parse_terminal_asterisk(tokens, idx) || parse_terminal_slash(tokens, idx))) {
    all = all && parse_factor(tokens, idx);
  }
  if (!all) {
    idx = store;
  }
  return all;
}

auto parse_factor(std::vector<token> &tokens, std::size_t &idx) -> bool {
  // factor = "input"
  //        | id
  //        | number
  //        | "(", exp, ")"
  bool all = true;
  auto store = idx;
  all = all && (
      parse_terminal_input(tokens, idx) ||
      parse_terminal_id(tokens, idx) ||
      parse_terminal_number(tokens, idx) ||
      (
       parse_terminal_open_paren(tokens, idx) &&
       parse_exp(tokens, idx) &&
       parse_terminal_close_paren(tokens, idx)));
  if (!all) {
    idx = store;
  }
  return all;
}

auto parse_terminal_begin(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
    && tokens[idx].type == token_keyword
    && tokens[idx].text == "begin"
    && (++idx >= 0);
}

auto parse_terminal_period(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
    && tokens[idx].type == token_delimiter
    && tokens[idx].text == "."
    && (++idx >= 0);
}

auto parse_terminal_semicolon(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_delimiter
      && tokens[idx].text == ";"
      && (++idx >= 0);
}

auto parse_terminal_label(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "label"
      && (++idx >= 0);
}

auto parse_terminal_integer(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "integer"
      && (++idx >= 0);
}

auto parse_terminal_id(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_identifier
      && (++idx >= 0);
}

auto parse_terminal_comma(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_delimiter
      && tokens[idx].text == ","
      && (++idx >= 0);
}

auto parse_terminal_colon(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_delimiter
      && tokens[idx].text == ":"
      && (++idx >= 0);
}

auto parse_terminal_goto(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "goto"
      && (++idx >= 0);
}

auto parse_terminal_if(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "if"
      && (++idx >= 0);
}

auto parse_terminal_then(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "then"
      && (++idx >= 0);
}

auto parse_terminal_else(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "else"
      && (++idx >= 0);
}

auto parse_terminal_fi(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "fi"
      && (++idx >= 0);
}

auto parse_terminal_output(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "output"
      && (++idx >= 0);
}

auto parse_terminal_open_paren(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_delimiter
      && tokens[idx].text == "("
      && (++idx >= 0);
}

auto parse_terminal_close_paren(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_delimiter
      && tokens[idx].text == ")"
      && (++idx >= 0);
}

auto parse_terminal_less(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_operator
      && tokens[idx].text == "<"
      && (++idx >= 0);
}

auto parse_terminal_greater(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_operator
      && tokens[idx].text == ">"
      && (++idx >= 0);
}

auto parse_terminal_equal(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_operator
      && tokens[idx].text == "="
      && (++idx >= 0);
}

auto parse_terminal_plus(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_operator
      && tokens[idx].text == "+"
      && (++idx >= 0);
}

auto parse_terminal_minus(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_operator
      && tokens[idx].text == "-"
      && (++idx >= 0);
}

auto parse_terminal_asterisk(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_operator
      && tokens[idx].text == "*"
      && (++idx >= 0);
}

auto parse_terminal_slash(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_operator
      && tokens[idx].text == "/"
      && (++idx >= 0);
}

auto parse_terminal_input(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "input"
      && (++idx >= 0);
}

auto parse_terminal_end(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_keyword
      && tokens[idx].text == "end"
      && (++idx >= 0);
}

auto parse_terminal_assign(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_delimiter
      && tokens[idx].text == "=>"
      && (++idx >= 0);
}

auto parse_terminal_number(std::vector<token> &tokens, std::size_t &idx) -> bool {
  return idx < tokens.size()
      && tokens[idx].type == token_number
      && (++idx >= 0);
}

auto main(int argc, char *argv[]) -> int {
  if (argc != 2) {
    std::cerr << "run with exactly one source file path." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto source_fs = std::ifstream(argv[1]);
  if (!source_fs.is_open()) {
    std::cerr << "failed to open file \"" << argv[1] << "\"." << std::endl;
    std::exit(EXIT_FAILURE);
  }
  source_fs.unsetf(source_fs.skipws);

  auto tokens = compiler::tokenize(
      std::istream_iterator<char>(source_fs),
      std::istream_iterator<char>(),
      spl_automata{});

  if (parse_it(tokens.cbegin(), tokens.cend())) {
    std::cout << "accept!" << std::endl;
  } else {
    std::cout << "reject..." << std::endl;
  }
}
