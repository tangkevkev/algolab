#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <vector>
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t,
                                                                              traits::edge_descriptor>>>>
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
    int n, m;
    std::cin >> n >> m;
    //Store the known won points of each player
    std::vector<int> known_points(n, 0);
    std::vector<std::vector<int>> unknown_results;

    //Go through all results
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        if (c == 0)
        {
            unknown_results.push_back({a, b});
        }
        else
        {
            int winner = (c == 1) ? a : b;
            known_points[winner]++;
        }
    }

    //Go through all scores, compute the difference between the achieved points and the required score
    std::vector<int> diff(n, 0);
    bool feasible = true;
    int expected_flow = 0;

    for (int i = 0; i < n; i++)
    {
        int score;
        std::cin >> score;

        diff[i] = score - known_points[i];
        expected_flow += diff[i];
        //If player i has already more points than he should have, the score is not feasible
        if (diff[i] < 0)
        {
            feasible = false;
        }
        //       std::cout << "Player " << i <<  " expects: " << diff[i] << std::endl;
        //       std::cout << "Known points: " << known_points[i] <<". Expected score: " << score << std::endl;
    }

    if (!feasible)
    {
        std::cout << "no" << std::endl;
        return;
    }

    if (expected_flow != unknown_results.size())
    {
        std::cout << "no" << std::endl;
        return;
    }

    //Else build the flow graph
    graph G(4); //dummy value of 4 vertices
    edge_adder adder(G);

    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    std::vector<vertex_desc> vertices(n);
    //add an edge between each player and the target, we want to reach the missing points
    for (int i = 0; i < n; i++)
    {
        vertex_desc vertex_i = boost::add_vertex(G);
        adder.add_edge(vertex_i, v_target, diff[i]);
        vertices[i] = vertex_i;
    }

    //Not using duplicate vertex indices
    for (auto u : unknown_results)
    {
        vertex_desc intermediate = boost::add_vertex(G);
        adder.add_edge(v_source, intermediate, 1);
        adder.add_edge(intermediate, vertices[u[0]], 1);
        adder.add_edge(intermediate, vertices[u[1]], 1);
    }

    int flow = boost::push_relabel_max_flow(G, v_source, v_target);
    if (expected_flow == flow)
    {
        std::cout << "yes" << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
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
