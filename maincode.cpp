#include <iostream>
#include <vector>
using namespace std;

// ------------------ FIFO ------------------
void ThuatToanFIFO(int capacity, string ref) {
    vector<int> frames;
    int page_faults = 0;
    int index_to_replace = 0;

    cout << "\nQua trinh thay the trang (FIFO):\n";

    for (char c : ref) {
        int page = c - '0';
        bool hit = false;

        for (int x : frames) {
            if (x == page) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            if ((int)frames.size() < capacity) {
                frames.push_back(page);
            }
            else {
                frames[index_to_replace] = page;
                index_to_replace = (index_to_replace + 1) % capacity;
            }
            page_faults++;
        }

        cout << "Trang " << page << " -> [ ";
        for (int x : frames) cout << x << " ";
        cout << "]" << (hit ? " (hit)" : " (loi trang)") << "\n";
    }

    cout << "\nTong so loi trang = " << page_faults << endl;
}

// ------------------ OPT ------------------
void ThuatToanOPT(int capacity, string ref) {
    vector<int> frames;
    int page_faults = 0;

    cout << "\nQua trinh thay the trang (OPT):\n";

    for (int i = 0; i < (int)ref.size(); i++) {
        int page = ref[i] - '0';
        bool hit = false;

        for (int x : frames) {
            if (x == page) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            if ((int)frames.size() < capacity) {
                frames.push_back(page);
            }
            else {
                int idx_to_replace = -1;
                int farthest = -1;

                for (int j = 0; j < (int)frames.size(); j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < (int)ref.size(); k++) {
                        if (frames[j] == ref[k] - '0') {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use == -1) {
                        idx_to_replace = j;
                        break;
                    }
                    else if (next_use > farthest) {
                        farthest = next_use;
                        idx_to_replace = j;
                    }
                }

                frames[idx_to_replace] = page;
            }
            page_faults++;
        }

        cout << "Trang " << page << " -> [ ";
        for (int x : frames) cout << x << " ";
        cout << "]" << (hit ? " (hit)" : " (loi trang)") << "\n";
    }

    cout << "\nTong so loi trang = " << page_faults << endl;
}

// ------------------ LRU ------------------
void ThuatToanLRU(int capacity, string ref) {
    vector<int> frames;
    int page_faults = 0;

    cout << "\nQua trinh thay the trang (LRU):\n";

    for (int i = 0; i < (int)ref.size(); i++) {
        int page = ref[i] - '0';
        bool hit = false;

        for (int x : frames) {
            if (x == page) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            if ((int)frames.size() < capacity) {
                frames.push_back(page);
            }
            else {
                int idx_to_replace = -1;
                int least_recent = i;

                for (int j = 0; j < (int)frames.size(); j++) {
                    int last_use = -1;
                    for (int k = i - 1; k >= 0; k--) {
                        if (frames[j] == ref[k] - '0') {
                            last_use = k;
                            break;
                        }
                    }
                    if (last_use < least_recent) {
                        least_recent = last_use;
                        idx_to_replace = j;
                    }
                }

                frames[idx_to_replace] = page;
            }
            page_faults++;
        }

        cout << "Trang " << page << " -> [ ";
        for (int x : frames) cout << x << " ";
        cout << "]" << (hit ? " (hit)" : " (loi trang)") << "\n";
    }

    cout << "\nTong so loi trang = " << page_faults << endl;
}

// ------------------ MAIN ------------------
int main() {
    int capacity;
    string ref;
    int choice;

    cout << "Nhap so khung trang: ";
    cin >> capacity;

    cout << "Nhap chuoi tham chieu: ";
    cin >> ref;

    cout << "\nChon thuat toan:\n";
    cout << "1. FIFO\n2. OPT\n3. LRU\n";
    cout << "Nhap lua chon: ";
    cin >> choice;

    if (choice == 1) ThuatToanFIFO(capacity, ref);
    else if (choice == 2) ThuatToanOPT(capacity, ref);
    else if (choice == 3) ThuatToanLRU(capacity, ref);
    else cout << "Lua chon khong hop le!\n";

    return 0;
}
