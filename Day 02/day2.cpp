#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <regex>
#include <sstream>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  char a, b;
  int part1 = 0, part2 = 0;

  while (cin >> a >> b) {
    if (a == 'A') // Rock
    {
      if (b == 'X')
      {
        part1 += 1; part1 += 3; // Rock
        part2 += 3; part2 += 0; //Scissors
      }
      else if (b == 'Y')
      {
        part1 += 2; part1 += 6; // Paper
        part2 += 1; part2 += 3; // Rock
      }
      else if (b == 'Z')
      {
        part1 += 3; part1 += 0; //Scissors
        part2 += 2; part2 += 6; // Paper
      }
    }
    else if (a == 'B') // Paper
    {
      if (b == 'X')
      {
        part1 += 1; part1 += 0; // Rock
        part2 += 1; part2 += 0; // Rock
      }
      else if (b == 'Y')
      {
        part1 += 2; part1 += 3; // Paper
        part2 += 2; part2 += 3; // Paper
      }
      else if (b == 'Z')
      {
        part1 += 3; part1 += 6; // Scissors
        part2 += 3; part2 += 6; // Scissors
      }
    }
    else if (a == 'C') // Scissors
    {
      if (b == 'X')
      {
        part1 += 1; part1 += 6; // Rock
        part2 += 2; part2 += 0; // Paper
      }
      else if (b == 'Y')
      {
        part1 += 2; part1 += 0; // Paper
        part2 += 3; part2 += 3; // Scissors
      }
      else if (b == 'Z')
      {
        part1 += 3; part1 += 3; // Scissors
        part2 += 1; part2 += 6; // Rock
      }
    }
  }

  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2;

  return 0;
}