#include <iostream>
#include <string>

using namespace std;

struct Beatmap {
    string title;
    string artist;
    string status;
    double stars;
    Beatmap *left, *right;
};

string toLower(string str) {
    string result = str;
    for (int i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

const int MAX_HASH = 20;
Beatmap* hashTable[MAX_HASH];

int generateHash(string key) {
    int hash = 0;
    for (char c : key) hash += c;
    return hash % MAX_HASH;
}

void insertToHash(Beatmap* b) {
    int idx = generateHash(b->title);
    while (hashTable[idx] != nullptr) {
        idx = (idx + 1) % MAX_HASH;
    }
    hashTable[idx] = b;
}

Beatmap* insertToTree(Beatmap* root, Beatmap* newNode) {
    if (root == nullptr) return newNode;
    if (newNode->stars < root->stars)
        root->left = insertToTree(root->left, newNode);
    else
        root->right = insertToTree(root->right, newNode);
    return root;
}

void searchByStatus(Beatmap* root, string targetStatus, bool &found) {
    if (root == nullptr) return;
    searchByStatus(root->left, targetStatus, found);
    if (toLower(root->status) == toLower(targetStatus)) {
        cout << "- [" << root->status << "] " << root->title << " | Stars: " << root->stars << "*" << endl;
        found = true;
    }
    searchByStatus(root->right, targetStatus, found);
}

Beatmap* rootTree = nullptr;

void addBeatmap(string t, string a, string s, double st) {
    Beatmap* newMap = new Beatmap{t, a, s, st, nullptr, nullptr};
    rootTree = insertToTree(rootTree, newMap);
    insertToHash(newMap);
}

void displayAll(Beatmap* root) {
    if (root == nullptr) return;

    displayAll(root->left);
    cout << "- [" << root->status << "]\t| " << root->artist << " - " << root->title << "\t| Difficulty: " << root->stars << "*" << endl;
    displayAll(root->right);
}

int main() {
    addBeatmap("XaleidoscopiX", "xi", "Ranked", 8.06);
    addBeatmap("XaleidoscopiX", "xi", "Graveyard", 9.98);
    addBeatmap("Sage", "Camellia", "Graveyard", 5.19);
    addBeatmap("of Ambrosia", "Frums", "Loved", 8.09);
    addBeatmap("IF:U", "MisoilePunch", "Ranked", 4.24);
    addBeatmap("APOCALYPSE RAY", "xi", "Loved", 9.69);
    addBeatmap("DiSANiMATE", "seatrus", "Qualified", 10.23);
    addBeatmap("Burning Star", "LV.4", "Graveyard", 3.67);

    int menu;
    string query;

    while (true) {
        system("clear");
        cout << "======================================" << endl;
        cout << "            SELAMAT DATANG" << endl;
        cout << "======================================" << endl;
        cout << "|1. Cari berdasarkan status beatmap" << endl;
        cout << "|2. Cari detail berdasarkan judul beatmap" << endl;
        cout << "|3. Tampilkan semua beatmap" << endl;
        cout << "|0. Keluar" << endl;
        cout << "> ";
        cin >> menu;

        if (menu == 1) {
            cout << "Masukkan Status (Ranked/Loved/Qualified/Graveyard): ";
            cin >> query;

            bool found = false;
            cout << "\n--- Hasil Pencarian Status: " << query << " ---" << endl;
            searchByStatus(rootTree, query, found);
            if (!found) cout << "Beatmap dengan status tersebut tidak ditemukan." << endl;
            
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        } 
        else if (menu == 2) {
            cout << "Masukkan Judul Beatmap: ";
            cin.ignore();
            getline(cin, query);
            
            int idx = generateHash(query);
            bool found = false;
            
            for (int i = 0; i < MAX_HASH; i++) {
                int currentIdx = (idx + i) % MAX_HASH;
                if (hashTable[currentIdx] != nullptr && toLower(hashTable[currentIdx]->title) == toLower(query)) {
                    cout << "\n[Detail Found]:\n" << hashTable[currentIdx]->artist << " - " << hashTable[currentIdx]->title;
                    cout << "\nStatus: " << hashTable[currentIdx]->status << " | Difficulty: " << hashTable[currentIdx]->stars << "*" << endl;
                    found = true;
                }
            }
            if (!found) cout << "\nBeatmap tidak ditemukan di database." << endl;
            
            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();
        } else if (menu == 3) {
            cout << "\n--- Seluruh Database Beatmap (Urutan berdasarkan tingkat kesulitan) ---" << endl;
            if (rootTree == nullptr) {
                cout << "Database kosong!" << endl;
            } else {
                displayAll(rootTree);
            }
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        } else if (menu == 0) break;
    }
    return 0;
}
