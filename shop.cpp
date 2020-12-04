#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <vector>

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
    int n, m, s;
    std::cin >> n >> m >> s;

    graph G(4);
    edge_adder adder(G);

    std::vector<vertex_desc> vertices(n);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    vertices[0] = v_source;
    for (int i = 1; i < n; i++)
    {
        vertices[i] = boost::add_vertex(G);
    }

    for (int i = 0; i < s; i++)
    {
        int index;
        std::cin >> index;
        //Add a connection to the target (each shop should lead to the target node)
        adder.add_edge(vertices[index], v_target, 1);
    }

    for (int i = 0; i < m; i++)
    {
        int from, to;
        std::cin >> from >> to;
        //Its bidirectional, hence we need to add a edge in the opposite direction too
        adder.add_edge(vertices[from], vertices[to], 1);
        adder.add_edge(vertices[to],vertices[from], 1);
    }

    //This works as we are only using each edge at most once in a max flow (setting each edge with weight 1)
    int flow = boost::push_relabel_max_flow(G, v_source, v_target);

    if (flow == s)
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
    while (t-- > 0)
    {
        testcase();
    }

    return 0;
}