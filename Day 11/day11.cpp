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
#include<numeric>// for C++17
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

unsigned long long int LCM(unsigned long long int a, unsigned long long int b) // The function runs recursive in nature to return GCD.
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
  unsigned long long int operationValue;
  unsigned long long int divisibleBy;
  unsigned long long int ifTrue;
  unsigned long long int ifFalse;
  unsigned long long int inspectedItemsCount = 0;
};

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<monkey> monkeys;
  int monkeyIndex = 0;

  while (getline(cin, line)) {
    if (line != "")
    {
      monkey m;
      m.index = monkeyIndex;
      getline(cin, line);
      m.startingItems = split2(line);
      getline(cin, line);
      auto words = split(line);
      m.operationName = words[0][0];
      if (words.size() == 1)
      {
        m.operationValue = -1;
      }
      else
      {
        m.operationValue = stoi(words[1]);
      }
      getline(cin, line);
      m.divisibleBy = split2(line)[0];
      getline(cin, line);
      m.ifTrue = split2(line)[0];
      getline(cin, line);
      m.ifFalse = split2(line)[0];
      monkeys.push_back(m);
      monkeyIndex++;
    }
  }

  int n = 10000;
  unsigned long long int lcm = 1;

  for (auto monkey : monkeys)
  {
    lcm = LCM(monkey.divisibleBy, lcm);
  }

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

        auto division = newItem % lcm;

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
  cout << "Part 2: " << items[0] * items[1];
}