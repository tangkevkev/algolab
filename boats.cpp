#include <iostream>
#include <vector>
#include <algorithm>

//50/100 Points, wrong answer on last test-set

int fst_compare(std::vector<int> &a, std::vector<int> &b)
{
    return (a[0] < b[0]);
}

void testcase()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> boats(n, std::vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        int l, p;
        std::cin >> l;
        std::cin >> p;
        boats[i] = {p, l}; //first position of the assigned ring, then the length of the boat
    }

    std::sort(boats.begin(), boats.end(), fst_compare);
  /*  for (int i = 0; i < n; i++)
    {
             std::cout << boats[i][0] << " " << boats[i][1] << std::endl;
    }
*/
    //apply earliest deadline first(in the slides its called to be a working greedy algo)
    //We evaluate at each ring. Ideally we place the boat at the left most possible position

    //We check the position for each ring.
    //  0 1 2 3 4 5! 6 7 8! 9 10 11 12 13 14 15 16 17 18 19 20
    //  - - - - - -  - - -

    int left = INT32_MIN;
    int boat_count = 0;
    //Go through all rings, check which boats may cover it
    for (int i = 0; i < n; i++)
    {
        int ring_i = boats[i][0];
        int length_i = boats[i][1] - 1;

        //Where can we start placing our boat (ideally at the most left position possible)

        int left_i = std::max(left, (ring_i - length_i));
        //   std::cout <<"i :" << i << ". left: " << left << std::endl;
        if (left > ring_i)
            continue;

        //compute edf of boat i
        int edf_i = (left_i + length_i);

        //Check if there's any edf smaller than edf_i
        for (int j = i + 1; j < n; j++)
        {
            int ring_j = boats[j][0];
            int length_j = boats[j][1] - 1;

//            std::cout << "i: " << i << " . " <<"j : " << j << ". n : " << n << std::endl;

            //It is either the left bounded by the last boat, or the ring location minus its length
            int left_j = std::max(left, (ring_j - length_j));
            int edf_j = left_j + length_j; //edf of boat j,
            
            if(edf_i < ring_j){
                break;
            }    


            if (edf_i > edf_j)
            {
                edf_i = edf_j;
                i = j;
            }
        }
        //std::cout << "i : " << i << ". ring: " << boats[i][0] << ". length: " << boats[i][1] << std::endl;
        //std::cout << "left: " << (edf_i - boats[i][1] + 1) << ". right: " << edf_i << std::endl;
        left = (boats[i][0] == edf_i) ? edf_i : edf_i + 1;

        boat_count++;
    }
    std::cout << boat_count << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while (t-- > 0)
        testcase();
    return 0;
}