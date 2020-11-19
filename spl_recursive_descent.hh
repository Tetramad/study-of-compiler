#pragma once

#include <vector>

#include "spl_automata.hh"

auto parse_it(std::vector<token>::const_iterator first, std::vector<token>::const_iterator last) -> bool;

auto ts_expect(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last, token_type type, std::string text) -> bool;
auto next_token(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_s(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_b(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_b_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_d(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_d_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_l(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_l_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_n(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_n_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_z(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_y(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_m(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_a(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_a_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_a__(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_g(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_i(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_i_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_w(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_w_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_c(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_c_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_e(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_e_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_t(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_t_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
auto nts_f(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool;
