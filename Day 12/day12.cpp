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
#include <queue>

using namespace std;

int lin[] = { 1,-1,0,0 };
int col[] = { 0,0,1,-1 };

struct queueItem {
  int x;
  int y;
  int step;
};

int BFS(vector<string>v, pair<int, int> s, pair<int, int> e)
{
  vector<vector<int>> vis(v.size(), vector<int>(v[0].size(), 0));
  queue <queueItem> q;

  vis[s.first][s.second] = 0;
  q.push(queueItem{ s.first,s.second,1 });
  int Min = 999999;

  while (!q.empty())
  {
    auto item = q.front();
    q.pop();

    for (int dir = 0; dir < 4; dir++)
    {
      queueItem item2 = queueItem{ item.x + lin[dir],item.y + col[dir],item.step + 1 };

      if (!(item2.x >= 0 && item2.y >= 0 && item2.x < v.size() && item2.y < v[0].size() && vis[item2.x][item2.y] == 0))
      {
        continue;
      }
      if (vis[e.first][e.second] < Min && vis[e.first][e.second] != 0)
      {
        Min = vis[e.first][e.second];
      }
      if (v[item2.x][item2.y] <= v[item.x][item.y] + 1)
      {
        q.push(item2);
        vis[item2.x][item2.y] = item.step;
      }
    }
  }

  return Min;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<string> input;
  pair<int, int> s, e;

  int index = 0;
  while (getline(cin, line)) {
    if (line != "")
    {
      for (int i = 0; i < line.size(); i++)
      {
        if (line[i] == 'S') {
          s = { index, i };
        }
        else if (line[i] == 'E') {
          e = { index, i };
        }
      }
      input.push_back(line);
      index++;
    }
  }

  input[s.first][s.second] = 'a' - 1;
  cout << "Part 1: " << BFS(input, s, e) << endl;

  int minimumPath = 9999999;
  for (int i = 0; i < input.size(); i++)
  {
    for (int j = 0; j < input[i].size(); j++)
    {
      if (input[i][j] == 'a')
      {
        minimumPath = min(minimumPath, BFS(input, { i,j }, e));
      }
    }
  }

  cout << "Part 2: " << minimumPath << endl;
}