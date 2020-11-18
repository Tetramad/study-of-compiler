#pragma once

auto parse_spl_program(std::vector<token> &tokens) -> bool;
auto parse_block(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_dcl(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_st_list(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_st(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_statement(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_assignment(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_goto_st(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_if_st(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_write_st(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_condition(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_exp(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_term(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_factor(std::vector<token> &tokens, std::size_t &idx) -> bool;

auto parse_terminal_begin(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_period(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_semicolon(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_label(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_integer(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_id(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_comma(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_colon(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_goto(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_if(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_then(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_else(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_fi(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_output(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_open_paren(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_close_paren(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_less(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_greater(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_equal(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_plus(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_minus(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_asterisk(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_slash(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_input(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_end(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_assign(std::vector<token> &tokens, std::size_t &idx) -> bool;
auto parse_terminal_number(std::vector<token> &tokens, std::size_t &idx) -> bool;
