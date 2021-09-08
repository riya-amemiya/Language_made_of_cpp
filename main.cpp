#include "main.hpp"
std::vector<std::string> split(std::string str, std::string separator) {
    if (separator == "") {
        return {str};
    };
    std::vector<std::string> result;
    std::string tstr = str + separator;
    long l = tstr.length(), sl = separator.length();
    std::string::size_type pos = 0, prev = 0;
    for (; pos < l && (pos = tstr.find(separator, pos)) != std::string::npos; prev = (pos += sl)) {
        result.emplace_back(tstr, prev, pos - prev);
    }
    return result;
}

int main(int argc, const char **argv) {
    std::ifstream ifs(argv[1]);
    if (ifs.fail()) {
        std::cerr << "失敗" << std::endl;
        return -1;
    }
    std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    std::vector<std::string> code = split(str, "\n");
    std::vector<std::string> token = {};
    std::string stack = "";
    for (int i = 0; i < code.size(); i++) {
        std::vector<std::string> v = split(code[i], ";");
        for (int y = 0; y < v.size(); y++) {
            token.push_back(v[y]);
        }
    }
    for (int n = 0; n < token.size(); n++) {
        for (size_t c = token[n].find_first_of(" "); c != std::string::npos;
             c = token[n].find_first_of(" ")) {
            token[n].erase(c, 1);
        }
        if (!token[n].empty()) {
            if (!(token[n].find(".") == std::string::npos)) {
                std::vector<std::string> x = split(token[n], ".");
                for (int i = 0; i < x.size(); i++) {
                    if (!x[i].empty()) {
                        stack +=
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;{}[]"
                            "_+*-%"[std::stoi(x[i])];
                    }
                }
                std::cerr << stack << std::endl;
                stack = "";
            }
        }
    }
    return 0;
}
