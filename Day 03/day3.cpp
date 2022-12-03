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

int prioritySum(vector<char> items)
{
  int sum = 0;
  for (auto i : items)
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
  return sum;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string rucksack;
  vector<char> itemsPart1, itemsPart2;
  map<int, int> fr, fr2;
  int index = 0, elvesNumber = 3;

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
    for (auto item : rucksack)
    {
      if (fr2[item] == index % elvesNumber)
      {
        fr2[item] = index % elvesNumber + 1;
      }
      if (fr2[item] == elvesNumber)
      {
        itemsPart2.push_back(item);
        break;
      }
    }
    index++;
  }

  cout << "Part1: " << prioritySum(itemsPart1) << endl;
  cout << "Part2: " << prioritySum(itemsPart2) << endl;
}
