#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <functional>
#include <iterator>
#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "The file is not open\n";
    return 2;
  }
  using namespace piyavkin;
  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!in.eof())
  {
    std::copy(input_it_t{in}, input_it_t{}, std::back_inserter(polygons));
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  for (size_t i = 0; i < polygons.size(); ++i)
  {
    std::cout << polygons[i].points.size();
    for (size_t j = 0; j < polygons[i].points.size(); ++j)
    {
      std::cout << " (" << polygons[i].points[j].x << ';' << polygons[i].points[j].y << ')';
    }
    std::cout << ' ' << polygons[i].getArea() << '\n';
  }
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(getArea, _1, _2, std::cref(polygons));
  }
  std::string name = "";
  while (std::cin >> name)
  {
    try
    {
      cmds.at(name)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
