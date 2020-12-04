#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/enum.h>

#include <CGAL/Exact_circular_kernel_2.h>


//#include "printlp.hpp"



// choose input type (input coefficients must fit)
typedef double IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_circular_kernel_2 K;

typedef K::Point_2 Point;
typedef K::Circle_2 Circle;
typedef K::Line_2 Segment;

long floor_to_double(const CGAL::Quotient<ET> &x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(){
    int n,m,c;
    std::cin >> n >> m >> c;
    std::vector<std::vector<int>> whs(n, std::vector<int>(4,0));
    std::vector<std::vector<int>> stds(m, std::vector<int>(4,0));
    std::vector<std::vector<int>> rws(n, std::vector<int>(m,0));
    std::vector<std::vector<int>> ctrs(c, std::vector<int>(3,0));
    std::vector<Point> point_whs(n);
    std::vector<Point> point_std(m);

    for(int i = 0; i < n; i++){
        std::cin >> whs[i][0] >> whs[i][1] >> whs[i][2] >> whs[i][3];
        point_whs[i] = Point(whs[i][0], whs[i][1]);
    }

    for(int i = 0; i < m; i++){
        std::cin >> stds[i][0] >> stds[i][1] >> stds[i][2] >> stds[i][3];
        point_std[i] = Point(stds[i][0], stds[i][1]);
    }   

    std::vector<std::vector<Segment>> segments(n, std::vector<Segment>(m));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            std::cin >> rws[i][j]; 
            rws[i][j] *= 100;
            segments[i][j] = Segment(point_whs[i], point_std[j]);
        }
    }

    std::vector<Circle> circles(c);
    for(int i = 0; i < c; i++){
        std::cin >> ctrs[i][0] >> ctrs[i][1] >> ctrs[i][2];
        circles[i] = Circle(Point(ctrs[i][0], ctrs[i][1]), ctrs[i][2]);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            Segment ij_segment = segments[i][j];
            for(int k = 0; k < c; k++){
                if(CGAL::do_intersect(ij_segment, circles[k])){
                    rws[i][j] -= 1;
                }
            }         
        }
    }

    std::vector<std::vector<int>> rws_index(n, std::vector<int>(m,0));
    int index = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            rws_index[i][j] = index++;
        }
    }
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    for(int i = 0; i < n; i++){
        for(int j = 0 ;j < m; j++){
            lp.set_c(rws_index[i][j], -rws[i][j]);
        }
    }

    for(int i = 0; i < m; i++){
        //First equation set that we deliver the exact amount of fluid
        //Second equation set that we don't deliver more pure alcohol than allowed
        int first_eq = 2*i;
        int second_eq = (2*i)+1;
        lp.set_r(first_eq, CGAL::EQUAL);
        for(int j = 0; j < n; j++){
            lp.set_a(rws_index[j][i],first_eq, 100);   
            double pure_alc = double(whs[j][3]);
            lp.set_a(rws_index[j][i], second_eq, pure_alc);
        }
        lp.set_b(first_eq, stds[i][2]*100);
        lp.set_b(second_eq, stds[i][3]*100);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m ; j++){
            lp.set_a(rws_index[i][j],2*m+i, 1);
        }
        lp.set_b(2*m+i, whs[i][2]);
        lp.set_r(2*m+i, CGAL::SMALLER);
    }

    Solution s = CGAL::solve_linear_program(lp, ET());

  //  std::cout << lp << std::endl;
  /*  std::cout << s << std::endl;
    std::cout << "-------" << std::endl;*/

    if(s.is_optimal()){
        long res = (floor_to_double(-s.objective_value()));
        std::cout << res/100 << std::endl;

    }else if(s.is_infeasible()){
        std::cout << "RIOT!"<< std::endl;
    }



}

int main(int argc, char const *argv[]) {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--){
        testcase();
    }    
}
