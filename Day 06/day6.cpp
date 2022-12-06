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
#include <bitset>

using namespace std;

int solve(string s, int n)
{
  for (int i = 0; i < s.size(); i++)
  {
    auto substr = s.substr(i, n);
    map<char, int> frequency;
    bool ok = true;
    for (auto letter : substr)
    {
      frequency[letter]++;
      if (frequency[letter] > 1)
      {
        ok = 0;
        break;
      }
    }

    if (ok)
    {
      return i + n;
    }
  }
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string s;
  cin >> s;

  cout << "Part 1: " << solve(s, 4) << endl;
  cout << "Part 2: " << solve(s, 14) << endl;
}