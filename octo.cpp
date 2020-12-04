#include <iostream>
#include <vector>
#include <algorithm>

int sort_snd(std::vector<int> a, std::vector<int> b)
{
    return (a[1] > b[1]);
}

void testcase()
{
    int n;
    std::cin >> n;

    std::vector<int> t(n);            //t(i) = bombing time of bomb i
    std::vector<int> ref_bomb(n, -1); //Reference to the bomb lying on the top
    std::vector<int> ref_count(n, 0); //Counting how much bomb are still lying under it

    //Build bombs dependencies
    for (int i = 0; i <= (n - 3) / 2; i++)
    {
        ref_bomb[2 * i + 1] = i;
        ref_bomb[2 * i + 2] = i;

        ref_count[i] = 2;
    }

    int bomb_time;
    for (int i = 0; i < n; i++)
    {
        std::cin >> bomb_time;
        if (ref_bomb[i] != -1)
            t[i] = std::min(bomb_time, t[ref_bomb[i]]);
        else
            t[i] = bomb_time;

    }


    std::vector<std::vector<int>> toDo;

    //Push bottom bombs to our scheduler
    for (int i = (n - 1) / 2; i < n; i++)
    {
        toDo.push_back({i, t[i]});
    }

    int time = 0;
    bool explodes = false;
    std::sort(toDo.begin(), toDo.end(), sort_snd);

    //From the todo queue, take the one with earliest deadline
    while (!toDo.empty())
    {
        auto current = toDo.back();
        toDo.pop_back();
        int index = current[0];
        int deadline = current[1];

        //  std::cout << "current bomb : " << index << ". has deadline: " << deadline << std::endl;
        //  std::cout << "ref bomb is : " << ref_bomb[index] << std::endl;
        //  std::cout << "time: " << time << std::endl;
        //deadline is already over, it explodes (note that james bond needs 1 time unit to handle one bomb)
        if (time >= deadline)
        {
            explodes = true;
            // std::cout << "explodes" << std::endl;
            break;
        }
        //There's a bomb on top of the bomb at this index
        if (ref_bomb[index] != -1)
        {
            int top_index = ref_bomb[index];
            ref_count[top_index] = ref_count[top_index] - 1;
            //   std::cout << "ref_count of " << top_index << " is : " << ref_count[top_index] << std::endl;

            //no Bomb lies below top-index bomb
            if (ref_count[top_index] == 0)
            {
                //    std::cout << "is 0. top index = " << top_index << std::endl;
                std::vector<int> value(2);
                value = {top_index, t[top_index]};
                auto it =
                    std::lower_bound(toDo.begin(), toDo.end(), value, sort_snd);
                toDo.insert(it, value);
            }
        }
        time++;
    }
    if (explodes)
    {
        std::cout << "no" << std::endl;
    }
    else
    {
        std::cout << "yes" << std::endl;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while (t--)
        testcase();
    return 0;
}