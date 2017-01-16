//
// Created by sander on 1/16/17.
//

#include "HighscoreState.hpp"
#include "../../util/UnusedMacro.hpp"

namespace State {
    HighscoreState::HighscoreState(Game &context)
    : IGameState(context)
    {
        this->_read_from_file();
        this->_sort_list();
    }

    void HighscoreState::update(int time_since_last_update) {
        this->_context.SDL_facade.handle_sdl_events();

        Input keys = this->_context.SDL_facade.get_input();

        for (auto key : keys.keys_released) {
            switch (key) {
                case Key::ESC:
                    this->_write_to_file();
                    this->_context.set_new_state(std::make_shared<MenuState>(this->_context));
                    break;
                default:
                    break;
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image("res/helpscreen.bmp" , CoordinateInt{0,0});

        int current_y_pos = this->_start_pos_y;
        for (int i = 0; i < this->_scores.size(); i++) {
            this->_context.SDL_facade.draw_text(this->_scores[i].name, this->_font, this->_color, {this->_start_pos_x_names, current_y_pos});
            this->_context.SDL_facade.draw_text(to_string(this->_scores[i].score), this->_font, this->_color, {this->_start_pos_x_scores, current_y_pos});
            current_y_pos += this->_step_size_y;
        }

        this->_context.SDL_facade.render_buffer();
    }

    void HighscoreState::add_score(int time, string name) {
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

    void HighscoreState::_read_from_file() {
        string line;
        ifstream file("highscore.txt");
        vector<string> temp;
        if(file.is_open()){
            while(getline(file, line, '-')){
                line.erase(std::remove(line.begin(),line.end(), '\n'), line.end());
                temp.push_back(line);
            }
            for(int i = 0; i < temp.size(); i = i + 2){
                this->_scores.push_back({stoi(temp[i+1]), temp[i]});
            }
        }

    }

    void HighscoreState::_write_to_file() {
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

    void HighscoreState::_sort_list() {
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