vector<vector<string>> a;
string line;
while (getline(cin, line, '-')) { // 分隔符默认为空格
    if (line.empty()) {
        break; // 读入空行或 EOF
    }
    vector<string> words;
    istringstream iss(line);
    string word;
    while (iss >> word) {
        words.push_back(word);
    }
    a.push_back(words);
}