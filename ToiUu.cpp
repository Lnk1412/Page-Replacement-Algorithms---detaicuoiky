#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int capacity;
    cout << "Nhap so khung trang: ";
    cin >> capacity;

    string ref;
    cout << "Nhap chuoi tham chieu: ";
    cin >> ref;

    vector<int> frames;
    int page_faults = 0;

    cout << "\nQua trinh thay the trang (OPT):\n";

    for (int i = 0; i < (int)ref.size(); i++) {
        int page = ref[i] - '0';
        bool hit = false;

        // kiem tra hit
        for (int x : frames) {
            if (x == page) {
                hit = true;
                break;
            }
        }

        if (!hit) { // neu miss
            if ((int)frames.size() < capacity) {
                frames.push_back(page);
            }
            else {
                // tim trang can thay theo OPT
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
                    if (next_use == -1) { // khong dung lai nua
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

        // in trang thai
        cout << "Trang " << page << " -> [ ";
        for (int x : frames) cout << x << " ";
        cout << "]" << (hit ? " (hit)" : " (loi trang)") << "\n";
    }

    cout << "\nTong so loi trang = " << page_faults << endl;
    return 0;
}
