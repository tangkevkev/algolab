// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <iostream>
#include <vector>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;



void testcase(){
    int z,j;
    std::cin >> z >> j;

    std::vector<int> zones(z, 0);
    for(int i = 0; i < z; i++){
        std::cin >> zones[i];
    }

    std::vector<std::vector<int>> job_zones;
    std::vector<int> reward(j, 0);

    for(int i = 0; i < j; i++){
        std::cin >> reward[i];
    }

    for(int i = 0; i < j; i++){
        int n1;
        std::cin >> n1;
        std::vector<int> r_zones;
        while(n1-- > 0){
            int k;
            std::cin >> k;
            r_zones.push_back(k);
        }
        job_zones.push_back(r_zones);
    }
    
    Program lp (CGAL::SMALLER, true, 0, true, 1); 
    //variables k_i ,  0 <= i < j. k_i = 1 if job i is made
    //variables b_i, 0 <= i < j . b_i = 1 if ticket for zone i is purchased

    //Objective is to maximize k_1*reward_1 +..+k_j*reward_j - b_1*zones_1 - ... - b_j*zones_j
    //Set constraint such that 0 <= sum of b_z - k_i*L_i (b_z is each zone need for job i. If k_i is taken, the sum has to be L_i which is equals to the required zones for job i)
    //If job i is not taken k_i is zero hence it will be bigger 0
    
    std::vector<int> coeff_k(j, 0);
    std::vector<int> coeff_b(z, 0);


    for(int i = 0; i < j; i++){
        coeff_k[i] = i;
        //Negate (We want to maximize)
        lp.set_c(coeff_k[i], -reward[i]);
    }

    for(int i = 0; i < z; i++){
        coeff_b[i] = i+j;
        //Negate 
        lp.set_c(coeff_b[i], zones[i]);
    }

    for(int eq_number = 0; eq_number < j; eq_number++){
        lp.set_b(eq_number, 0);
        std::vector<int> req_zones = job_zones[eq_number];

        lp.set_a(coeff_k[eq_number], eq_number, req_zones.size());
        for(int i : req_zones){
            lp.set_a(coeff_b[i], eq_number, -1);
        }
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    std::cout << s.objective_value() << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while(t-- > 0){
        testcase();
    }
}