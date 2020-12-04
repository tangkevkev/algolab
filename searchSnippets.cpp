#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

// Full points, runs in 0(M log M) or O(M²) not sure. Depends on the implementation of sort in <algorithm>
// M >= numbers readed

// Idea: Store position + word_id as tuple in a big vector
// Sort vector by position of the word (M log M or M² )
// Then apply sliding window algorithm to select the optimal interval

bool compareFirst(std::array<int, 2> a, std::array<int, 2> b)
{
    return (a[0] < b[0]);
}

void testcase()
{
    int n;
    std::cin >> n;

    //Store the number of occurence's of word i in m[i]
    int total_words = 0;
    std::vector<int> m(n, 0);
    for (int i = 0; i < n; i++)
    {
        std::cin >> m[i];
        total_words += m[i];
    }

    //vector allWords stores the occurences of each word at each position
    //We can do this as the exercises states that p_ij is pairwise distinct
    std::vector<std::array<int, 2>> allWords;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m[i]; j++)
        {
            int pos;
            std::cin >> pos;
            allWords.push_back({pos, i});
        }
    }

    //Sort it for the traversal
    std::sort(allWords.begin(), allWords.end(), compareFirst);

    std::vector<int> lastOccurenceIndex(n, -1);
    int count = 0;
    //trying to optimize.. dont know if its worth..
    int aWSize = allWords.size();

    //The interval starts at the first words position
    int a = allWords[0][0], b = allWords[aWSize - 1][0];
    int left_index = 0;

    //Including all words is the worst solution (longest solution)
    int optimal = __INT32_MAX__;

    for (int i = 0; i < aWSize; i++)
    {
        std::array<int, 2> el = allWords[i];
        int word_id = el[1];
        int pos_index = el[0];

        if (lastOccurenceIndex[word_id] == -1)
        {
            lastOccurenceIndex[word_id] = pos_index;
            count++;
        }
        else
        {
            int new_left_index = left_index;
            lastOccurenceIndex[word_id] = pos_index;

            for (int j = left_index; j < i; j++)
            {
                int dif = j - left_index;
                auto leftEl = allWords[j];
                auto rightEl = allWords[i - dif];

                
                if (leftEl[1] == rightEl[1] && j < (i - dif))
                {
                    new_left_index++;
                }
                else if (lastOccurenceIndex[leftEl[1]] != leftEl[0] ||leftEl[0] == allWords[i][0])
                {
                    new_left_index++;
                }
                else
                {
                    break;
                }
            }
            if (new_left_index != left_index)
            {
                left_index = new_left_index;
            }
        }

        if (count == n)
        {
            int new_optimal = (allWords[i][0] - allWords[left_index][0]) + 1;
            optimal = (new_optimal < optimal) ? new_optimal : optimal;
       /*    std::cout << "left_index : " << left_index << ". right: " << i << ". optimal: " << optimal << std::endl;

            for (int j = left_index; j <= i; j++)
            {
                std::cout << allWords[j][1] << " ";
            }
            std::cout << std::endl;
        */
        }
    }
    std::cout << optimal << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;

    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        testcase();
    }
}