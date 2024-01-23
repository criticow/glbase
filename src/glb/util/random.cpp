#include "random.hpp"

std::string Random::UUID()
{
  std::random_device rd;
  std::mt19937_64 mt(rd());
  std::uniform_int_distribution<uint64_t> dist;

  uint64_t part1 = dist(mt);
  uint64_t part2 = dist(mt);

  std::stringstream ss;
  ss << std::hex << std::setw(16) << std::setfill('0') << part1;
  ss << std::hex << std::setw(16) << std::setfill('0') << part2;

  std::string uuid = ss.str();

  for(char &c : uuid)
  {
    c = std::toupper(c);
  }
  
  return uuid;
}

int Random::choose(int min, int max)
{
  std::random_device rd;
  std::mt19937_64 mt(rd());
  std::uniform_int_distribution<int> dist(min, max);

  return dist(mt);
}
