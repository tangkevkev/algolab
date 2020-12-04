#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <tuple>
#include <set>

bool compareInt(int a, int b)
{
    return b > a;
}

bool compareFst(std::array<int, 2> A, std::array<int, 2> B)
{
    return B[0] > A[0];
}

void testcase()
{
    int n;
    std::cin >> n;

    int distance = 100;

    std::vector<int> x;
    for (int i = 0; i < n; i++)
    {
        int x_i;
        std::cin >> x_i;
        x.push_back(x_i);
    }

    std::vector<std::array<int, 2>> ranges;
    std::sort(x.begin(), x.end(), compareInt);

    for (int i = 0; i < n; i++)
    {
        int x_i = x[i];
        ranges.push_back({x_i - distance, x_i + distance});
    }

    //Store common ranges (left, right, count of parasols in that range defined by [left,right])
    std::vector<std::array<int, 3>> commonRanges;
    std::vector<std::set<int>> memberRanges;
    int index_range = 0;
    int max_elements = -1;
    // A0 B0 C1 A1 B1 C2
    // Results to Range B0 A1
    // Results to Range C1 A1 with 3 parasols in that range
    for (int i = 0; i < n - 1; i++)
    {
        std::array<int, 2> A = ranges[i];
        std::array<int, 2> B = ranges[i + 1];

        if (commonRanges.size() > 0)
        {
            for (int j = 0; j < commonRanges.size(); j++)
            {
                std::array<int, 3> currentRange = commonRanges[j];
                if (currentRange[1] >= B[0])
                {
                    //Add index of the members in this range
                    auto newMem = memberRanges[j];
                    newMem.emplace(i + 1);
                    memberRanges[j] = newMem;

                    int new_count = currentRange[2] + 1;
                    commonRanges[j] = {B[0], currentRange[1], new_count};

                    max_elements = (new_count > max_elements) ? new_count : max_elements;
                }
            }
        }

        if (A[1] >= B[0])
        {
            commonRanges.push_back({B[0], A[1], 2});
            std::set<int> mem = {i, i + 1};
            memberRanges.push_back(mem);
            max_elements = (2 > max_elements) ? 2 : max_elements;
        }
    }
    /*
    for (int i = 0; i < n; i++)
    {
        std::cout << "index: " << i << ". range: " << ranges[i][0] << ", " << ranges[i][1] << std::endl;
    }
    std::cout << "CommonRanges:" << std::endl;
*/
    std::vector<std::array<int, 3>> optimalRanges;
    std::vector<std::set<int>> optimalMembers;

    for (int i = 0; i < commonRanges.size(); i++)
    {
        auto c = commonRanges[i];
        /* std::cout << "index " << i << ". [" << c[0] << "," << c[1] << "] count: " << c[2] << std::endl;

        std::cout << "---members---" << std::endl;
        for (int x_i : memberRanges[i])
        {
            std::cout << x_i << " ";
        }
        std::cout << std::endl;*/

        if (c[2] == max_elements)
        {
            optimalRanges.push_back(c);
            optimalMembers.push_back(memberRanges[i]);
        }
    }

    // First component stores distance to the ideal point and the second its coordinate
    std::vector<std::array<int, 2>> result;

    for (int i = 0; i < optimalRanges.size(); i++)
    {
        auto oR = optimalRanges[i];
        auto oM = optimalMembers[i];

        int sum = oR[0] + oR[1];
        std::vector<int> mids;

        if (sum % 2 == 0)
        {
            mids.push_back(sum / 2);
        }
        else
        {
            if (sum > 0)
            {
                mids.push_back((sum / 2));
                mids.push_back((sum / 2) + 1);
            }
            else
            {
                mids.push_back((sum / 2) - 1);
                mids.push_back((sum / 2));
            }
        }

        for (int mid : mids)
        {
            int max_dist_to_mid = 0;
            for (int member : oM)
            {
                int dist = std::abs(x[member] - mid);
                max_dist_to_mid = (dist > max_dist_to_mid) ? dist : max_dist_to_mid;
            }
            result.push_back({max_dist_to_mid, mid});
        }
    }
    if (max_elements != -1)
    {

        std::sort(result.begin(), result.end(), compareFst);
        int min_dist = result[0][0];
        std::cout << max_elements << " " << result[0][0] << std::endl;
        //    std::cout << "Results: " << std::endl;
        for (auto res : result)
        {
            if (res[0] > min_dist)
                break;
            std::cout << res[1] << " ";
        }
    }
    else
    {
        //no overlapping ranges => all parasols are ideal.
        std::cout << "1 0" << std::endl;
        for (int x_i : x)
        {
            std::cout << x_i << " ";
        }
    }
    std::cout << std::endl;
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