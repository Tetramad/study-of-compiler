#include "spl_automata.hh"
#include "spl_recursive_descent.hh"

auto parse_it(std::vector<token>::const_iterator first, std::vector<token>::const_iterator last) -> bool {
  return nts_s(first, last);
}

auto ts_expect(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last, token_type type, std::string text) -> bool {
  return first != last && first->type == type && (text.empty() || first->text == text);
}

auto next_token(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (first != last) {
    ++first;
    return true;
  } else {
    return false;
  }
}

auto nts_s(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "begin")) {
    return nts_b(first, last)
      && ts_expect(first, last, token_delimiter, ".")
      && next_token(first, last);
  } else {
    return false;
  }
}

auto nts_b(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "begin")) {
    return next_token(first, last)
      && nts_b_(first, last);
  } else {
    return false;
  }
}

auto nts_b_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "label")
      || ts_expect(first, last, token_keyword, "integer")) {
    return nts_d(first, last)
      && ts_expect(first, last, token_delimiter, ";")
      && next_token(first, last)
      && nts_b_(first, last);
  } else if (ts_expect(first, last, token_identifier, "")
      || ts_expect(first, last, token_keyword, "input")
      || ts_expect(first, last, token_number, "")
      || ts_expect(first, last, token_delimiter, "(")
      || ts_expect(first, last, token_keyword, "goto")
      || ts_expect(first, last, token_keyword, "if")
      || ts_expect(first, last, token_keyword, "output")
      || ts_expect(first, last, token_keyword, "begin")) {
    return nts_l(first, last)
      && ts_expect(first, last, token_keyword, "end")
      && next_token(first, last);
  } else {
    return false;
  }
}

auto nts_d(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "label")) {
    return next_token(first, last)
      && ts_expect(first, last, token_identifier, "")
      && next_token(first, last)
      && nts_d_(first, last);
  } else if (ts_expect(first, last, token_keyword, "integer")) {
    return next_token(first, last)
      && ts_expect(first, last, token_identifier, "")
      && next_token(first, last)
      && nts_d_(first, last);
  } else {
    return false;
  }
}

auto nts_d_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_delimiter, ",")) {
    return next_token(first, last)
      && ts_expect(first, last, token_identifier, "")
      && next_token(first, last)
      && nts_d_(first, last);
  } else if (ts_expect(first, last, token_delimiter, ";")) {
    return true;
  } else {
    return false;
  }
}

auto nts_l(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_identifier, "")
      || ts_expect(first, last, token_keyword, "input")
      || ts_expect(first, last, token_number, "")
      || ts_expect(first, last, token_delimiter, "(")
      || ts_expect(first, last, token_keyword, "goto")
      || ts_expect(first, last, token_keyword, "if")
      || ts_expect(first, last, token_keyword, "output")
      || ts_expect(first, last, token_keyword, "begin")) {
    return nts_n(first, last)
      && nts_l_(first, last);
  } else {
    return false;
  }
}

auto nts_l_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_delimiter, ";")) {
    return next_token(first, last)
      && nts_l(first, last);
  } else if (ts_expect(first, last, token_keyword, "end")
      || ts_expect(first, last, token_keyword, "fi")
      || ts_expect(first, last, token_keyword, "else")) {
    return true;
  } else {
    return false;
  }
}

auto nts_n(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_identifier, "")) {
    return next_token(first, last)
      && nts_n_(first, last);
  } else if (ts_expect(first, last, token_keyword, "input")) {
    return next_token(first, last)
      && nts_z(first, last);
  } else if (ts_expect(first, last, token_number, "")) {
    return next_token(first, last)
      && nts_z(first, last);
  } else if (ts_expect(first, last, token_delimiter, "(")) {
    return next_token(first, last)
      && nts_e(first, last)
      && ts_expect(first, last, token_delimiter, ")")
      && next_token(first, last)
      && nts_z(first, last);
  } else if (ts_expect(first, last, token_keyword, "goto")) {
    return nts_g(first, last);
  } else if (ts_expect(first, last, token_keyword, "if")) {
    return nts_i(first, last);
  } else if (ts_expect(first, last, token_keyword, "output")) {
    return nts_w(first, last);
  } else if (ts_expect(first, last, token_keyword, "begin")) {
    return nts_b(first, last);
  } else {
    return false;
  }
}

