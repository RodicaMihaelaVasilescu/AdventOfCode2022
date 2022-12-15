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

const int LINE = 2000000;
const int LIMIT = 4000000;

//const int LINE = 10;
//const int LIMIT = 20;

vector<int> split(string line, string delimiters = ",./;= ")
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
  Point sensor, beacon;
  int distance;
};

int GetManhattanDistance(Point p1, Point p2)
{
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void ExcludeNumbersOutOfLimits(int& n)
{
  if (n < 0)
  {
    n = 0;
  }
  else if (n > LIMIT)
  {
    n = LIMIT;
  }
}

void GetBeaconsLine(Pair item, set<int>& columnsWithoutBeacons, set<int>& beaconsToExclude, int line)
{
  if (item.sensor.y + item.distance >= line)
  {
    int dif = item.distance - abs(item.sensor.y - line);
    int a = item.sensor.x - dif;
    int b = item.sensor.x + dif;

    if (a > b)
    {
      return;
    }
    for (int i = a; i <= b; i++)
    {
      if (beaconsToExclude.find(i) == beaconsToExclude.end())
      {
        columnsWithoutBeacons.insert(i);
      }
    }
  }
}

void GetBeaconsLine2(Pair item, string& solution, int line)
{
  if (item.sensor.y + item.distance >= line)
  {
    int dif = item.distance - abs(item.sensor.y - line);
    int a = item.sensor.x - dif;
    int b = item.sensor.x + dif;

    ExcludeNumbersOutOfLimits(a);
    ExcludeNumbersOutOfLimits(b);

    if (a <= b)
    {
      solution.replace(a, b - a + 1, string(b - a + 1, '#'));
    }
  }
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<Pair> sensors;
  set<int> columnsWithoutBeacons;
  set<int> beaconsToExclude;

  for (int index = 0; (getline(cin, line)); index++) {
    auto words = split(line, "qwertyuiopasdfghjklzxcvbnmS,:.= ");
    Point sensor = Point{ words[0], words[1] };
    Point beacon = Point{ words[2], words[3] };
    sensors.push_back(Pair{ sensor, beacon, GetManhattanDistance(sensor, beacon) });
    if (beacon.y == LINE)
    {
      beaconsToExclude.insert(beacon.y);
    }
  }

  for (Pair const& item : sensors)
  {
    GetBeaconsLine(item, columnsWithoutBeacons, beaconsToExclude, LINE);
  }
  cout << "Part 1: " << columnsWithoutBeacons.size() << endl;

  string fullLine(LIMIT + 1, '#');

  for (int i = 0; i < LIMIT; i++)
  {
    string currentLine = string(LIMIT + 1, '.');
    for (Pair const& item : sensors)
    {
      GetBeaconsLine2(item, currentLine, i);
    }
    if (currentLine != fullLine)
    {
      for (int j = 0; j <= LIMIT; j++)
      {
        if (currentLine[j] == '.')
        {
          cout << "Part 2: " << 1ll * j * 4000000 + i;
          return 0;
        }
      }
    }
  }
}