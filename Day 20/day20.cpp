#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <regex>
#include <sstream>
#include <numeric>
#include <bitset>

using namespace std;

void insertNextItem(list<pair<long long, long long>>& numbers, list<pair<long long, long long>>::iterator it, pair<long long, long long> item)
{
  long long n = numbers.size();
  long long nr = abs(item.first) % n;

  if (item.first > 0)
  {
    while (nr--)
    {
      if (it == numbers.end())
      {
        it = next(numbers.begin());
      }
      else
      {
        it = next(it);
      }
    }
  }
  else if (item.first < 0)
  {
    while (nr--)
    {
      if (it == numbers.begin())
      {
        it = prev(numbers.end());
      }
      else
      {
        it = prev(it);
      }
    }
  }

  if (it == numbers.end())
  {
    numbers.push_front(item);
  }
  else
  {
    numbers.insert(it, 1, item);
  }
}

long long solve(vector<long long> initialNumbers, int times = 1)
{
  list<pair<long long, long long>> numbers;
  long long id = 0;
  long long id0 = 0;
  for (auto i : initialNumbers)
  {
    if (i == 0)
    {
      id0 = id;
    }
    numbers.push_back({ i ,id++ });
  }

  for (int j = 0; j < times; j++)
  {
    for (long long i = 0; i < initialNumbers.size(); i++)
    {
      if (initialNumbers[i] == 0)
      {
        continue;
      }
      auto it = numbers.begin();
      while (it->second != i)
      {
        it++;
      }
      pair<long long, long long> newNodeVal = { it->first, it->second };

      list<pair<long long, long long> >::iterator it2;

      it2 = next(it);
      if (it2 == numbers.end())
      {
        it2 = numbers.begin();
      }

      if (it == numbers.begin())
      {
        numbers.pop_front();
      }
      else if (it == numbers.end())
      {
        numbers.pop_back();
      }
      else
      {
        numbers.erase(it);
      }

      insertNextItem(numbers, it2, newNodeVal);
    }
  }

  auto it = numbers.begin();
  while (it->first != 0 && it->second != id0)
  {
    if (it == numbers.end())
    {
      it = next(numbers.begin());
    }
    else
    {
      it = next(it);
    }
  }

  long long sum = 0;
  long long nr = 3000;
  while (nr--)
  {
    if (it == numbers.end())
    {
      it = next(numbers.begin());
    }
    else
    {
      it = next(it);
    }

    if (nr == 2000 || nr == 1000 || nr == 0)
    {
      if (it == numbers.end())
      {
        sum += numbers.begin()->first;
      }
      else
      {
        sum += it->first;
      }
    }

  }
  return sum;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;

  vector<long long> initialNumbers;
  vector<long long> initialNumbers2;

  long long n;
  while (cin >> n)
  {
    initialNumbers.push_back(n);
    initialNumbers2.push_back(811589153 * n);
  }
  cout << "Part 1: " << solve(initialNumbers) << endl;
  cout << "Part 2: " << solve(initialNumbers2, 10) << endl;
  return 0;

}