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

int binaryToDecimal(string binaryNumber)
{
  return stoi(binaryNumber, 0, 2);
}

string decimalToBinary(int n)
{
  string binary = std::bitset<8>(n).to_string();
  return binary;
}

void replaceAll(string& s, const string& search, const string& replace)
{
  for (size_t pos = 0; ; pos += replace.length())
  {
    // Locate the substring to replace
    pos = s.find(search, pos);
    if (pos == string::npos) break;
    // Replace by erasing and inserting
    s.erase(pos, search.length());
    s.insert(pos, replace);
  }
}
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
struct coord
{
  int x;
  int y;
};

struct line
{
  vector<coord> v;
};

int xmin = 999999, xmax = 0, ymin = 99999, ymax = 0;
void print(map<pair<int, int>, char>m)
{
  for (int i = 0; i < 15; i++)
  {
    for (int j = 450; j < 550; j++)
    {
      if (i == 0 && j == 500)
      {
        cout << "+";
      }
      else  if (m[{i, j}] == 0)
      {
        cout << " ";
      }
      else
      {
        cout << m[{i, j}];
      }
    }
    cout << endl;
  }
  cout << endl;
}


coord fall(map<pair<int, int>, char>m, coord drop)
{
  if (m[{drop.x + 1, drop.y }] == 0)
  {
    drop.x++;
  }
  else if (m[{drop.x + 1, drop.y - 1 }] == 0)
  {
    drop.x++;
    drop.y--;
  }
  else if (m[{drop.x + 1, drop.y + 1 }] == 0)
  {
    drop.x++;
    drop.y++;
  }
  return drop;
}

void main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string s;
  vector<line> v;
  //vector<int> fr(1000, 0);
  //vector<vector<int>> vec(1001, vector<int>(1001, 0));

  while (getline(cin, s)) {
    if (s == "")
    {

    }
    else
    {
      auto words = split2(s, ", ->");
      auto l = line();
      for (int i = 0; i < words.size(); i++)
      {
        l.v.push_back(coord{ words[i],words[i + 1] });
        i++;
      }
      v.push_back(l);
    }
  }

  map<pair<int, int>, char> m;

  for (auto rock : v)
  {
    auto s = rock.v[0];
    for (int k = 1; k < rock.v.size(); k++)
    {
      auto e = rock.v[k];
      if (s.x == e.x)
      {
        for (int i = min(s.y, e.y); i <= max(s.y, e.y); i++)
        {
          xmin = min(xmin, i);
          xmax = max(xmax, i);
          m[{i, s.x}] = '#';
        }
      }
      else if (s.y == e.y)
      {
        for (int j = min(s.x, e.x); j <= max(s.x, e.x); j++)
        {
          ymin = min(ymin, j);
          ymax = max(ymax, j);
          m[{s.y, j}] = '#';
        }
      }

      s = e;
    }
  }

  vector<coord> drops;
  int j = 0;
  while (j++ < 1000)
  {

    //cout << j << endl;

    coord drop = coord{ 0,500 };
    auto prevDrop = drop;
    int i = 0;
    do
    {
      i++;
      if (drop.x > ymax)
      {
        int cnt = 0;
        for (auto val : m)
        {
          if (val.second == '0')
            cnt++;
        }
        //cout << cnt - 1 << endl;
        cout << j - 1 << endl;
        return;
      }
      prevDrop = drop;
      drop = fall(m, drop);
      m[{prevDrop.x, prevDrop.y}] = 0;
      m[{drop.x, drop.y}] = 'o';
      if (drop.x == 0 && drop.y == 500)
      {
        return;
      }
    } while (!(drop.x == prevDrop.x && drop.y == prevDrop.y));

    //print(m);
    drops.push_back(prevDrop);
  }

  //print(m);

  //for (auto i : v)
  //{
  //  cout << i.x << "," << i.y << endl;
  //}
}