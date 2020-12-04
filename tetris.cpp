//(100/100 Points) Passes the bordercases (multiple bricks of [0,w] were not taken into account)
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

    //Bricks of length w(filling the whole line);
    int w_bricks = 0;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;
        std::vector<int> brick = {std::min(a, b), std::max(a, b)};

        if (brick[0] == 0 && brick[1] == w)
        {
            w_bricks++;
        }
        else
        {
            bricks.emplace(brick);
        }
    }

    graph G(4);
    edge_adder adder(G);

    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    //Null reference (same as vertex not created yet)
    const vertex_desc null_vertex = boost::add_vertex(G);

    //Keep reference to vertices
    std::vector<vertex_desc> vertices(n, null_vertex);

    //Bottleneck vertex for brick with same end, bottleneck is built with the in and out vertices
    std::vector<vertex_desc> bottleneck_in(w + 1, null_vertex);
    std::vector<vertex_desc> bottleneck_out(w + 1, null_vertex);

    std::vector<bool> bottleneck_init(w + 1, false);
    bottleneck_init[0] = true;
    bottleneck_init[w] = true;

    bottleneck_out[0] = v_source;
    bottleneck_in[w] = v_target;

    for (auto brick : bricks)
    {
        //Vertex for the brick
        vertex_desc vertex = boost::add_vertex(G);
        int left_coord = brick[0];
        int right_coord = brick[1];

        if (bottleneck_init[left_coord] == false)
        {
            bottleneck_in[left_coord] = boost::add_vertex(G);
            bottleneck_out[left_coord] = boost::add_vertex(G);
            adder.add_edge(bottleneck_in[left_coord], bottleneck_out[left_coord], 1);
        }

        if (bottleneck_init[right_coord] == false)
        {
            bottleneck_in[right_coord] = boost::add_vertex(G);
            bottleneck_out[right_coord] = boost::add_vertex(G);
            adder.add_edge(bottleneck_in[right_coord], bottleneck_out[right_coord], 1);
        }

        adder.add_edge(bottleneck_out[left_coord], vertex, 1);
        adder.add_edge(vertex, bottleneck_in[right_coord], 1);

        bottleneck_init[left_coord] = true;
        bottleneck_init[right_coord] = true;
    }

    int flow = boost::push_relabel_max_flow(G, v_source, v_target);
    std::cout << (flow+w_bricks) << std::endl;
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