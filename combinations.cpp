/*//////////////////////////////////////////////////////////////////////////////////////////

    Fernando Aristizabal
    COP 3530
    Spring 2017
    Project #2

/*//////////////////////////////////////////////////////////////////////////////////////////
///////// libraries ////////////////////////////////////////////////////////////////////////

#include <iostream> // read and write to buffer
#include <vector> // vectors
using namespace std; // no need to use std

////////////////////////////////////////////////////////////////////////////////////////////
//////// function prototypes ///////////////////////////////////////////////////////////////

void generateLPS(string hint, int W, int *lps);
void kmp(string hint, string initial, vector<int> &indices);
void lcs(vector<int> indices);

////////////////////////////////////////////////////////////////////////////////////////////
///////////// main /////////////////////////////////////////////////////////////////////////

int main()
{

    // initialize variables
    string initial;
    string hint;
    vector<int> indices;

    // obtain inputs
    getline(cin,initial);
    getline(cin,hint);

    // print empty line & exit script if either input is length 0
    if (initial.length() == 0 || hint.length() == 0) { cout << "\n" ; return 0; }

    // find indices of occurence of hint string in initial string with kmp algorithm
    kmp(initial, hint, indices);

    // find longest common subsequence
    lcs(indices);

    // go to new line
    cout << "\n";

    return 0;

}

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////// functions ////////////////////////////////////////////////////////

// find longest prefix suffix (lps) for given hint
void generateLPS(string hint, int W, int *lps)
{
    // initialize
    lps[0] = 0; // lps
    int l = 0; // length of the previous lps
    int i = 1;

    while (i < W)
    {
        if (hint[i] == hint[l])
        {
            l++;
            lps[i] = l;
            i++;
        }
        else
        {
            if (l != 0) l = lps[l-1];
            else { lps[i] = 0 ; i++ ; }
        }
    }
}


// Finds occurrence indicies of hint within initial
void kmp(string initial, string hint, vector<int> &indices)
{
    //initialize
    int N = initial.length(); // length of initial string
    int W = hint.length(); // length of hint string
    int lps[W]; // longest prefix suffix array

    // generate lps array
    generateLPS(hint, W, lps);

    int n = 0;  // index for initial
    int w  = 0;  // index for hint
    while (n < N)
    {
        if (hint[w] == initial[n]) { w++ ; n++; } // if strings match increment both n and w

        if (w == W) // end of hint string is reached
        {
            indices.push_back(n-w); // add index
            w = lps[w-1]; // reset w using lps array
        }


        else if (n < N && hint[w] != initial[n])
        {
            if (w != 0) w = lps[w-1];
            else n++;
        }
    }

}

// longest common subsequence of vector and its reverse order
void lcs(vector<int> indices)
{
    // initialize variables
    int M = indices.size()-1; // size of indices array minus 1 (size of difference array)
    int table[M+1][M+1]; // table array
    int ii = M; // reverse difference counter

    // build table array
    for (int i = 0; i <= M; i++)
    {
        for (int j = 0; j <= M; j++)
        {
            if (i == 0 || j == 0) // for first table entry
                table[i][j] = 0;
            else if ( (indices[i]-indices[i-1]) == (indices[ii+1]-indices[ii]) ) // if match increments lcs
                table[i][j] = table[i-1][j-1] + 1;
            else
                table[i][j] = max(table[i-1][j], table[i][j-1]); // if no match then take max adjacent value

            ii--; // decrement reverse difference counter
        }
        ii = M; // reset reverse difference counter
    }

    // traverse array and print matches
    int i = M-1, j = M-1;
    ii = 0; // difference counter

    while (i >= 0 && j >= 0)
    {
        // If Difference[] == reverseDifference[] are same, then print
        if ( (indices[i+1]-indices[i]) == (indices[ii+1]-indices[ii]) )
        {
            cout << (indices[ii+1]-indices[ii]) << " "; // print answer
            i--; j--; ii++;  // update counters
        }

        // If D != rD, go in the direction of larger value
        else if (table[i][j+1] > table[i+1][j]) i--;

        else  { j-- ; ii++ ;}
    }
}

