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
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

vector<string> split(string line, string delimiters = ",./:;= qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM")
{
  vector<string> words;
  if (line.empty())
  {
    return words;
  }

  int index = line.find_first_of(delimiters);
  if (!line.substr(0, index).empty())
  {
    words.push_back(line.substr(0, index));
  }

  while (index != -1) {
    index++;
    line = line.substr(index, line.length() - index);
    index = line.find_first_of(delimiters);
    auto newWord = line.substr(0, index);
    if (!newWord.empty())
    {
      words.push_back(newWord);
    }
  }
  return words;
}

vector<unsigned long long int> split2(string line, string delimiters = ",./;:= qwertyuiopasdfghjklzxcvbnmIQWERTYUIOPASDFGHJKLZXCVBNM")
{
  vector<unsigned long long int> words;

  int index = line.find_first_of(delimiters);
  if (!line.substr(0, index).empty())
  {
    words.push_back(stoi(line.substr(0, index)));
  }

  while (index != -1) {
    index++;
    line = line.substr(index, line.length() - index);
    index = line.find_first_of(delimiters);
    auto newWord = line.substr(0, index);
    if (!newWord.empty())
    {
      words.push_back(stoull(newWord));
    }
  }
  return words;
}

unsigned long long int LCM(unsigned long long int a, unsigned long long int b)
{
  unsigned long long  lcm = 1;
  if (a > b)
    lcm = a;
  else
    lcm = b;
  while (1) {
    if (lcm % a == 0 && lcm % b == 0) {
      return lcm;
      break;
    }
    lcm++;
  }
}

struct monkey
{
  int index;
  vector<unsigned long long int> startingItems;
  char operationName;
  int operationValue;
  int divisibleBy;
  int ifTrue;
  int ifFalse;
  int inspectedItemsCount = 0;
};

unsigned long long int solve(vector<monkey> monkeys, int n, unsigned long long int lcm = 0)
{
  map<unsigned long long int, unsigned long long int>frequency;

  for (int index = 0; index < n; index++)
  {
    for (auto& m : monkeys)
    {
      for (auto& i : m.startingItems)
      {
        m.inspectedItemsCount++;
        frequency[i]++;

        unsigned long long int newItem;

        if (m.operationName == '*')
        {
          if (m.operationValue == -1)
          {
            newItem = i * i;
          }
          else
          {
            newItem = i * m.operationValue;
          }
        }
        else if (m.operationName == '+')
        {
          if (m.operationValue == -1)
          {
            newItem = i + i;
          }
          else
          {
            newItem = i + m.operationValue;
          }
        }

        unsigned long long int division = lcm != 0 ? newItem % lcm : newItem / 3;

        if (division % m.divisibleBy == 0)
        {

          monkeys[m.ifTrue].startingItems.push_back(division);
        }
        else
        {
          monkeys[m.ifFalse].startingItems.push_back(division);
        }
      }
      m.startingItems.clear();
    }
  }

  vector<unsigned long long int> items;
  for (auto monkey : monkeys)
  {
    items.push_back(monkey.inspectedItemsCount);
  }

  sort(items.rbegin(), items.rend());
  return items[0] * items[1];
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<monkey> monkeys;

  while (getline(cin, line)) {
    if (line != "")
    {
      monkey m;
      m.index = split2(line)[0];
      getline(cin, line);
      m.startingItems = split2(line);
      getline(cin, line);
      auto words = split(line);
      m.operationName = words[0][0];
      m.operationValue = words.size() == 1 ? -1 : stoi(words[1]);
      getline(cin, line);
      m.divisibleBy = split2(line)[0];
      getline(cin, line);
      m.ifTrue = split2(line)[0];
      getline(cin, line);
      m.ifFalse = split2(line)[0];
      monkeys.push_back(m);
    }
  }

  unsigned long long int lcm = 1;
  for (auto monkey : monkeys)
  {
    lcm = LCM(monkey.divisibleBy, lcm);
  }

  cout << "Part 1: " << solve(monkeys, 20) << endl;
  cout << "Part 2: " << solve(monkeys, 10000, lcm) << endl;
}