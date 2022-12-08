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

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<vector<int>> v;
  int n, m = 0;

  while (getline(cin, line)) {
    m++;
    vector<int> ints;
    for (auto ch : line)
    {
      ints.push_back(ch - '0');
    }
    n = ints.size();
    v.push_back(ints);
  }

  vector<vector<int>> left(1001, vector<int>(1001, 0));
  for (int i = 0; i < n; i++)
  {
    int Max = v[i][0] - 1;
    for (int j = 0; j < m; j++)
    {
      if (v[i][j] > Max)
      {
        left[i][j] = 1;
        Max = v[i][j];
      }
    }
  }

  vector<vector<int>> right(1001, vector<int>(1001, 0));
  for (int i = 0; i < n; i++)
  {
    int Max = v[i][m - 1] - 1;
    for (int j = m - 1; j >= 0; j--)
    {
      if (v[i][j] > Max)
      {
        right[i][j] = 1;
        Max = v[i][j];
      }
    }
  }

  vector<vector<int>> top(1001, vector<int>(1001, 0));
  for (int j = 0; j < m; j++)
  {
    int Max = v[0][j] - 1;
    for (int i = 0; i < n; i++)
    {
      if (v[i][j] > Max)
      {
        top[i][j] = 1;
        Max = v[i][j];
      }
    }
  }

  vector<vector<int>> bottom(1001, vector<int>(1001, 0));
  for (int j = m - 1; j >= 0; j--)
  {
    int Max = v[n - 1][j] - 1;
    for (int i = n - 1; i >= 0; i--)
    {
      if (v[i][j] > Max)
      {
        bottom[i][j] = 1;
        Max = v[i][j];
      }
    }
  }

  int nr = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (left[i][j] == 1 || right[i][j] == 1 || top[i][j] == 1 || bottom[i][j] == 1)
      {
        nr++;
      }
    }
  }
  cout << "Part 1: " << nr << endl;

  int Max = 0;
  for (int i = 1; i < n - 1; i++)
  {
    for (int j = 1; j < m - 1; j++)
    {
      int nrLeft = 0;
      for (int j2 = j - 1; j2 >= 0; j2--)
      {
        nrLeft++;
        if (v[i][j2] >= v[i][j])
        {
          break;
        }
      }

      int nrRight = 0;
      for (int j2 = j + 1; j2 < m; j2++)
      {
        nrRight++;
        if (v[i][j2] >= v[i][j])
        {
          break;
        }
      }

      int nrTop = 0;
      for (int i2 = i - 1; i2 >= 0; i2--)
      {
        nrTop++;
        if (v[i2][j] >= v[i][j])
        {
          break;
        }
      }

      int nrBottom = 0;
      for (int i2 = i + 1; i2 < n; i2++)
      {
        nrBottom++;
        if (v[i2][j] >= v[i][j])
        {
          break;
        }
      }
      Max = max(nrLeft * nrTop * nrRight * nrBottom, Max);
    }
  }
  cout << "Part 2: " << Max << endl;

}