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

vector<int> split2(string line, string delimiters = ",./;= ")
{
  vector<int> words;

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
      words.push_back(stoi(newWord));
    }
  }
  return words;
}

struct point
{
  int x;
  int y;
};

map<pair<int, int>, char> matrix, initialMatrix;

void fall(point& drop)
{
  matrix[{drop.x, drop.y}] = 0;
  if (matrix[{drop.x + 1, drop.y }] == 0)
  {
    drop.x++;
  }
  else if (matrix[{drop.x + 1, drop.y - 1 }] == 0)
  {
    drop.x++;
    drop.y--;
  }
  else if (matrix[{drop.x + 1, drop.y + 1 }] == 0)
  {
    drop.x++;
    drop.y++;
  }
  matrix[{drop.x, drop.y}] = 'o';
}


bool canFall(point drop)
{
  return matrix[{drop.x + 1, drop.y }] == 0 || matrix[{drop.x + 1, drop.y - 1 }] == 0 || matrix[{drop.x + 1, drop.y + 1 }] == 0;
}

void main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;

  point Min = point{ INT_MAX,INT_MAX };
  point Max = point{ 0,0 };

  while (getline(cin, line)) {

    auto words = split2(line, ", ->");
    point start = point{ words[0], words[1] };

    for (int i = 2; i < words.size() - 1; i += 2)
    {
      point end = point{ words[i] , words[i + 1] };

      if (start.x == end.x)
      {
        for (int k = min(start.y, end.y); k <= max(start.y, end.y); k++)
        {
          Min.x = min(Min.x, k);
          Max.x = max(Max.x, k);
          matrix[{k, start.x}] = '#';
        }
      }
      else if (start.y == end.y)
      {
        for (int k = min(start.x, end.x); k <= max(start.x, end.x); k++)
        {
          Min.y = min(Min.y, k);
          Max.y = max(Max.y, k);
          matrix[{start.y, k}] = '#';
        }
      }
      start = end;
    }
  }

  initialMatrix = matrix;
  vector<point> drops;
  bool overflow = false;
  while (!overflow)
  {
    point drop = point{ 0,500 };
    while (canFall(drop))
    {
      fall(drop);
      if (drop.x >= Max.x)
      {
        overflow = true;
        cout << "Part 1: " << drops.size() << endl;
        break;
      }
    }
    drops.push_back(drop);
  }

  matrix = initialMatrix;
  drops.clear();
  Max.x += 2;
  for (int i = -10000; i <= 10000; i++)
  {
    matrix[{ Max.x, i}] = '#';
  }

  while (true)
  {
    point drop = point{ 0,500 };
    while (canFall(drop))
    {
      fall(drop);
    }
    drops.push_back(drop);
    if (drop.x == 0 && drop.y == 500)
    {
      cout << "Part 2: " << drops.size() << endl;
      break;
    }
  }
}