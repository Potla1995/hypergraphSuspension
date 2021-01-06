// This program is designed to compute the adjacency lists of graphs D(k,q) and D'(k,q) for k<=11 and primes q.
// We use k=11 and q=3 and output the lists of D(k,q) and D'(k,q) in Graph-D-11-3.csv and Graph-Dp-11-3.csv.

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>

const int PRIME = 3;
const int k = 11;

// Define a Vertex as a vector of integers, and the adjacency list as a map from a Vertex to a vector of Vertices.
// adjListDkqL and adjListDkqR are the adjacency lists from the left and right side of D(k,q), respectively.
// adjListDpkqL and adjListDpkqR are defined similarly.

typedef std::vector<int> Vertex;
std::vector<Vertex> vertices;
typedef std::map <Vertex, std::vector<Vertex> > AdjList;
AdjList adjListDkqL, adjListDkqR, adjListDpkqL, adjListDpkqR;

// Function to first enumerate all q^k possible vertices.

void populateVertexVector() {
    vertices.clear();
    for(int x = 0; x < pow(PRIME,k); x++) {
        int n = x;
        Vertex a;
        for(int i = 0; i < k; i++) {
            a.push_back(n % PRIME);
            n /= PRIME;
        }
        vertices.push_back(a);
    }
}

// Boolean functions that determine if two Vertices are adjacent in D(k,q) and D'(k,q), respectively.

bool isEdgeDkq(Vertex a, Vertex b) {
    int a1 = a[0], b1 = b[0];
    int a11 = (k > 1 ? a[1] : 0), b11 = (k > 1 ? b[1] : 0);
    int a12 = (k > 2 ? a[2] : 0), b12 = (k > 2 ? b[2] : 0);
    int a21 = (k > 3 ? a[3] : 0), b21 = (k > 3 ? b[3] : 0);
    int a22 = (k > 4 ? a[4] : 0), b22 = (k > 4 ? b[4] : 0);
    int ap22 = (k > 5 ? a[5] : 0), bp22 = (k > 5 ? b[5] : 0);
    int a23 = (k > 6 ? a[6] : 0), b23 = (k > 6 ? b[6] : 0);
    int a32 = (k > 7 ? a[7] : 0), b32 = (k > 7 ? b[7] : 0);
    int a33 = (k > 8 ? a[8] : 0), b33 = (k > 8 ? b[8] : 0);
    int ap33 = (k > 9 ? a[9] : 0), bp33 = (k > 9 ? b[9] : 0);
    int a34 = (k > 10 ? a[10] : 0), b34 = (k > 10 ? b[10] : 0);

    bool r1 = k > 1 ? ((a11 + b11 + a1 * b1) % PRIME == 0) : true;
    bool r2 = k > 2 ? ((a12 + b12 + a1 * b11) % PRIME == 0) : true;
    bool r3 = k > 3 ? ((a21 + b21 + a11 * b1) % PRIME == 0) : true;
    bool r4 = k > 4 ? ((a22 + b22 + a12 * b1) % PRIME == 0) : true;
    bool r5 = k > 5 ? ((ap22 + bp22 + a1 * b21) % PRIME == 0) : true;
    bool r6 = k > 6 ? ((a23 + b23 + a1 * b22) % PRIME == 0) : true;
    bool r7 = k > 7 ? ((a32 + b32 + ap22 * b1) % PRIME == 0) : true;
    bool r8 = k > 8 ? ((a33 + b33 + a23 * b1) % PRIME == 0) : true;
    bool r9 = k > 9 ? ((ap33 + bp33 + a1 * b32) % PRIME == 0) : true;
    bool r10 = k > 10 ? ((a34 + b34 + a1 * b33) % PRIME == 0) : true;

    return r1 && r2 && r3 && r4 && r5 && r6 && r7 && r8 && r9 && r10;
}

