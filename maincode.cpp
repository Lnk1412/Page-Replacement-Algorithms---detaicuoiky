#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

void printLine(int n) {
    cout << "+";
    for (int i = 0; i < n; i++) cout << "----+";
    cout << "\n";
}

//FIFO
void ThuatToanFIFO(int capacity, string ref) {
    vector<int> frames;
    int page_faults = 0;
    int index_to_replace = 0;
    vector<vector<int>> table(capacity, vector<int>(ref.size(), -1));

    for (int i = 0; i < (int)ref.size(); i++) {
        int page = ref[i] - '0';
        bool hit = false;

        for (int x : frames) if (x == page) { hit = true; break; }

        if (!hit) {
            if ((int)frames.size() < capacity) frames.push_back(page);
            else {
                frames[index_to_replace] = page;
                index_to_replace = (index_to_replace + 1) % capacity;
            }
            page_faults++;
        }
        for (int r = 0; r < capacity; r++)
            if (r < (int)frames.size()) table[r][i] = frames[r];
    }

    cout << "\n=== Qua trinh thay the trang (FIFO) ===\n";
    printLine(ref.size());
    cout << "|    "; for (char c : ref) cout << setw(4) << c << "|"; cout << "\n";
    printLine(ref.size());
    for (int r = 0; r < capacity; r++) {
        cout << "|F" << r << "  ";
        for (int i = 0; i < (int)ref.size(); i++) {
            if (table[r][i] == -1) cout << setw(4) << " " << "|";
            else cout << setw(4) << table[r][i] << "|";
        }
        cout << "\n"; printLine(ref.size());
    }
    cout << "Tong so loi trang = " << page_faults << "\n";
}

//TOI UU
void ThuatToanOPT(int capacity, string ref) {
    vector<int> frames;
    int page_faults = 0;
    vector<vector<int>> table(capacity, vector<int>(ref.size(), -1));

    for (int i = 0; i < (int)ref.size(); i++) {
        int page = ref[i] - '0';
        bool hit = false;

        for (int x : frames) if (x == page) { hit = true; break; }

        if (!hit) {
            if ((int)frames.size() < capacity) frames.push_back(page);
            else {
                int idx_to_replace = -1, farthest = -1;
                for (int j = 0; j < (int)frames.size(); j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < (int)ref.size(); k++)
                        if (frames[j] == ref[k] - '0') { next_use = k; break; }
                    if (next_use == -1) { idx_to_replace = j; break; }
                    else if (next_use > farthest) { farthest = next_use; idx_to_replace = j; }
                }
                frames[idx_to_replace] = page;
            }
            page_faults++;
        }
        for (int r = 0; r < capacity; r++)
            if (r < (int)frames.size()) table[r][i] = frames[r];
    }

    cout << "\n=== Qua trinh thay the trang (OPT) ===\n";
    printLine(ref.size());
    cout << "|    "; for (char c : ref) cout << setw(4) << c << "|"; cout << "\n";
    printLine(ref.size());
    for (int r = 0; r < capacity; r++) {
        cout << "|F" << r << "  ";
        for (int i = 0; i < (int)ref.size(); i++) {
            if (table[r][i] == -1) cout << setw(4) << " " << "|";
            else cout << setw(4) << table[r][i] << "|";
        }
        cout << "\n"; printLine(ref.size());
    }
    cout << "Tong so loi trang = " << page_faults << "\n";
}

//LRU
void ThuatToanLRU(int capacity, string ref) {
    vector<int> frames;
    int page_faults = 0;
    vector<vector<int>> table(capacity, vector<int>(ref.size(), -1));

    for (int i = 0; i < (int)ref.size(); i++) {
        int page = ref[i] - '0';
        bool hit = false;

        for (int x : frames) if (x == page) { hit = true; break; }

        if (!hit) {
            if ((int)frames.size() < capacity) frames.push_back(page);
            else {
                int idx_to_replace = -1, least_recent = i;
                for (int j = 0; j < (int)frames.size(); j++) {
                    int last_use = -1;
                    for (int k = i - 1; k >= 0; k--)
                        if (frames[j] == ref[k] - '0') { last_use = k; break; }
                    if (last_use < least_recent) { least_recent = last_use; idx_to_replace = j; }
                }
                frames[idx_to_replace] = page;
            }
            page_faults++;
        }
        for (int r = 0; r < capacity; r++)
            if (r < (int)frames.size()) table[r][i] = frames[r];
    }

    cout << "\n=== Qua trinh thay the trang (LRU) ===\n";
    printLine(ref.size());
    cout << "|    "; for (char c : ref) cout << setw(4) << c << "|"; cout << "\n";
    printLine(ref.size());
    for (int r = 0; r < capacity; r++) {
        cout << "|F" << r << "  ";
        for (int i = 0; i < (int)ref.size(); i++) {
            if (table[r][i] == -1) cout << setw(4) << " " << "|";
            else cout << setw(4) << table[r][i] << "|";
        }
        cout << "\n"; printLine(ref.size());
    }
    cout << "Tong so loi trang = " << page_faults << "\n";
}

// MAIN
int main() {
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cout << "Khong mo duoc file input.txt!\n";
        return 1;
    }

    int capacity, choice;
    string ref;

    fin >> capacity;
    fin >> ref;
    fin >> choice;
    fin.close();

    cout << left << setw(20) << "So khung trang" << ": " << capacity << "\n";
    cout << left << setw(20) << "Chuoi tham chieu" << ": ";
    for (char c : ref) cout << c << " ";
    cout << "\n";
    cout << left << setw(20) << "Lua chon thuat toan" << ": ";
    if (choice == 1) cout << "FIFO";
    else if (choice == 2) cout << "OPT";
    else if (choice == 3) cout << "LRU";
    else cout << "Khong hop le";
    cout << "\n\n";

    if (choice == 1) ThuatToanFIFO(capacity, ref);
    else if (choice == 2) ThuatToanOPT(capacity, ref);
    else if (choice == 3) ThuatToanLRU(capacity, ref);
    else cout << "Lua chon khong hop le!\n";

    return 0;
}
