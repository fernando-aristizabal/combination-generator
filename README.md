In order to generate combinations, two established algorithms, Knuth-
Morris-Pratt (KMP) and Longest Common Subsequence (LCS), are utilized. The KMP algorithm is
used to determine a vector where each element represents an occurrence of the hint string within the
initial string. KMP first preprocesses the hint string of length W in O(W) time by determining a
Longest Prefix Suffix (LPS) array where each element i is the length of the longest proper prefix in the
current sub-pattern (hint[0 to i]) that matches a proper suffix in the same sub-pattern. This LPS array is
used to search the initial string (length N) for occurrences of the hint string in O(N) time by being able
to reset the hint string counter with the LPS array’s current value. In total, the KMP algorithm runs in
O(N+W) time. After determining the vector with the indices of occurrence, the LCS algorithm is now
applied to the difference of the vector’s adjacent elements (indices[i+1] - indices[i]) along with the
reverse of this difference vector. LCS first generates a table that stores the longest common
subsequence for each pairwise combination of characters. To print the results, the table is traversed
from the lower right corner in the direction of the larger values. Every match of characters is outputted
as part of the combination. This approach to finding the LCS operates in O(M 2 ) time. Combining both
algorithms, KMP and LCS, yields a total asymptotic time complexity of O(N+W+M 2 ).

Compiling
g++ combinations.cpp -o combination