auto nts_n_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_delimiter, ":")) {
    return next_token(first, last)
      && nts_m(first, last);
  } else if (ts_expect(first, last, token_operator, "*")
      || ts_expect(first, last, token_operator, "/")
      || ts_expect(first, last, token_operator, "+")
      || ts_expect(first, last, token_operator, "-")
      || ts_expect(first, last, token_delimiter, "=>")) {
    return nts_z(first, last);
  } else {
    return false;
  }
}

auto nts_z(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_operator, "*")) {
    return next_token(first, last)
      && nts_f(first, last)
      && nts_y(first, last);
  } else if (ts_expect(first, last, token_operator, "/")) {
    return next_token(first, last)
      && nts_f(first, last)
      && nts_y(first, last);
  } else if (ts_expect(first, last, token_operator, "+")
      || ts_expect(first, last, token_operator, "-")
      || ts_expect(first, last, token_delimiter, "=>")) {
    return nts_y(first, last);
  } else {
    return false;
  }
}

auto nts_y(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_operator, "+")) {
    return next_token(first, last)
      && nts_t(first, last)
      && nts_a_(first, last);
  } else if (ts_expect(first, last, token_operator, "-")) {
    return next_token(first, last)
      && nts_t(first, last)
      && nts_a_(first, last);
  } else if (ts_expect(first, last, token_delimiter, "=>")) {
    return nts_a_(first, last);
  } else {
    return false;
  }
}

auto nts_m(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "input")
      || ts_expect(first, last, token_identifier, "")
      || ts_expect(first, last, token_number, "")
      || ts_expect(first, last, token_delimiter, "(")) {
    return nts_a(first, last);
  } else if (ts_expect(first, last, token_keyword, "goto")) {
    return nts_g(first, last);
  } else if (ts_expect(first, last, token_keyword, "if")) {
    return nts_i(first, last);
  } else if (ts_expect(first, last, token_keyword, "output")) {
    return nts_w(first, last);
  } else if (ts_expect(first, last, token_keyword, "begin")) {
    return nts_b(first, last);
  } else {
    return false;
  }
}

auto nts_a(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "input")
      || ts_expect(first, last, token_identifier, "")
      || ts_expect(first, last, token_number, "")
      || ts_expect(first, last, token_delimiter, "(")) {
    return nts_e(first, last)
      && nts_a_(first, last);
  } else {
    return false;
  }
}

auto nts_a_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_delimiter, "=>")) {
    return next_token(first, last)
      && ts_expect(first, last, token_identifier, "")
      && next_token(first, last)
      && nts_a__(first, last);
  } else {
    return false;
  }
}

auto nts_a__(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_delimiter, "=>")) {
    return nts_a_(first, last);
  } else if (ts_expect(first, last, token_delimiter, ";")
      || ts_expect(first, last, token_keyword, "end")
      || ts_expect(first, last, token_keyword, "fi")
      || ts_expect(first, last, token_keyword, "else")) {
    return true;
  } else {
    return false;
  }
}

auto nts_g(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "goto")) {
    return next_token(first, last)
      && ts_expect(first, last, token_identifier, "")
      && next_token(first, last);
  } else {
    return false;
  }
}

auto nts_i(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "if")) {
    return next_token(first, last)
      && nts_c(first, last)
      && ts_expect(first, last, token_keyword, "then")
      && next_token(first, last)
      && nts_l(first, last)
      && nts_i_(first, last);
  } else {
    return false;
  }
}

auto nts_i_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "fi")) {
    return next_token(first, last);
  } else if (ts_expect(first, last, token_keyword, "else")) {
    return next_token(first, last)
      && nts_l(first, last)
      && ts_expect(first, last, token_keyword, "fi")
      && next_token(first, last);
  } else {
    return false;
  }
}

