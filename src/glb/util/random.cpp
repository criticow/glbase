#include "random.hpp"

std::string Random::UUID()
{
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<uint64_t> dis;

  uint64_t part1 = dis(gen);
  uint64_t part2 = dis(gen);

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