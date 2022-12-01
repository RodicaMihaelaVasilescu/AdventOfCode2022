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
#include <numeric>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<int> numbers;
  int sum = 0;

  while (getline(cin, line)) {
    if (line == "")
    {
      numbers.push_back(sum);
      sum = 0;
    }
    else
    {
      sum += stoi(line);
    }
  }
  numbers.push_back(sum);

  sort(numbers.rbegin(), numbers.rend());

  // the Elf carrying the most Calories
  cout << "Part 1: " << numbers[0] << endl;
  // the top three Elves carrying the most Calories
  cout << "Part 2: " << accumulate(numbers.begin(), numbers.begin() + 3, 0) << endl;
}