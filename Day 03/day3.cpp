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
#include <bitset>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string rucksack;
  vector<char> itemsPart1, itemsPart2;
  map<int, int> fr, fr2;
  int index = 0;

  int elvesNumber = 3;

  while (cin >> rucksack) {

    // part 1
    fr.clear();
    for (int i = 0; i < rucksack.size() / 2; i++)
    {
      fr[rucksack[i]] = 1;
    }

    for (int i = rucksack.size() / 2; i < rucksack.size(); i++)
    {
      if (fr[rucksack[i]] != 0) {
        itemsPart1.push_back(rucksack[i]);
        break;
      }
    }

    //part 2
    if (index % elvesNumber == 0)
    {
      fr2.clear();
    }
    for (int i = 0; i < rucksack.size(); i++)
    {
      if (fr2[rucksack[i]] == index % elvesNumber)
      {
        fr2[rucksack[i]] = index % elvesNumber + 1;
      }
      if (fr2[rucksack[i]] == elvesNumber)
      {
        itemsPart2.push_back(rucksack[i]);
        break;
      }
    }
    index++;
  }

  int sum = 0, sum2 = 0;
  for (auto i : itemsPart1)
  {
    if (i >= 'a' && i <= 'z')
    {
      sum += i - 'a' + 1;
    }
    else
    {
      sum += i - 'A' + 1 + 26;
    }
  }

  for (auto i : itemsPart2)
  {
    if (i >= 'a' && i <= 'z')
    {
      sum2 += i - 'a' + 1;
    }
    else
    {
      sum2 += i - 'A' + 1 + 26;
    }
  }

  cout << "Part1: " << sum << endl;
  cout << "Part2: " << sum2 << endl;
}