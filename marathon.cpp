// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

#include <iostream>
#include <vector>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                              boost::no_property, boost::property<boost::edge_weight_t, int, boost::property<boost::edge_capacity_t, int>>>
    weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>
    graph;

typedef traits::vertex_descriptor vertex_desc_flow;
typedef traits::edge_descriptor edge_desc_flow;

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
    int n, m, s, f;
    std::cin >> n >> m >> s >> f;

    weighted_graph G(n + 1);
    weight_map weights = boost::get(boost::edge_weight, G);
    auto capacity = boost::get(boost::edge_capacity, G);

    for (int i = 0; i < m; i++)
    {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        if (a == b)
        {
            continue;
        }
        edge_desc e;
        e = boost::add_edge(a, b, G).first;
        weights[e] = d;
        capacity[e] = c;
        e = boost::add_edge(b, a, G).first;
        weights[e] = d;
        capacity[e] = c;
    }

    int n1 = boost::num_vertices(G);
    std::vector<int> dist_map_source(n1);
    std::vector<int> dist_map_target(n1);

    boost::dijkstra_shortest_paths(G, s,
                                   boost::distance_map(boost::make_iterator_property_map(
                                       dist_map_source.begin(), boost::get(boost::vertex_index, G))));

    boost::dijkstra_shortest_paths(G, f,
                                   boost::distance_map(boost::make_iterator_property_map(
                                       dist_map_target.begin(), boost::get(boost::vertex_index, G))));

    int shortest_path = dist_map_source[f];
    graph G_flow(n + 1);
    edge_adder adder(G_flow);

    auto edge_iters = boost::edges(G);
    for (auto edge_it = edge_iters.first; edge_it != edge_iters.second; ++edge_it)
    {
        const edge_desc edge = *edge_it;
        auto source = boost::source(edge, G);
        auto target = boost::target(edge, G);

        if(dist_map_source[source] < dist_map_source[target]){
            int total = weights[edge] + dist_map_source[source] + dist_map_target[target];
            if(total == shortest_path){
                adder.add_edge(source, target, capacity[edge]);
            }
        }else{
            int total = weights[edge] + dist_map_source[target] + dist_map_target[source];
            if(total == shortest_path){
                adder.add_edge(target, source, capacity[edge]);
            }
        }
    }
    long flow = boost::push_relabel_max_flow(G_flow, s, f);
    std::cout << flow/2 << std::endl;
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
}