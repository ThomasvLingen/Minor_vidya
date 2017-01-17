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

    vector<highscore> HighscoreObject::get_scores(string level_name) {
        return this->_scores.find(level_name)->second;
    }

    void HighscoreObject::add_score(int time, string level_name) {
        if(level_name != "" && time > 0) {
            if(!(this->_scores.find(level_name) != this->_scores.end())){
                vector<highscore> tempvec;
                tempvec.push_back({time, "xxxx"});
                this->_scores.insert(std::pair<string, vector<highscore>>(level_name, tempvec));
            }
            else if (this->_scores.find(level_name)->second.size() == 10) {
                int highest_number = time;
                int index = 20;

                for(int i = 0; i < (int)this->_scores.find(level_name)->second.size(); i++){
                    if (this->_scores.find(level_name)->second[i].score > highest_number) {
                        highest_number = this->_scores.find(level_name)->second[i].score;
                        index = i;
                    }
                }
                if(index != 20){
                    this->_scores.find(level_name)->second[index].score = time;
                    this->_sort_list();
                }

            } else {
                this->_scores.find(level_name)->second.push_back({time, "xxx"});
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
            for(int i = 0; i < (int)temp.size(); i = i + 2){
                if(this->_scores.find(temp[i]) != this->_scores.end()){
                    this->_scores.find(temp[i])->second.push_back({stoi(temp[i+1]), "xxxx"});
                } else {
                    vector<highscore> tempvec;
                    tempvec.push_back({stoi(temp[i+1]), "xxxx"});
                    this->_scores.insert(std::pair<string, vector<highscore>>(temp[i], tempvec));
                }
            }
        }

    }

    map<string, vector<highscore>> HighscoreObject::get_all_scores(){
        return this->_scores;
    };

    void HighscoreObject::_write_to_file() {
        int counter = 0;
        ofstream file;
        file.open("highscore.txt");
        for(map<string, vector<highscore>>::iterator it = this->_scores.begin(); it != this->_scores.end(); it++){
            for(int i = 0; i < (int)it->second.size(); i++){
                file << it->first << "-" << it->second[i].score;
                if(i < (int)it->second.size() - 1){
                    file << '-';
                }
            }
            if(counter < (int)this->_scores.size()){
                file << '-';
            }
            counter++;
        }
        file.close();
    }

    void HighscoreObject::_sort_list() {
        for (map<string, vector<highscore>>::iterator it = this->_scores.begin(); it != this->_scores.end(); it++) {
            for (int i = 0; i < (int)it->second.size(); i++) {
                for (int j = i + 1; j < (int)it->second.size(); j++) {
                    if (it->second[i].score > it->second[j].score) {

                        int temp_score = it->second[i].score;

                        it->second[i].score = it->second[j].score;
                        it->second[j].score = temp_score;
                    }
                }
            }
        }
    }
}