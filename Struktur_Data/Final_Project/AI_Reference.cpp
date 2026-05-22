// I use this code from AI but just the skeleton. for the rest of code, im try my best to write it myself.

#include <iostream>
#include <string>

using namespace std; // Dilarang pakai <algorithm>, <vector>, <queue>, dll.

// ==========================================
// 0. DATA STRUCTURE CORE
// ==========================================
struct Beatmap {
    string title;
    string artist;
    double stars;
    int bpm;
};

// ==========================================
// 1. LINKED LIST (Master Playlist)
// ==========================================
struct LLNode {
    Beatmap data;
    LLNode* next;
};
LLNode* headPlaylist = nullptr;

// ==========================================
// 2 & 3. QUEUE (Download) & STACK (History)
// ==========================================
struct QNode {
    Beatmap data;
    QNode* next;
};
QNode* frontQueue = nullptr;
QNode* rearQueue = nullptr;

struct SNode {
    Beatmap data;
    SNode* next;
};
SNode* topStack = nullptr;

// ==========================================
// 4. TREE (Filter By Stars)
// ==========================================
struct TreeNode {
    Beatmap data;
    TreeNode* left;
    TreeNode* right;
};
TreeNode* rootTree = nullptr;

// ==========================================
// 5. HASH TABLE (Fast Title Lookup)
// ==========================================
const int HASH_SIZE = 50;
Beatmap* hashTable[HASH_SIZE]; // Array of pointer untuk Hash Table

int getHash(string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum % HASH_SIZE;
}
// Implementasikan Linear Probing di fungsi insert-nya nanti

// ==========================================
// 6. GRAPH (Recommendation System)
// ==========================================
// Adjacency List manual: Array of LLNode
struct GraphNode {
    Beatmap data;
    LLNode* similarMaps; // Menyimpan edge ke beatmap lain yang mirip
};
GraphNode* recommendationGraph[100]; 
int graphSize = 0;

// ==========================================
// 7 & 8. SORTING & SEARCHING
// ==========================================
// Buat fungsi Bubble Sort manual untuk mengurutkan LLNode (Playlist)
// Buat fungsi Linear Search manual untuk menyisir LinkedList

// ==========================================
// ENGINE: MENGHUBUNGKAN SEMUANYA
// ==========================================
void addNewBeatmap(string t, string a, double s, int b) {
    Beatmap newMap = {t, a, s, b};
        
    // 1. Masuk ke Linked List
    // 2. Masuk ke Tree (rootTree = insertTree(rootTree, newMap))
    // 3. Masuk ke Hash Table (insertHash(newMap))
    // 4. Daftarkan sebagai Node baru di Graph
}

int main() {
    // Inisialisasi Hash Table
    for(int i = 0; i < HASH_SIZE; i++) hashTable[i] = nullptr;

    int menu;
    while (true) {
        // Karena GUI hanya nilai tambah, CLI yang solid lebih penting 
        cout << "\n=== OSU! BEATMAP ENGINE ===" << endl;
        cout << "1. Download Beatmap (Queue)" << endl;
        cout << "2. Lihat Playlist (Linked List & Sort)" << endl;
        cout << "3. Cari Judul (Hash Table)" << endl;
        cout << "4. Filter Bintang (Tree)" << endl;
        cout << "5. Lihat Rekomendasi (Graph)" << endl;
        cout << "6. History Terakhir (Stack)" << endl;
        cout << "0. Keluar" << endl;
        cout << "> ";
        cin >> menu;
        
        // Buat switch-case untuk memanggil fungsionalitas di atas
        if (menu == 0) break;
    }
    return 0;
}