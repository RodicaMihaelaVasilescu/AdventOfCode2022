// credits geeksforgeeks: https://www.geeksforgeeks.org/maximum-cost-path-in-an-undirected-graph-such-that-no-edge-is-visited-twice-in-a-row/

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

struct valve
{
  int index;
  string name;
  int rate = 0;
  set<string> namesLeadsTo;
  vector<valve> leadsTo;
};

map<tuple<int, int, int>, int> dp;
vector<vector<pair<int, int>>> edges;

// To store largest
// cost leaf vertex
int best = 0;

// DFS Traversal to find the update
// the maximum cost of from any
// node to leaf
int DFS(vector<int> cost, int previous, int u, int time)
{
  if (time == 0)
  {
    return 0;
  }

  if (dp[make_tuple(previous, u, time)] != 0)
  {
    return dp[make_tuple(previous, u, time)];
  }


  // Initially assuming edge
  // not to be traversed
  int answer = 0;
  int check = 1;

  // Bitwise AND the current
  // check with the returned
  // check by the previous
  // DFS Call
  check <<= previous;

  if ((check & u) == 0 && cost[previous] != 0)
  {
    // Add cost of vertex
    // to the answer
    auto nextCost = cost[previous] * (time - 1) + DFS(cost, previous, check | u, time - 1);
    answer = max(answer, nextCost);
  }

  for (auto edge : edges[previous])
  {
    // Back edge found so,
    // edge can be part of
    // traversal
    answer = max(answer, DFS(cost, edge.second, u, time - 1));
  }

  // Updates total cost of parent
  // including child nodes
  dp[make_tuple(previous, u, time)] = answer;
  return answer;
}

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<valve> valves;
  vector<int> cost;

  int index = 0;
  int start = 0;
  while (getline(cin, line)) {
    if (line != "")
    {
      line[0] = 'v';
      auto words = split(line, "qwertyuiopasdfghjklzxcvbnm =;,");
      set<string>names;
      for (int i = 2; i < words.size(); i++)
      {
        names.insert(words[i]);
      }
      if (words[0] == "AA")
      {
        start = index;
      }
      valves.push_back(valve{ index, words[0], stoi(words[1]), names });
      cost.push_back(stoi(words[1]));
      index++;
    }
  }

  for (auto& valve : valves)
  {
    vector < pair<int, int>> currentEdge;
    for (auto nameLeadsTo : valve.namesLeadsTo)
    {
      for (auto& otherValve : valves)
      {
        if (nameLeadsTo == otherValve.name) {
          valve.leadsTo.push_back(otherValve);
          currentEdge.push_back({ 0,otherValve.index });
        }
      }
    }
    edges.push_back(currentEdge);
  }

  cout << "Part 1: " << DFS(cost, start, 0, 30) << endl;
}