auto nts_w(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "output")) {
    return next_token(first, last)
      && ts_expect(first, last, token_delimiter, "(")
      && next_token(first, last)
      && nts_e(first, last)
      && nts_w_(first, last);
  } else {
    return false;
  }
}

auto nts_w_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_delimiter, ",")) {
    return next_token(first, last)
      && nts_e(first, last)
      && nts_w_(first, last);
  } else if (ts_expect(first, last, token_delimiter, ")")) {
    return next_token(first, last);
  } else {
    return false;
  }
}

auto nts_c(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_identifier, "")
      || ts_expect(first, last, token_keyword, "input")
      || ts_expect(first, last, token_number, "")
      || ts_expect(first, last, token_delimiter, "(")) {
    return nts_e(first, last)
      && nts_c_(first, last);
  } else {
    return false;
  }
}

auto nts_c_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_operator, "<")) {
    return next_token(first, last)
      && nts_e(first, last);
  } else if (ts_expect(first, last, token_operator, ">")) {
    return next_token(first, last)
      && nts_e(first, last);
  } else if (ts_expect(first, last, token_operator, "=")) {
    return next_token(first, last)
      && nts_e(first, last);
  } else {
    return false;
  }
}

auto nts_e(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_identifier, "")
      || ts_expect(first, last, token_keyword, "input")
      || ts_expect(first, last, token_number, "")
      || ts_expect(first, last, token_delimiter, "(")) {
    return nts_t(first, last)
      && nts_e_(first, last);
  } else {
    return false;
  }
}

auto nts_e_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_operator, "*")) {
    return next_token(first, last)
      && nts_t(first, last);
  } else if (ts_expect(first, last, token_operator, "/")) {
    return next_token(first, last)
      && nts_t(first, last);
  } else if (ts_expect(first, last, token_delimiter, ")")
      || ts_expect(first, last, token_delimiter, "=>")
      || ts_expect(first, last, token_delimiter, ",")
      || ts_expect(first, last, token_operator, "<")
      || ts_expect(first, last, token_operator, ">")
      || ts_expect(first, last, token_operator, "=")
      || ts_expect(first, last, token_keyword, "then")) {
    return true;
  } else {
    return false;
  }
}

auto nts_t(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_identifier, "")
      || ts_expect(first, last, token_keyword, "input")
      || ts_expect(first, last, token_number, "")
      || ts_expect(first, last, token_delimiter, "(")) {
    return nts_f(first, last)
      && nts_t_(first, last);
  } else {
    return false;
  }
}

auto nts_t_(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_operator, "+")) {
    return next_token(first, last)
      && nts_f(first, last);
  } else if (ts_expect(first, last, token_operator, "-")) {
    return next_token(first, last)
      && nts_f(first, last);
  } else if (ts_expect(first, last, token_operator, "*")
      || ts_expect(first, last, token_operator, "/")
      || ts_expect(first, last, token_delimiter, ")")
      || ts_expect(first, last, token_delimiter, "=>")
      || ts_expect(first, last, token_delimiter, ",")
      || ts_expect(first, last, token_operator, "<")
      || ts_expect(first, last, token_operator, ">")
      || ts_expect(first, last, token_operator, "=")
      || ts_expect(first, last, token_keyword, "then")) {
    return true;
  } else {
    return false;
  }
}

auto nts_f(std::vector<token>::const_iterator &first, std::vector<token>::const_iterator const &last) -> bool {
  if (ts_expect(first, last, token_keyword, "input")) {
    return next_token(first, last);
  } else if (ts_expect(first, last, token_identifier, "")) {
    return next_token(first, last);
  } else if (ts_expect(first, last, token_number, "")) {
    return next_token(first, last);
  } else if (ts_expect(first, last, token_delimiter, "(")) {
    return next_token(first, last)
      && nts_e(first, last)
      && ts_expect(first, last, token_delimiter, ")")
      && next_token(first, last);
  } else {
    return false;
  }
}
