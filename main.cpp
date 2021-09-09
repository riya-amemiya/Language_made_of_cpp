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
    std::vector<std::string> code_import = split(str, "\n");
    std::vector<std::string> code = {};
    std::string token =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;"
        "{}[]"
        "_+*-%";
    std::string stack = "";
    for (int i = 0; i < code_import.size(); i++) {
        std::vector<std::string> v = split(code_import[i], ";");
        for (int y = 0; y < v.size(); y++) {
            code.push_back(v[y]);
        }
    }
    for (int n = 0; n < code.size(); n++) {
        for (size_t c = code[n].find_first_of(" "); c != std::string::npos;
             c = code[n].find_first_of(" ")) {
            code[n].erase(c, 1);
        }
        if (!code[n].empty()) {
            if (!(code[n].find(".") == std::string::npos)) {
                std::vector<std::string> x = split(code[n], ".");
                for (int i = 0; i < x.size(); i++) {
                    if (!x[i].empty()) {
                        int z = std::stoi(x[i]);
                        if (z <= 74 && z >= 0) {
                            stack += token[z];
                        } else {
                            std::cerr << "値が範囲外です" << std::endl;
                            return -1;
                        }
                    }
                }
                std::cerr << stack << std::endl;
                stack = "";
            }
        }
    }
    return 0;
}
