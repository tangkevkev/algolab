#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

void testCase()
{
    int n, c, f;
    std::cin >> n >> c >> f;

    graph G(n);

    std::vector<std::vector<std::string>> characteristics(n, std::vector<std::string>());
    std::string new_charasterics;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < c; j++)
        {
            std::cin >> new_charasterics;
            characteristics[i].push_back(new_charasterics);
        }

        std::sort(characteristics[i].begin(), characteristics[i].end());
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            std::vector<std::string> intersection;
            std::set_intersection(characteristics[i].begin(), characteristics[i].end(),
                                  characteristics[j].begin(), characteristics[j].end(), std::back_inserter(intersection));

            if (intersection.size() > f)
            {
                boost::add_edge(i, j, G);
            }
        }
    }
    std::vector<vertex_desc> mate_map(n); // exterior property map
    boost::edmonds_maximum_cardinality_matching(G,
                                                boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    int matching_size = boost::matching_size(G,
                                             boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

    if (matching_size * 2 == n)
    {
        std::cout << "not optimal" << std::endl;
    }
    else
    {
        std::cout << "optimal" << std::endl;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t-- > 0)
        testCase();
    return 0;
}