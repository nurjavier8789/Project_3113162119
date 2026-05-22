#include <iostream>
#include <string>

using namespace std;

struct Beatmap {
    string title;
    string artist;
    double stars;
    int bpm;
};

struct LLNode {
    Beatmap data;
    LLNode* next;
};
LLNode* headPlaylist = nullptr;

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

struct TreeNode {
    Beatmap data;
    TreeNode* left;
    TreeNode* right;
};
TreeNode* rootTree = nullptr;

// Lowering case
string toLower(string str) {
    string result = str;
    for (int i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

const int HASH_SIZE = 50;
Beatmap* hashTable[HASH_SIZE];

int getHash(string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum % HASH_SIZE;
}

struct GraphNode {
    Beatmap data;
    LLNode* similarMaps;
};
GraphNode* recommendationGraph[100]; 
int graphSize = 0;

// Add Beatmap to linked list
void insertToLinkedList(Beatmap newBeatmap) {
    LLNode *newNode = new LLNode;
    newNode->data = newBeatmap;
    newNode->next = nullptr;

    if (headPlaylist == nullptr) {
        headPlaylist = newNode;
        return;
    } else {
        LLNode* temp = headPlaylist;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Add beatmap title to hash
void insertToHash(Beatmap b) {
    Beatmap* newMap = new Beatmap{b.title, b.artist, b.stars, b.bpm};
    
    int idx = getHash(toLower(newMap->title));
    
    while (hashTable[idx] != nullptr) {
        idx = (idx + 1) % HASH_SIZE;
    }
    
    hashTable[idx] = newMap;
}

// Insert beatmap data into tree
TreeNode* insertToTree(TreeNode* root, Beatmap newMap) {
    if (root == nullptr) {
        TreeNode* newNode = new TreeNode;
        newNode->data = newMap;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (newMap.stars < root->data.stars) {
        root->left = insertToTree(root->left, newMap);
    } 
    else {
        root->right = insertToTree(root->right, newMap);
    }
    return root;
}

void addNewBeatmap(string title, string artist, double diff, int bpm) {
    Beatmap newMap = {title, artist, diff, bpm};

    insertToLinkedList(newMap);
    insertToHash(newMap);
    rootTree = insertToTree(rootTree, newMap);
}

// Menu 1 Download Baru (kayak nambah lagu baru ke linkedlist)
void enqueueDownload(Beatmap newMap) {
    QNode* newNode = new QNode;
    newNode->data = newMap;
    newNode->next = nullptr;

    if (rearQueue == nullptr) {
        frontQueue = rearQueue = newNode;
        cout << "[+] " << newMap.title << " masuk ke antrean download." << endl;
        return;
    } else {
        rearQueue->next = newNode;
        rearQueue = newNode;
        cout << "[+] " << newMap.title << " masuk ke antrean download." << endl;
    }
}

// Menu 2
void processDownload() {
    if (frontQueue == nullptr) {
        cout << "Tidak ada beatmap di antrean download." << endl;
        return;
    }

    QNode* temp = frontQueue;
    Beatmap finishedMap = temp->data;

    frontQueue = frontQueue->next;
    
    if (frontQueue == nullptr) {
        rearQueue = nullptr;
    }

    delete temp;

    cout << "\n[V] DOWNLOAD SELESAI: " << finishedMap.title << endl;

    addNewBeatmap(finishedMap.title, finishedMap.artist, finishedMap.stars, finishedMap.bpm);
}

// Menu 3 Lihat Playlist
void viewBeatmap() {
    if (headPlaylist == nullptr) {
        system("clear");
        cout << "======================================" << endl;
        cout << "           BEATMAP LISTING" << endl;
        cout << "======================================" << endl;
        cout << "Tidak ada lagu untuk saat ini..." << endl;
        cout << "Tekan enter untuk melanjutkan..." << endl;
        cin.ignore(); cin.get();
    } else {
        LLNode *curr = headPlaylist;
        int index = 1;

        system("clear");
        cout << "======================================" << endl;
        cout << "           BEATMAP LISTING" << endl;
        cout << "======================================" << endl;
        
        while (curr != nullptr) {
            cout << index << ". " << curr->data.title << " - " << curr->data.artist << " | Stars: " << curr->data.stars << " | BPM: " << curr->data.bpm << endl;
            curr = curr->next;
            index++;
        };
    }

    cout << "\nTekan enter untuk melanjutkan..." << endl;
    cin.ignore(); cin.get();
}

// Menu 5 Filter Bintang
void filterByStars(TreeNode* root, double minStars, double maxStars, bool &found) {
    if (root == nullptr) return;

    filterByStars(root->left, minStars, maxStars, found);

    if (root->data.stars >= minStars && root->data.stars <= maxStars) {
        cout << "- " << root->data.title << " - " << root->data.artist 
             << " | Stars: " << root->data.stars << "* | BPM: " << root->data.bpm << endl;
        found = true;
    }

    filterByStars(root->right, minStars, maxStars, found);
}

int main() {
    for(int i = 0; i < HASH_SIZE; i++) hashTable[i] = nullptr;

    addNewBeatmap("7 Wonders", "Sakuzyo", 5.7, 168);
    addNewBeatmap("CHUTEN", "t+pazolite", 6.2, 125);
    addNewBeatmap("IF:U", "MisoilePunch", 4.2, 190);
    addNewBeatmap("Tsunagite", "rintaro soma", 3.8, 88);
    addNewBeatmap("Apollo", "TJ.hangneil", 6.6, 339);
    addNewBeatmap("over the top", "xi", 9.71, 202);

    int menu;
    while (true) {
        system("clear");
        cout << "======================================" << endl;
        cout << "           BEATMAP LISTING" << endl;
        cout << "======================================" << endl;
        cout << "1. Download Beatmap Baru (Done)" << endl;
        cout << "2. Proses Antrean Download (Done)" << endl;
        cout << "3. Lihat Playlist (Done)" << endl;
        cout << "4. Cari Judul Lagu (Done)" << endl;
        cout << "5. Filter Bintang (Done)" << endl;
        cout << "6. Lihat Rekomendasi ()" << endl;
        cout << "7. History Terakhir ()" << endl;
        cout << "0. Keluar" << endl;
        cout << "> ";
        cin >> menu;
        
        if (menu == 1) {
            string title, artist;
            double diff;
            int bpm;

            system("clear");
            cout << "======================================" << endl;
            cout << "           DOWNLOAD BEATMAP" << endl;
            cout << "======================================" << endl;
            cin.ignore();
            
            cout << "Judul Lagu: ";
            getline(cin, title);
            
            cout << "Nama Artist: ";
            getline(cin, artist);
            
            cout << "Star Rating: ";
            cin >> diff;
            
            cout << "BPM Lagu: ";
            cin >> bpm;

            Beatmap mapBaru = {title, artist, diff, bpm};
            
            enqueueDownload(mapBaru); 
            
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        } else if (menu == 2) {
            system("clear");
            cout << "======================================" << endl;
            cout << "           PROSES DOWNLOAD" << endl;
            cout << "======================================" << endl;

            processDownload();
            
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        } else if (menu == 3) {
            viewBeatmap();
        } else if (menu == 4) {
            string query;
            system("clear");
            cout << "======================================" << endl;
            cout << "           CARI JUDUL LAGU" << endl;
            cout << "======================================" << endl;
            cin.ignore();
            cout << "Masukkan Judul Beatmap: ";
            getline(cin, query);
            
            int idx = getHash(toLower(query));
            bool found = false;

            for (int i = 0; i < HASH_SIZE; i++) {
                int currentIdx = (idx + i) % HASH_SIZE;
                
                if (hashTable[currentIdx] != nullptr && toLower(hashTable[currentIdx]->title) == toLower(query)) {
                    cout << "\n[Ditemukan]: " << hashTable[currentIdx]->title << " - " << hashTable[currentIdx]->artist;
                    cout << "\nStars: " << hashTable[currentIdx]->stars << " | BPM: " << hashTable[currentIdx]->bpm << endl;
                    found = true;
                }
            }

            if (!found) {
                cout << "\nBeatmap '" << query << "' tidak ditemukan." << endl;
            }

            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        } else if (menu == 5) {
            double minStars, maxStars;

            system("clear");
            cout << "======================================" << endl;
            cout << "            FILTER BINTANG" << endl;
            cout << "======================================" << endl;
            cout << "(Masukkan angka desimal)" << endl;
            cout << "Masukkan Minimum Tingkat Kesulitan: ";
            cin >> minStars;
            cout << "Masukkan Maksimal Tingkat Kesulitan: ";
            cin >> maxStars;

            system("clear");
            cout << "======================================" << endl;
            cout << "            FILTER BINTANG" << endl;
            cout << "======================================" << endl;
            cout << "Hasil Filter Tingkat Kesulitan range " << minStars << " - " << maxStars << ":" << endl;
            bool found = false;

            filterByStars(rootTree, minStars, maxStars, found);

            if (!found) {
                cout << "Tidak ada beatmap yang memenuhi kriteria bintang tersebut";
            }

            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        } else if (menu == 0) break;
    }
    return 0;
}