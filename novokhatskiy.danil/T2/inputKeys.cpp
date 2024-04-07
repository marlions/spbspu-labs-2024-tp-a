#include <bitset>
#include <string>
#include "delimiter.hpp"
#include "inputKeys.hpp"

std::istream& novokhatskiy::operator>>(std::istream& in, BinKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    in.setstate(std::ios::failbit);
  }
  std::bitset< 64 > bin;
  in >> DelimiterString< false >{ "0b" } >> bin;
  if (in)
  {
    key.value = bin.to_ullong();
  }
  return in;
}

std::istream& novokhatskiy::operator>>(std::istream& in, RATKey&& key)
{
  using strD = novokhatskiy::DelimiterString< true >;
  using strictStrD = novokhatskiy::DelimiterString< false >;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    in.setstate(std::ios::failbit);
  }
  long long ll{};
  unsigned long long ull{};
  in >> strD{ "(:n" } >> ll >> strD{ ":d" } >> ull >> strictStrD{ ":)" };
  if (in)
  {
    key.pair.first = ll;
    key.pair.second = ull;
  }
  return in;
}

std::istream& novokhatskiy::operator>>(std::istream& in, STRKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    in.setstate(std::ios::failbit);
  }
  std::string tmp = "";
  std::getline(in >> Delimiter< false >{ '"' }, tmp, '"');
  if (in)
  {
    key.str = tmp;
  }
  return in;
}
