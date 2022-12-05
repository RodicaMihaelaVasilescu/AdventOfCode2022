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
#include <stack>

using namespace std;


vector<int> split(string line, string delimiters = ",./;=[]abcdefghijklmnopqrstuvwxyz ")
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
  vector<vector<char>> cratesMatrix;
  vector<stack<char>> stacksPart1, stacksPart2;
  vector<vector<int>> instructions;

  while (getline(cin, line)) {
    if (line == "" || line[1] == '1')
    {
      continue;
    }
    if (line[0] == 'm')
    {
      vector<int> instruction = split(line);
      instructions.push_back(instruction);
    }
    else
    {
      vector<char> crates;
      for (int i = 0; i < line.size(); i += 3)
      {
        string substr = line.substr(i, 3);
        crates.push_back(substr[1]);
        i++; // skip space
      }
      cratesMatrix.push_back(crates);
    }
  }

  for (int j = 0; j < cratesMatrix[0].size(); j++)
  {
    stack<char> crates;
    for (int i = cratesMatrix.size() - 1; i >= 0; i--)
    {
      if (cratesMatrix[i][j] != ' ')
      {
        crates.push(cratesMatrix[i][j]);
      }
    }
    stacksPart1.push_back(crates);
    stacksPart2.push_back(crates);
  }

  for (auto instruction : instructions)
  {
    int cratesToMove = instruction[0], moveFrom = instruction[1] - 1, moveTo = instruction[2] - 1;
    vector<int> crates;
    while (cratesToMove--)
    {
      stacksPart1[moveTo].push(stacksPart1[moveFrom].top());
      stacksPart1[moveFrom].pop();

      crates.push_back(stacksPart2[moveFrom].top());
      stacksPart2[moveFrom].pop();
    }

    for (int i = crates.size() - 1; i >= 0; i--)
    {
      stacksPart2[moveTo].push(crates[i]);
    }
  }

  cout << "Part 1: ";
  for (auto crater : stacksPart1)
  {
    cout << crater.top();
  }
  cout << endl;

  cout << "Part 2: ";
  for (auto crater : stacksPart2)
  {
    cout << crater.top();
  }
  cout << endl;
}