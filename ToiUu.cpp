#include <iostream>
#include <vector>
using namespace std;

// Hàm tìm trang để thay thế theo thuật toán Optimal
int findReplaceIndex(const vector<int>& frames, const vector<int>& refs, int current) {
    int farthest = -1, idx = -1;
    for (int i = 0; i < frames.size(); i++) {
        int j;
        for (j = current + 1; j < refs.size(); j++) {
            if (frames[i] == refs[j]) break;
        }
        if (j == refs.size()) return i; // trang không còn dùng nữa
        if (j > farthest) {
            farthest = j;
            idx = i;
        }
    }
    return idx;
}

int main() {
    int frameCount, n;
    cout << "Nhap so khung: ";
    cin >> frameCount;
    cout << "Nhap do dai chuoi tham chieu: ";
    cin >> n;

    vector<int> refs(n);
    cout << "Nhap chuoi tham chieu: ";
    for (int i = 0; i < n; i++) cin >> refs[i];

    vector<int> frames;
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = refs[i];
        bool found = false;

        // Kiểm tra trang có trong khung chưa
        for (int x : frames) {
            if (x == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            pageFaults++;
            if (frames.size() < frameCount) {
                frames.push_back(page);
            }
            else {
                int idx = findReplaceIndex(frames, refs, i);
                frames[idx] = page;
            }
        }
    }

    cout << "Tong so loi trang: " << pageFaults << endl;
    return 0;
}