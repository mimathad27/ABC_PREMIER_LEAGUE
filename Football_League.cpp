#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

struct Team {
    string name;
    string town;
    string stadium;
};

struct Match {
    string homeTeam;
    string awayTeam;
    string localTown;
    string stadium;
    int leg;
    int weekend;
}
