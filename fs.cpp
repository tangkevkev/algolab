#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property,                        // no vertex property
                              boost::property<boost::edge_weight_t, int> // interior edge weight property
                              >
    weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

void testcase()
{
    int n, m;

    std::cin >> n;
    std::cin >> m;

    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);

    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        std::cin >> from;
        std::cin >> to;
        std::cin >> weight;
        edge_desc e;
        e = boost::add_edge(from, to, G).first;
        weights[e] = weight;
    }

    std::vector<edge_desc> mst; // vector to store MST edges (not a property map!)
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

    int mst_weight = 0;

    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it)
    {
        mst_weight += weights[*it];
    }

    std::vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, 0, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));

    int max_dist = *std::max_element(dist_map.begin(), dist_map.end());

    std::cout << mst_weight << " " << max_dist << std::endl;
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