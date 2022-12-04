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

vector<int> split(string line, string delimiters = ",./;=- ")
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

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<int> v;
  int sumPart1 = 0, sumPart2 = 0;

  while (getline(cin, line)) {
    v = split(line);
    if (v[0] <= v[2] && v[1] >= v[3] || v[2] <= v[0] && v[3] >= v[1])
    {
      sumPart1++;
      sumPart2++;
    }
    else if (v[0] == v[2] || v[0] == v[3] || v[1] == v[2] || v[1] == v[3] ||
      v[0] <= v[2] && v[1] <= v[3] && v[1] >= v[2] ||
      v[0] >= v[2] && v[0] <= v[3] && v[1] >= v[3])
    {
      sumPart2++;
    }
  }

  cout << "Part 1: " << sumPart1 << endl;
  cout << "Part 2: " << sumPart2 << endl;
}