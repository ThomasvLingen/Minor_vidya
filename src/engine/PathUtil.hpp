//
// Created by mafn on 11/29/16.
//

#ifndef MINOR_VIDYA_PATHUTIL_HPP
#define MINOR_VIDYA_PATHUTIL_HPP

#include <string>

namespace Engine {
    using std::string;

    class PathUtil {
    public:
        static string get_run_path();
    private:
        static bool _initialised;
        static void _init_run_path();
        static string _run_path;
    };
}


#endif //MINOR_VIDYA_PATHUTIL_HPP
