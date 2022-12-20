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

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  deque<pair<int, int>> input;
  vector<int> initialNumbers;

  int x;
  int id = 0;
  while (cin >> x) {
    input.push_back({ x,id++ });
    initialNumbers.push_back(x);

  }

  int n = input.size();
  for (int i = 0; i < initialNumbers.size(); i++)
  {
    if (initialNumbers[i] == 0)
    {
      continue;
    }

    while (input[0].second != i)
    {
      rotate(input.begin(), input.begin() + 1, input.end());
    }
    auto item = *input.begin();
    input.pop_front();
    int rotationNumber = abs(item.first) % input.size();

    while (rotationNumber--)
    {
      if (item.first > 0)
      {
        rotate(input.begin(), input.begin() + 1, input.end());
      }
      else
      {
        rotate(input.rbegin(), input.rbegin() + 1, input.rend());
      }
    }
    input.push_front(item);
    //for (auto i : input)
    //{
    //  cout << i.first << " ";
    //}
    //cout << endl;
  }

  while (input[0].first != 0)
  {
    rotate(input.begin(), input.begin() + 1, input.end());
  }

  int rotationNr = 3000;
  int sum = 0;
  while (rotationNr--)
  {
    rotate(input.begin(), input.begin() + 1, input.end());
    if (rotationNr == 2000)
    {
      sum += input[0].first;
    }
    if (rotationNr == 1000)
    {
      sum += input[0].first;
    }
  }
  sum += input[0].first;
  cout << sum;

  return 0;
}