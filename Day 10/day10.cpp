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
#include "AdventOfCode2022.h"

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

struct instruction
{
  string name;
  int val = 0;
};

int cycleOf40 = 20;
int counter = 0;
int strength = 0;

void tick(int x, int& crt)
{
  //part1
  counter++;
  if (counter == cycleOf40 && cycleOf40 <= 220)
  {
    strength += x * cycleOf40;
    cycleOf40 += 40;
  }

  // part2
  if (x == crt || x + 1 == crt || x + 2 == crt)
  {
    cout << "#";
  }
  else
  {
    cout << " ";
  }

  crt++;
  if (crt == 41)
  {
    crt = 1;
    cout << endl;
  }
}

void compute(vector<instruction> v)
{
  int x = 1, crt = 1;
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i].name == "noop")
    {
      tick(x, crt);
    }
    else if (v[i].name == "addx")
    {
      tick(x, crt);
      tick(x, crt);
      x += v[i].val;
    }
  }
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<instruction> instructions;

  while (getline(cin, line)) {

    auto words = split(line);
    if (words[0] == "noop")
    {
      instruction x;
      x.name = words[0];
      instructions.push_back(x);
    }
    else if (words[0] == "addx")
    {
      instruction x;
      x.name = words[0];
      x.val = stoi(words[1]);
      instructions.push_back(x);
    }
  }

  cout << "Part 2: \n";
  compute(instructions);
  cout << "\nPart 1: " << strength;
}