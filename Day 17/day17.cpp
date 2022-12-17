// It takes less than a minute in release mode

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
#include <list>

using namespace std;

int WIDTH = 7;

struct shape
{
  string name;
  vector<pair<int, int>> p;
  int height;
};


bool PlaceShape(map<pair<int, int>, char>& matrix, shape s, pair<int, int> start, pair<int, int> end)
{
  auto matrix2 = matrix;
  for (auto i : s.p)
  {
    matrix2[{i.first + start.first, i.second + start.second}] = 0;
  }

  //place shape
  for (auto i : s.p)
  {
    if (!(i.first + end.first >= 0 && i.second + end.second >= 0 && i.second + end.second < WIDTH) ||
      matrix2[{i.first + end.first, i.second + end.second}] != 0)
    {
      return false;
    }
    matrix2[{i.first + end.first, i.second + end.second}] = '#';
  }
  matrix = matrix2;
  return true;
}

void Print(map<pair<int, int>, char> m, int height)
{
  for (int i = height; i >= 0; i--)
  {
    for (int j = 0; j <= WIDTH; j++)
    {
      if (m[{i, j}] == 0)
      {
        cout << '.';
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

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  vector<shape> shapes;

  shapes.push_back(shape{ "-", vector<pair<int,int>>{ {0,0},{0,1},{0,2},{0,3} }, 1 });
  shapes.push_back(shape{ "+", vector<pair<int,int>>{ {0,1},{1,0},{1,1},{1,2},{2,1}} ,3 });
  shapes.push_back(shape{ "L", vector<pair<int,int>>{ {1,2},{2,2},{0,2},{0,1},{0,0}} ,3 });
  shapes.push_back(shape{ "I", vector<pair<int,int>>{ {0,0},{1,0},{2,0},{3,0}}, 4 });
  shapes.push_back(shape{ "S", vector<pair<int,int>>{ {0,0},{0,1},{1,0},{1,1}},2 });

  string input;
  cin >> input;

  map<pair<int, int>, char> matrix;
  int shapeIndex = 0;
  shape currentShape = shapes[shapeIndex];
  pair<int, int> currentCoordinates = { 3,2 };

  int inputIndex = 0;

  int maxTall = 0;
  map<tuple<int, int, string>, int> previousConfigurationOccurrence;
  map<int, int> talls;

  while (true)
  {
    // move left or right one unit
    int horizontalOffset = input[inputIndex % input.size()] == '<' ? -1 : +1;
    inputIndex++;
    if (PlaceShape(matrix, currentShape, currentCoordinates, { currentCoordinates.first, currentCoordinates.second + horizontalOffset }))
    {
      currentCoordinates = { currentCoordinates.first,currentCoordinates.second + horizontalOffset };
    }
    // move down one unit
    if (PlaceShape(matrix, currentShape, currentCoordinates, { currentCoordinates.first - 1,currentCoordinates.second }))
    {
      currentCoordinates = { currentCoordinates.first - 1,currentCoordinates.second };
    }
    // If a downward movement would have caused a falling rock to move into the floor or an already-fallen rock, 
    // the falling rock stops where it is 
    else
    {
      maxTall = max(maxTall, abs(currentCoordinates.first + currentShape.height));
      talls[shapeIndex] = maxTall;
      currentCoordinates = { maxTall + 3, 2 };

      string maxTallLine = "";
      for (int i = 0; i < WIDTH; i++)
      {
        maxTallLine += matrix[{maxTall, i}];
      }

      shapeIndex++;
      currentShape = shapes[shapeIndex % shapes.size()];

      if (shapeIndex == 2022)
      {
        cout << "Part 1: " << maxTall << endl;

        long long n = 1000000000000;
        int previousShapeSimilarWith2022 = previousConfigurationOccurrence[{2022 % shapes.size(), inputIndex% input.size(), maxTallLine}];

        int indexesDifference = 2022 - previousShapeSimilarWith2022;
        int tallsDifference = talls[2022 - 1] - talls[previousShapeSimilarWith2022 - 1];

        cout << "Part 2: " << talls[n % indexesDifference] + n / indexesDifference * tallsDifference - 1;

        return 0;
      }
      previousConfigurationOccurrence[{shapeIndex% shapes.size(), inputIndex% input.size(), maxTallLine}] = shapeIndex;
    }
  }
}