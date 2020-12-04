
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

//Full points

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;


// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};


void testcase() {
	int n;
	int expected_flow = 0;

	std::cin >> n;

	std::vector<std::vector<int>> ac (n, std::vector<int>(2));
	for(int i = 0; i < n; i++){
		int a,c;
		std::cin >> a >> c;
		ac[i] = {a,c};
	}

	std::vector<std::vector<int>> sp (n, std::vector<int>(2));
	for(int i = 0; i < n; i++){
		int s,p;
		std::cin >> s >> p;
		sp[i] = {s, p};
		expected_flow += s;
	}

	std::vector<std::vector<int>> ve (n, std::vector<int>(2));
	for(int i = 0; i < n-1; i++){
		int v,e;
		std::cin >> v >> e;
		ve[i+1] = {v,e};
	}
	graph G(2);
	edge_adder adder(G);  
    
	auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    
	const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

	std::vector<vertex_desc> day_vertex(n);
	for(int i = 0; i < n; i++){
		day_vertex[i] = boost::add_vertex(G);
		adder.add_edge(v_source, day_vertex[i], ac[i][0], ac[i][1]);
		adder.add_edge(day_vertex[i], v_target, sp[i][0], 20-sp[i][1]);
	}

	for(int i = 1; i < n; i++){
		adder.add_edge(day_vertex[i-1], day_vertex[i], ve[i][0], ve[i][1]);
	}

	boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost = boost::find_flow_cost(G);
	int earning = 0;
    int flow = 0;

    out_edge_it e, eend;
	int i = 0;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_target,G), G); e != eend; ++e) {
     //   std::cout << "edge from " << boost::target(*e, G) << " to " << boost::source(*e, G) 
       //     << " with capacity " << c_map[r_map[*e]] << " and residual capacity " << rc_map[r_map[*e]] << "\n";
		int edge_flow = rc_map[*e] - c_map[*e];
        flow += edge_flow; 
		earning += edge_flow*sp[i++][1];
		cost -= edge_flow*(20-sp[i-1][1]);
    }

	if(flow == expected_flow){
		std::cout << "possible " << flow << " " <<  (earning-cost) << std::endl; 
	} else{
		std::cout << "impossible " << flow << " " << (earning-cost) << std::endl; 
	}

	

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
