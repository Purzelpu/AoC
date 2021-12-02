#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

struct coordinate
{
  int x;
  int depth;
  int aim;
};

struct command
{
  char direction;
  int amount;
};

coordinate apply1(coordinate c, command comm)
  {
    switch(comm.direction)
      {
      case 'f':
	return {c.x+comm.amount, c.depth, 0};
	break;
      case 'u':
	return {c.x, c.depth-comm.amount, 0};
	break;
      case 'd':
	return {c.x, c.depth+comm.amount, 0};
	break;
      default:
	throw std::logic_error("unexpected command");
      }
  }

coordinate apply2(coordinate c, command comm)
  {
    switch(comm.direction)
      {
      case 'f':
	return {c.x+comm.amount, c.depth+c.aim*comm.amount, c.aim};
	break;
      case 'u':
	return {c.x, c.depth, c.aim-comm.amount};
	break;
      case 'd':
	return {c.x, c.depth, c.aim+comm.amount};
	break;
      default:
	throw std::logic_error("unexpected command");
      }
  }

std::istream& operator>>(std::istream& stream, command& comm)
{
  std::string s;
  stream >> s;
  comm.direction = s[0];
  stream >> comm.amount;

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const command& comm)
{
  stream << "command " << comm.direction << " " << comm.amount;
  return stream;
}

std::vector<command> load_input()
{
  std::ifstream input("input");
  std::istream_iterator<command> input_it(input);
  return {input_it, {}};
}

int main()
{
  auto v = load_input();

  coordinate position = std::accumulate(v.begin(), v.end(), coordinate{0,0,0}, apply1);
  std::cout << position.x*position.depth << std::endl;

  position = std::accumulate(v.begin(), v.end(), coordinate{0,0,0}, apply2);
  std::cout << position.x*position.depth << std::endl;
  return 0;
}
