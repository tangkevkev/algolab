#include <iostream>
#include <queue>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>
    graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

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
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};

void testcase()
{
    int g, s, l;
    std::cin >> g >> s >> l;

    graph G(0);
    edge_adder adder(G);

    std::vector<vertex_desc> radio(g);
    std::vector<vertex_desc> satellite(s);

    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    //Create vertices for radio (ground stations)
    for (int i = 0; i < g; i++)
    {
        radio[i] = boost::add_vertex(G);
        adder.add_edge(v_source, radio[i], 1);
    }

    //Create vertices for satellites, connecting to the target
    for (int i = 0; i < s; i++)
    {
        satellite[i] = boost::add_vertex(G);
        adder.add_edge(satellite[i], v_target, 1);
    }

    for (int i = 0; i < l; i++)
    {
        int radio_index, sat_index;
        std::cin >> radio_index >> sat_index;
        adder.add_edge(radio[radio_index], satellite[sat_index], 1);
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    // Retrieve capacity map and reverse capacity map
    const auto c_map = boost::get(boost::edge_capacity, G);
    const auto rc_map = boost::get(boost::edge_residual_capacity, G);

    //BFS to find vertex set S
    std::vector<bool> visited(g + s + 2, false);
    std::queue<vertex_desc> toDo;

    visited[v_source] = true;
    toDo.push(v_source);

    while (!toDo.empty())
    {
        const int u = toDo.front();
        toDo.pop();

        out_edge_it ebeg, eend;
        for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg)
        {
            const int v = boost::target(*ebeg, G);
            if (rc_map[*ebeg] == 0 || visited[v] == true)
                continue;
            visited[v] = true;
            toDo.push(v);
        }
    }
    int count_g = 0, count_s = 0;

    for (int i = 0; i < g; i++)
    {
        if (!visited[radio[i]])
        {
            count_g++;
        }
    }

    for (int i = 0; i < s; i++)
    {
        if (visited[satellite[i]])
        {
            count_s++;
        }
    }

    std::cout << count_g << " " << count_s << std::endl;
    for (int i = 0; i < g; i++)
    {
        if (!visited[radio[i]])
        {
            std::cout << i << " ";
        }
    }

    for (int i = 0; i < s; i++)
    {
        if (visited[satellite[i]])
        {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
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
