#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

void inKhung(const vector<int>& frames, int trang, bool trung, ostream& out) {
    out << setw(8) << trang << " | [ ";
    for (int x : frames) out << x << " ";
    out << "] " << (trung ? "(trung)" : "(loi)") << "\n";
}

void FIFO(int soKhung, string chuoi, ofstream& fout, ostream& out) {
    vector<int> frames;
    int loi = 0, idx = 0;

    fout << "\nThuat toan FIFO:\n";
    out << "\nThuat toan FIFO:\n";
    out << setw(8) << "Trang" << " | Khung\n";

    for (char c : chuoi) {
        int trang = c - '0';
        bool trung = false;
        for (int x : frames) if (x == trang) { trung = true; break; }

        if (!trung) {
            if ((int)frames.size() < soKhung) frames.push_back(trang);
            else { frames[idx] = trang; idx = (idx + 1) % soKhung; }
            loi++;
        }

        inKhung(frames, trang, trung, fout);
        inKhung(frames, trang, trung, out);
    }
    fout << "Tong so loi trang = " << loi << "\n";
    out << "Tong so loi trang = " << loi << "\n";
}

void OPT(int soKhung, string chuoi, ofstream& fout, ostream& out) {
    vector<int> frames;
    int loi = 0;

    fout << "\nThuat toan OPT:\n";
    out << "\nThuat toan OPT:\n";
    out << setw(8) << "Trang" << " | Khung\n";

    for (int i = 0; i < (int)chuoi.size(); i++) {
        int trang = chuoi[i] - '0';
        bool trung = false;
        for (int x : frames) if (x == trang) { trung = true; break; }

        if (!trung) {
            if ((int)frames.size() < soKhung) frames.push_back(trang);
            else {
                int idx = -1, xa = -1;
                for (int j = 0; j < (int)frames.size(); j++) {
                    int tiep = -1;
                    for (int k = i + 1; k < (int)chuoi.size(); k++) {
                        if (frames[j] == chuoi[k] - '0') { tiep = k; break; }
                    }
                    if (tiep == -1) { idx = j; break; }
                    if (tiep > xa) { xa = tiep; idx = j; }
                }
                frames[idx] = trang;
            }
            loi++;
        }

        inKhung(frames, trang, trung, fout);
        inKhung(frames, trang, trung, out);
    }
    fout << "Tong so loi trang = " << loi << "\n";
    out << "Tong so loi trang = " << loi << "\n";
}

void LRU(int soKhung, string chuoi, ofstream& fout, ostream& out) {
    vector<int> frames;
    int loi = 0;

    fout << "\nThuat toan LRU:\n";
    out << "\nThuat toan LRU:\n";
    out << setw(8) << "Trang" << " | Khung\n";

    for (int i = 0; i < (int)chuoi.size(); i++) {
        int trang = chuoi[i] - '0';
        bool trung = false;
        for (int x : frames) if (x == trang) { trung = true; break; }

        if (!trung) {
            if ((int)frames.size() < soKhung) frames.push_back(trang);
            else {
                int idx = -1, cu = i;
                for (int j = 0; j < (int)frames.size(); j++) {
                    int gan = -1;
                    for (int k = i - 1; k >= 0; k--) {
                        if (frames[j] == chuoi[k] - '0') { gan = k; break; }
                    }
                    if (gan < cu) { cu = gan; idx = j; }
                }
                frames[idx] = trang;
            }
            loi++;
        }

        inKhung(frames, trang, trung, fout);
        inKhung(frames, trang, trung, out);
    }
    fout << "Tong so loi trang = " << loi << "\n";
    out << "Tong so loi trang = " << loi << "\n";
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Khong mo duoc file\n";
        return 1;
    }

    int soKhung, chon;
    string chuoi;
    fin >> soKhung >> chuoi >> chon;

    cout << "So khung: " << soKhung << "\n";
    cout << "Chuoi tham chieu: " << chuoi << "\n";
    cout << "Lua chon: " << chon << "\n";

    if (chon == 1) FIFO(soKhung, chuoi, fout, cout);
    else if (chon == 2) OPT(soKhung, chuoi, fout, cout);
    else if (chon == 3) LRU(soKhung, chuoi, fout, cout);
    else fout << "Lua chon khong hop le\n";

    fin.close();
    fout.close();

    cout << "Da xong. Mo file output.txt de xem\n";
    return 0;
}
