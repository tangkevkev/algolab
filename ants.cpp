#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property,                        // no vertex property
                              boost::property<boost::edge_weight_t, int> // interior edge weight property
                              >
    weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor Vertex;

void testcase()
{
    int n, e, s, a, b;
    std::cin >> n >> e >> s >> a >> b;

    std::vector<weighted_graph> graphs(s);
    std::vector<weight_map> weights(s);

    weighted_graph combined_graph(n);
    weight_map combined_weights = boost::get(boost::edge_weight, combined_graph);

    weighted_graph graph_i(n);
    for (int i = 0; i < s; i++)
    {
        graphs.push_back(graph_i);
        weights.push_back(boost::get(boost::edge_weight, graphs[i]));
    }

    for (int i = 0; i < e; i++)
    {
        int from, to;
        std::cin >> from;
        std::cin >> to;

        edge_desc e;

        for (int j = 0; j < s; j++)
        {
            int weight;
            std::cin >> weight;

            e = boost::add_edge(from, to, graphs[j]).first;
            weights[j][e] = weight;
            e = boost::add_edge(from, to, combined_graph).first;
            combined_weights[e] = INT_MAX;
        }
    }

    std::vector<int> hives(n);
    //Reading in hives, which are irrelevant to our solution
    for (int i = 0; i < s; i++)
    {
        int unused;
        std::cin >> unused;
        hives.push_back(unused);
    }

    std::vector<std::vector<edge_desc>> mst(s); // vector to store MST edges (not a property map!)
    for (int i = 0; i < s; i++)
    {
        boost::kruskal_minimum_spanning_tree(graphs[i], std::back_inserter(mst[i]));
    }

    for (int i = 0; i < s; i++)
    {

        for (std::vector<edge_desc>::iterator it = mst[i].begin(); it != mst[i].end(); ++it)
        {
            auto from = boost::source(*it, graphs[i]);
            auto to = boost::target(*it, graphs[i]);

            auto edge_i = boost::edge(from, to, graphs[i]).first;
            auto edge_comb = boost::edge(from, to, combined_graph).first;


            combined_weights[edge_comb] = std::min(combined_weights[edge_comb], weights[i][edge_i]);
        }
    }

    std::vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(combined_graph, a,
                                   boost::distance_map(
                                       boost::make_iterator_property_map(dist_map.begin(),
                                                                         boost::get(boost::vertex_index, combined_graph))));
    std::cout << dist_map[b] << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++)
        testcase();

    return 0;
}