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
#include <tuple>
#include <bitset>

using namespace std;

vector<string> split(string line, string delimiters = ",./;= ")
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

map<string, long long> monkeyRes;
map<string, tuple<string, char, string>> monkeyOp;

long long getResult(string name)
{
  if (monkeyRes.count(name))
  {
    return monkeyRes[name];
  }
  tuple<string, char, string> t = monkeyOp[name];

  auto m1 = get<0>(t);
  auto op = get<1>(t);
  auto m2 = get<2>(t);

  if (op == '+')
  {
    return getResult(m1) + getResult(m2);
  }
  else if (op == '-')
  {
    return getResult(m1) - getResult(m2);
  }
  else if (op == 47)
  {
    return getResult(m1) / getResult(m2);
  }
  else if (op == '*')
  {
    return getResult(m1) * getResult(m2);
  }
  cout << "out";
  return 0;
}
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;

  while (getline(cin, line)) {
    auto words = split(line, " ,:");
    if (words.size() == 2)
    {
      monkeyRes[words[0]] = stol(words[1]);
    }
    else
    {
      monkeyOp[words[0]] = { words[1],char(words[2][0]),words[3] };
    }
  }

  auto child1 = getResult(get<0>(monkeyOp["root"]));
  auto child2 = getResult(get<2>(monkeyOp["root"]));

  auto root = getResult("root");

  cout << "Part 1: " << root;
  cout << " (" << child1 << " " << get<1>(monkeyOp["root"]) << " " << child2 << ")" << endl;

  long long a = 0;
  long long b = root * 2 + 1;

  while (true)
  {
    unsigned long long m = a / 2 + b / 2;
    monkeyRes["humn"] = m;
    long long r1 = getResult(get<0>(monkeyOp["root"]));
    long long r2 = getResult(get<2>(monkeyOp["root"]));
    if (r1 == r2)
    {
      do
      {
        m--;
        monkeyRes["humn"] = m;
        r1 = getResult(get<0>(monkeyOp["root"]));
        r2 = getResult(get<2>(monkeyOp["root"]));
      } while (r1 == r2);
      cout << "Part 2: " << m + 1 << endl;
      break;
    }

    if (r1 < r2 && child1 < child2 || r1 > r2 && child1 > child2)
    {
      a = m - 1;
    }
    else
    {
      b = m + 1;
    }
  }
  return 0;
}