//
// Created by sander on 1/16/17.
//

#ifndef MINOR_VIDYA_HIGHSCOREOBJECT_HPP
#define MINOR_VIDYA_HIGHSCOREOBJECT_HPP

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::stoi;
using std::to_string;
using std::ifstream;
using std::ofstream;
using std::remove;
using std::map;


struct highscore {
    int score;
    std::string name;
};

namespace GameLogic {

    class HighscoreObject {
    public:
        HighscoreObject();
        ~HighscoreObject();
        void add_score(int time, string name);
        vector<highscore> get_scores(string level_name);
        map<string, vector<highscore>> get_all_scores();

    private:
        map<string, vector<highscore>> _scores;
        void _read_from_file();
        void _write_to_file();
        void _sort_list();
    };
}
#endif //MINOR_VIDYA_HIGHSCOREOBJECT_HPP
