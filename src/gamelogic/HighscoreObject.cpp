//
// Created by sander on 1/16/17.
//

#include "HighscoreObject.hpp"

namespace GameLogic {
    HighscoreObject::HighscoreObject() {
        this->_read_from_file();
        this->_sort_list();
    }

    HighscoreObject::~HighscoreObject() {
        this->_write_to_file();
    }

    vector<highscore> HighscoreObject::get_scores() {
        return this->_scores;
    }

    void HighscoreObject::add_score(int time, string name) {
        if(name != "" && time > 0) {
            if (this->_scores.size() == 10) {
                int highest_number = time;
                int index = 20;

                for(int i = 0; i < this->_scores.size(); i++){
                    if (_scores[i].score > highest_number) {
                        highest_number = _scores[i].score;
                        index = i;
                    }
                }
                if(index != 20){
                    this->_scores[index].score = time;
                    this->_scores[index].name = name;
                    this->_sort_list();
                }

            } else {
                this->_scores.push_back({time, name});
                this->_sort_list();
            }
        }
    }

    void HighscoreObject::_read_from_file() {
        string line;
        ifstream file("highscore.txt");
        vector<string> temp;
        if(file.is_open()){
            while(getline(file, line, '-')){
                line.erase(remove(line.begin(),line.end(), '\n'), line.end());
                temp.push_back(line);
            }
            for(int i = 0; i < temp.size(); i = i + 2){
                this->_scores.push_back({stoi(temp[i+1]), temp[i]});
            }
        }

    }

    void HighscoreObject::_write_to_file() {
        ofstream file;
        file.open("highscore.txt");
        for(int i = 0; i < this->_scores.size(); i++){
            file << this->_scores[i].name << "-" << this->_scores[i].score;
            if(i < this->_scores.size() - 1){
                file << '-';
            }
        }
        file.close();
    }

    void HighscoreObject::_sort_list() {
        for (int i = 0; i < this->_scores.size(); i++) {
            for(int j = i + 1; j < this->_scores.size(); j++){
                if(this->_scores[i].score > this->_scores[j].score){

                    string temp_name = this->_scores[i].name;
                    int temp_score = this->_scores[i].score;

                    this->_scores[i].score = this->_scores[j].score;
                    this->_scores[i].name = this->_scores[j].name;
                    this->_scores[j].score = temp_score;
                    this->_scores[j].name = temp_name;
                }
            }
        }
    }
}