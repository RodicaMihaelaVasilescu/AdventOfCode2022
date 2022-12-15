// part 2 . Warning! the solution is not efficient. It takes over 5h of running in release mode
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

struct Point
{
  int x;
  int y;
};

struct Pair
{
  int id;
  Point s, b;
  int d;
};


static int getDist(Point p1, Point p2)
{
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int LIMIT = 4000000;

void getBeaconsLine(Pair item, string& sol, int line)
{
  if (item.s.y + item.d >= line)
  {
    int dif = item.d - abs(item.s.y - line);
    int a = item.s.x - dif;
    int b = item.s.x + dif;

    if (a < 0)
	{
      a = 0;
	}
    if (a > LIMIT)
	{
      a = LIMIT;
	}
    if (b < 0)
	{
      b = 0;
	}
    if (b > LIMIT)
	{
      b = LIMIT;
	}
    if (a > b)
    {
      return;
    }
    sol.replace(a, b - a + 1, string(b - a + 1, '#'));

  }
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<Pair> sensors;

  int ind = 0;
  while (getline(cin, line)) {
    if (line != "")
    {
      auto words = split2(line, "qwertyuiopasdfghjklzxcvbnmS,:.= ");
      Point s = Point{ words[0], words[1] };
      Point b = Point{ words[2], words[3] };
      sensors.push_back(Pair{ ind, s, b, getDist(s, b) });
      ind++;
    }
  }

  string full(LIMIT + 1, '#');
  for (int i = 0; i < LIMIT; i++)
  {
    string sol = string(LIMIT + 1, '.');
    for (auto item : sensors)
    {
      getBeaconsLine(item, sol, i);
    }
    if (sol != full)
    {
      for (int j = 0; j <= LIMIT; j++)
      {
        if (sol[j] == '.')
        {
          cout << i << " * " << j << " = " << 1ll * j * 4000000 + i;
          return 0;
        }
      }
    }
  }
}