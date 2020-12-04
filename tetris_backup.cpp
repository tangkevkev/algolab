#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

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

void testcase()
{
    int w, n;
    std::cin >> w;
    std::cin >> n;

    //Using set as we dont need duplicates of bricks and + it is sorted
    std::set<std::vector<int>> bricks;
    //Working with vector is cooler (store bricks in the vector later)
    std::vector<std::vector<int>> v_bricks;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;
        std::vector<int> brick = {std::min(a, b), std::max(a, b)};
        bricks.emplace(brick);
    }

    //We store the indices of the bricks with the same left ends
    std::vector<std::vector<int>> left_ends(w, std::vector<int>());

    graph G(4);
    edge_adder adder(G);

    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    //Null reference (same as vertex not created yet)
    const vertex_desc null_vertex = boost::add_vertex(G);

    //Keep reference to vertices
    std::vector<vertex_desc> vertices(n, null_vertex);

    //Bottleneck for brick with same right side
    std::vector<vertex_desc> bottlenecks(w, null_vertex);
    bottlenecks[0] = v_source;
    bottlenecks[w - 1] = v_target;

    //Not sure if efficient, but since set is not providing random access ...
    //Convert set to vector
    int total_lines = 0;
    int b_i = 0;
    //Bricks we need to process
    std::vector<int> toDo;

    for (auto b : bricks)
    {
        //Brick b covers the whole line
        if (b[0] == 0 && b[1] == w - 1)
        {
            total_lines++;
            continue;
        }

        if (b[0] == 0)
        {
            toDo.push_back(b_i);
        }
        v_bricks.push_back(b);
        left_ends[b[0]].push_back(b_i);

        b_i++;
    }

    std::cout << "segfaul here" << std::endl;

    std::vector<bool> processed(n, false);
    std::cout << "segfaul here 1" << std::endl;

    while (toDo.size() > 0)
    {
        std::cout << "segfaul here 2" << std::endl;

        int cur_index = toDo.back();

        toDo.pop_back();

        //Get left and right position of the brick
        auto cur_brick = v_bricks[cur_index];

        int left = cur_brick[0];
        int right = cur_brick[1];

        if (vertices[cur_index] == null_vertex)
        {
            vertices[cur_index] = boost::add_vertex(G);
        }
        auto cur_vertex = vertices[cur_index];

        //Connect the brick vertex to the left and right bottleneck
        if (bottlenecks[left] == null_vertex)
        {
            bottlenecks[left] = boost::add_vertex(G);
        }
        if (bottlenecks[right] == null_vertex)
        {
            bottlenecks[right] = boost::add_vertex(G);
        }
        std::cout << "before pro" << std::endl;

        if (processed[cur_index])
            continue;

        std::cout << "after pro" << std::endl;

        adder.add_edge(cur_vertex, bottlenecks[left], 1);
        adder.add_edge(cur_vertex, bottlenecks[right], 1);
        processed[cur_index] = true;

        for (int r_index : left_ends[right])
        {
            toDo.push_back(r_index);
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while (t-- > 0)
    {
        testcase();
    }
    return 0;
}