#include <type_traits>
#include <iostream>
#include <iterator>
#include <fstream>
#include <cstdlib>
#include "lexer.hh"

#include <unordered_map>

auto kw2str_lut = std::unordered_map<compiler::kw, std::string>{
  { compiler::kw::kw_begin, "begin" },
  { compiler::kw::kw_end, "end" },
  { compiler::kw::kw_label, "label" },
  { compiler::kw::kw_integer, "integer" },
  { compiler::kw::kw_goto, "goto" },
  { compiler::kw::kw_if, "if" },
  { compiler::kw::kw_then, "then" },
  { compiler::kw::kw_else, "else" },
  { compiler::kw::kw_fi, "fi" },
  { compiler::kw::kw_output, "output" },
  { compiler::kw::kw_input, "input" },
};

auto op2str_lut = std::unordered_map<compiler::op, std::string>{
  { compiler::op::op_less, "less" },
  { compiler::op::op_greater, "greater" },
  { compiler::op::op_equal, "equal" },
  { compiler::op::op_plus, "plus" },
  { compiler::op::op_minus, "minus" },
  { compiler::op::op_asterisk, "asterisk" },
  { compiler::op::op_slash, "slash" },
};

auto delim2str_lut = std::unordered_map<compiler::delim, std::string>{
  { compiler::delim::delim_assign, "assign" },
  { compiler::delim::delim_comma, "comma" },
  { compiler::delim::delim_period, "period" },
  { compiler::delim::delim_semicolon, "semicolon" },
  { compiler::delim::delim_colon, "colon" },
  { compiler::delim::delim_open_paren, "open_paren" },
  { compiler::delim::delim_close_paren, "close_paren" },
};

auto main(int argc, char *argv[]) -> int {
  if (argc != 2) {
    std::cerr << "should run with source file." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto source = std::ifstream(argv[1]);
  if (!source.is_open()) {
    std::cerr << "file open failed." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto str = std::string{std::istreambuf_iterator<char>{source},
    std::istreambuf_iterator<char>{}};
  auto lexer = compiler::lexer{};
  auto tokens = lexer.tokenize(str);
  for (auto const &token : tokens) {
    switch (token.index()) {
      case 0:
        std::cout << "id   [" << std::get<0>(token) << ']' << std::endl;
        break;
      case 1:
        std::cout << "num  [" << std::get<1>(token) << ']' << std::endl;
        break;
      case 2:
        std::cout << "kw   [" << kw2str_lut[std::get<2>(token)] << ']' << std::endl;
        break;
      case 3:
        std::cout << "op   [" << op2str_lut[std::get<3>(token)] << ']' << std::endl;
        break;
      case 4:
        std::cout << "delim[" << delim2str_lut[std::get<4>(token)] << ']' << std::endl;
        break;
    };
  }
}
