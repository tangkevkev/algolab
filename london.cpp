#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <string>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>
    graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder
{
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity)
    {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0;
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};

inline int char_index(char c)
{
    if (c == 'A')
        return 0;
    else if (c == 'B')
        return 1;
    else if (c == 'C')
        return 2;
    else if (c == 'D')
        return 3;
    else if (c == 'E')
        return 4;
    else if (c == 'F')
        return 5;
    else if (c == 'G')
        return 6;
    else if (c == 'H')
        return 7;
    else if (c == 'I')
        return 8;
    else if (c == 'J')
        return 9;
    else if (c == 'K')
        return 10;
    else if (c == 'L')
        return 11;
    else if (c == 'M')
        return 12;
    else if (c == 'N')
        return 13;
    else if (c == 'O')
        return 14;
    else if (c == 'P')
        return 15;
    else if (c == 'Q')
        return 16;
    else if (c == 'R')
        return 17;
    else if (c == 'S')
        return 18;
    else if (c == 'T')
        return 19;
    else if (c == 'U')
        return 20;
    else if (c == 'V')
        return 21;
    else if (c == 'W')
        return 22;
    else if (c == 'X')
        return 23;
    else if (c == 'Y')
        return 24;
    else if (c == 'Z')
        return 25;

    return -1;
}

void testcase()
{

    int w, h;
    std::cin >> h >> w;

    std::string crime_note;
    std::cin >> crime_note;
    int n = crime_note.size();

    //Letters used in the crime_note
    std::vector<int> letters_needed(26, 0);
    for (int i = 0; i < n; i++)
    {
        letters_needed[char_index(crime_note.at(i))]++;
    }

    std::vector<std::string> front(h);
    std::vector<std::string> back(h);

    for (int i = 0; i < h; i++)
    {
        std::cin >> front[i];
    }

    for (int i = 0; i < h; i++)
    {
        std::cin >> back[i];
    }

    graph G(26+(3*h*w));
    edge_adder adder(G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    for (int i = 0; i < 26; i++)
    {
        adder.add_edge(i, v_target, letters_needed[i]);
    }

    //Different node indices
    int vertex_index = 26;

    //Create an edge to each pair of letter [i][j]
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            char front_ij = front[i].at(j);
            char back_ij = back[i].at(w - j - 1);

            int index_front = char_index(front_ij);
            int index_back = char_index(back_ij);

            //Those letters aren't needed, hence we dont need to add it to our flowgraph
            if (letters_needed[index_front] == 0 && letters_needed[index_back] == 0)
                continue;

            //Build an edge with capacity 1 for one letter pair (as we can't use both letters at the same time)
            int index_edge_prev = vertex_index++;
            adder.add_edge(v_source, index_edge_prev, 1);

            if (letters_needed[index_front] > 0)
            {
                int index_edge = vertex_index++;
                adder.add_edge(index_edge_prev, index_edge, 1);
                adder.add_edge(index_edge, index_front, 1);
            }
            if (letters_needed[index_back] > 0)
            {
                int index_edge = vertex_index++;
                adder.add_edge(index_edge_prev, index_edge, 1);
                adder.add_edge(index_edge, index_back, 1);
            }
        }
    }
    int flow = boost::push_relabel_max_flow(G, v_source, v_target);
    if (flow >= n)
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
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
    return 0;
}