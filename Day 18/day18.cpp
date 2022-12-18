//this solution takes less than 3 minutes in release mode
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

// coordinates of a cube of 1 (0,0,0)
//(0, 0, 0), (1, 0, 0), (1, 1, 0), (0, 1, 0), (0, 0, 1), (1, 0, 1), (1, 1, 1), and (0, 1, 1)
vector<tuple<int, int, int>> getPoints(tuple<int, int, int> point)
{
  int x = get<0>(point);
  int y = get<1>(point);
  int z = get<2>(point);
  return { { x, y, z }, {x + 1,y,z}, {x + 1, y + 1, 0}, {0, y + 1, 0}, {0, 0, z + 1}, {x + 1, 0, z + 1}, {x + 1, y + 1, z + 1}, {0,y + 1,z + 1} };
}

vector<vector<tuple<int, int, int>>> getFaces(tuple<int, int, int> point)
{
  int x = get<0>(point);
  int y = get<1>(point);
  int z = get<2>(point);
  vector<vector<tuple<int, int, int>>>faces;
  vector<tuple<int, int, int>>face1 = { { x,   y,   z  }, { x   ,y   ,z + 1 }, { x + 1 ,y   ,z + 1 }, { x + 1 ,y  ,z   } }; // bottom
  vector<tuple<int, int, int>>face2 = { { x + 1 ,y + 1, z  }, { x + 1 ,y + 1 ,z + 1 }, { x + 1 ,y   ,z + 1 }, { x + 1 ,y  ,z   } };// front
  vector<tuple<int, int, int>>face3 = { { x   ,y + 1, z  }, { x   ,y + 1 ,z + 1 }, { x + 1 ,y + 1 ,z + 1 }, { x + 1, y + 1,z   } };// top
  vector<tuple<int, int, int>>face4 = { { x + 1 ,y + 1, z  }, { x   ,y + 1 ,z   }, { x   ,y   ,z   }, { x + 1 ,y  ,z   } }; // left
  vector<tuple<int, int, int>>face5 = { { x + 1 ,y + 1, z + 1}, { x   ,y + 1 ,z + 1 }, { x   ,y   ,z + 1 }, { x + 1 ,y  ,z + 1 } };// righr
  vector<tuple<int, int, int>>face6 = { { x   ,y + 1, z  }, { x   ,y + 1 ,z + 1 }, { x  , y   ,z + 1 }, { x   ,y  ,z   } }; //back
  faces.push_back(face1);
  faces.push_back(face2);
  faces.push_back(face3);
  faces.push_back(face4);
  faces.push_back(face5);
  faces.push_back(face6);

  return faces;
}
struct cube
{
  int index;
  tuple<int, int, int> p;
  vector<vector<tuple<int, int, int>>>faces;
};

bool isTheSameFace(vector<tuple<int, int, int>> face, vector<tuple<int, int, int>> otherFace)
{
  map<tuple<int, int, int>, bool > found;
  for (auto i : face)
  {
    found[i] = true;
  }
  for (auto i : otherFace)
  {
    if (!found[i])
    {
      return false;
    }
  }
  return true;
}
bool isFaceConnectedToAnotherCube(vector<tuple<int, int, int>> face, cube other)
{
  int distinctFaces = 0;
  int ind = 0;
  for (auto otherFace : other.faces)
  {
    ind++;
    if (ind == 6)
    {
      int bkp = 0;
    }
    if (isTheSameFace(face, otherFace))
    {
      return true;
    }
  }
  return false;
}

int getNumberOfDistinctFaces(vector<cube> cubes)
{
  int distinctFaces = 0;
  int all = cubes.size() * 6;
  for (auto cube : cubes)
  {
    int faceIndex = 0;
    for (auto face : cube.faces)
    {
      faceIndex++;
      if (faceIndex == 2) {
        int bkp = 0;
      }
      bool isDistinct = true;
      for (auto otherCube : cubes)
      {
        if (otherCube.index != cube.index)
        {
          if (isFaceConnectedToAnotherCube(face, otherCube))
          {
            isDistinct = false;
            break;
          }
        }
      }
      if (isDistinct)
      {
        distinctFaces++;
      }
    }
  }
  return distinctFaces;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<cube> cubes;
  vector<vector<tuple<int, int, int>>> p;

  int id = 0;
  while (getline(cin, line)) {
    auto coords = split2(line);
    cubes.push_back(cube{ id++,{ coords[0],coords[1], coords[2] } });

  }

  for (auto& i : cubes)
  {
    i.faces = getFaces(i.p);
  }

  cout << getNumberOfDistinctFaces(cubes);

}
