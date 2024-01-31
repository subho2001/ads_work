#include <iostream>
#include <string>

using namespace std;

void badCharHeuristic(string pattern, int badChar[]) {
    int m = pattern.length();
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        badChar[pattern[i]] = i;
    }
    for(int i=0; i<m; i++){
        cout<<badChar[pattern[i]]<<endl;
    }
}

void goodSuffixHeuristic(string pattern, int goodSuffix[]) {
    int m = pattern.length();
    int j = 0;
    for (int i = 0; i <= m; i++) {
        goodSuffix[i] = 0;
    }
    for (int i = m - 1; i >= 0; i--) {
        if (pattern[i] == pattern[m - 1 - j]) {
            j++;
        } else {
            j = 0;
        }
        goodSuffix[i] = j;
    }
}

void boyerMooreSearch(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();

    int badChar[256];
    int goodSuffix[m + 1];

    badCharHeuristic(pattern, badChar);
    goodSuffixHeuristic(pattern, goodSuffix);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        if (j < 0) {
            cout << "Pattern occurs at shift = " << s << endl;
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        } else {
            s += max(1, max(j - badChar[text[s + j]], goodSuffix[j + 1] - (m - 1 - j)));
        }
    }
}

int main() {
    string text, pattern;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the pattern: ";
    getline(cin, pattern);

    boyerMooreSearch(text, pattern);
    return 0;
}
