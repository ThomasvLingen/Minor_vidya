//
// Created by mafn on 11/29/16.
//

#ifndef MINOR_VIDYA_PATHUTIL_HPP
#define MINOR_VIDYA_PATHUTIL_HPP

#define VIDYA_RUNPATH ::Engine::PathUtil::get_run_path()

#include <string>

namespace Engine {
    using std::string;

    class PathUtil {
    public:
        static string get_run_path();
    };
}


#endif //MINOR_VIDYA_PATHUTIL_HPP