bool isEdgeDpkq(Vertex a, Vertex b) {
    int a1 = a[0], b1 = b[0];
    int a11 = (k > 1 ? a[1] : 0), b11 = (k > 1 ? b[1] : 0);
    int a12 = (k > 2 ? a[2] : 0), b12 = (k > 2 ? b[2] : 0);
    int a21 = (k > 3 ? a[3] : 0), b21 = (k > 3 ? b[3] : 0);
    int a22 = (k > 4 ? a[4] : 0), b22 = (k > 4 ? b[4] : 0);
    int ap22 = (k > 5 ? a[5] : 0), bp22 = (k > 5 ? b[5] : 0);
    int a23 = (k > 6 ? a[6] : 0), b23 = (k > 6 ? b[6] : 0);
    int a32 = (k > 7 ? a[7] : 0), b32 = (k > 7 ? b[7] : 0);
    int a33 = (k > 8 ? a[8] : 0), b33 = (k > 8 ? b[8] : 0);
    int ap33 = (k > 9 ? a[9] : 0), bp33 = (k > 9 ? b[9] : 0);
    int a34 = (k > 10 ? a[10] : 0), b34 = (k > 10 ? b[10] : 0);

    bool r1 = k > 1 ? ((a11 + (PRIME-1) * a1 + b11 + (PRIME-1) * b1 + a1 * b1) % PRIME == 0) : true;
    bool r2 = k > 2 ? ((a12 + a11 + b12 + b11 + a1 * b11) % PRIME == 0) : true;
    bool r3 = k > 3 ? ((a21 + a11 + b21 + b11 + a11 * b1) % PRIME == 0) : true;
    bool r4 = k > 4 ? ((a22 + a12 + b22 + b12 + a12 * b1) % PRIME == 0) : true;
    bool r5 = k > 5 ? ((ap22 + a21 + bp22 + b21 + a1 * b21) % PRIME == 0) : true;
    bool r6 = k > 6 ? ((a23 + a22 + b23 + b22 + a1 * b22) % PRIME == 0) : true;
    bool r7 = k > 7 ? ((a32 + ap22 + b32 + bp22 + ap22 * b1) % PRIME == 0) : true;
    bool r8 = k > 8 ? ((a33 + a23 + b33 + b23 + a23 * b1) % PRIME == 0) : true;
    bool r9 = k > 9 ? ((ap33 + a32 + bp33 + b32 + a1 * b32) % PRIME == 0) : true;
    bool r10 = k > 10 ? ((a34 + a33 + b34 + b33 + a1 * b33) % PRIME == 0) : true;

    return r1 && r2 && r3 && r4 && r5 && r6 && r7 && r8 && r9 && r10;
}

// Functions to export adjacency lists as .csv files.

std::string Vertex2Str(Vertex v) {
    std::stringstream ss;
    for(int i=0;i<v.size();i++)
        ss << v[i];
    return ss.str();
}

void printCSV(AdjList A, std::string GraphId){
    std::stringstream ss;
    ss<<GraphId<<k<<"-"<<PRIME<<".csv";
    std::ofstream fout(ss.str(),std::ios::out);
    for(auto &x : A){
        fout<<Vertex2Str(x.first)<<";";
        for(auto &y: x.second){
            fout<<Vertex2Str(y)<<"\';";
        }
        fout<<std::endl;
    }
    fout.close();
}

// Function to compute the adjacency lists via a brute force check.

void populateAdjLists() {
    for(Vertex& x: vertices) {
        for(Vertex& y: vertices) {
            if(isEdgeDkq(x, y)) {
                adjListDkqL[x].push_back(y);
                adjListDkqR[y].push_back(x);
            }
            if(isEdgeDpkq(x, y)) {
                adjListDpkqL[x].push_back(y);
                adjListDpkqR[y].push_back(x);
            }
        }
    }
}

// Main function:

int main() {
    // Populate all q^k possible vertices into the vector<Vertex> vertices.
    populateVertexVector();
    // Calculate the adjacency lists of D(k,q) and D'(k,q).
    populateAdjLists();
    // Export the adjacency lists.
    printCSV(adjListDkqL, "Graph-D-");
    printCSV(adjListDpkqL, "Graph-Dp-");
    return 0;
}
