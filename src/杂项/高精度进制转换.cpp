struct BaseConverter {
    map<char, int> charToInt;
    map<int, char> intToChar;
    BaseConverter() {
        for (int i = 0; i < 10; i++) {
            charToInt[(char)i + 48] = i;
            intToChar[i] = (char)i + 48;
        }
        for (int i = 10; i < 36; i++) {
            charToInt[(char)i + 55] = i;
            intToChar[i] = (char)i + 55;
        }
        for (int i = 36; i < 62; i++) {
            charToInt[(char)i + 61] = i;
            intToChar[i] = (char)i + 61;
        }
    }
    string convertBase(int fromBase, int toBase, const string &number) {
        vector<int> nums;
        for (auto &c : number) {
            nums.push_back(charToInt[c]);
        }
        reverse(nums.begin(), nums.end());
        vector<int> result;
        while (!nums.empty()) {
            int remainder = 0;
            for (int i = nums.size() - 1; i >= 0; i--) {
                nums[i] += remainder * fromBase;
                remainder = nums[i] % toBase;
                nums[i] /= toBase;
            }
            result.push_back(remainder);
            while (!nums.empty() && nums.back() == 0) {
                nums.pop_back();
            }
        }
        reverse(result.begin(), result.end());
        string res;
        for (int digit : result) {
            res += intToChar[digit];
        }
        return res;
    }
};