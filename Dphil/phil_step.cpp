#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define VIT(i, v) for (i = 0; i < v.size(); i++) 
#define IT(it, ds) for (it = ds.begin(); it != ds.end(); it++)
#define FUP(i, n) for (i = 0; i < n; i++)

typedef map<int, string> ISmap;
typedef map<int, int> IImap;
typedef map<string, int> SImap;
typedef map<string, string> SSmap;

typedef ISmap::iterator ISmit;
typedef IImap::iterator IImit;
typedef SSmap::iterator SSmit;
typedef SImap::iterator SImit;

typedef vector <int> IVec;
typedef vector <double> DVec;
typedef vector <string> SVec;

int main(int argc, char **argv)
{
  int t, tt, i;
  int index;
  vector <string> sv;
  istringstream ss;
  ifstream fin;
  string line, s;
  map <int, vector <string> > m;
  map <int, vector <string> >::iterator mit;

  if (argc != 2) {
    fprintf(stderr, "usage: phil_step file\n");
    exit(1);
  }

  fin.open(argv[1]);
  if (fin.fail()) perror(argv[1]);

  t = 0;
  index = 0;
  printf("NOPRINT\n");
  fflush(stdout);

  while (getline(fin, line)) {
    ss.clear();
    ss.str(line);
    sv.clear();
    while (ss >> s) sv.push_back(s);
    tt = atoi(sv[0].c_str());
    m[tt].push_back(line);
  }

  index = 0;
  mit = m.begin();

  while (1) {
    for (i = 0; i < m[index].size(); i++) printf("%s\n", m[index][i].c_str());
    mit++;
    if (mit == m.end()) exit(0);
    index = mit->first;
    for (i = 0; i < m[index].size(); i++) fprintf(stderr, "%s\n", m[index][i].c_str());
    getline(cin, line);
  }
}
