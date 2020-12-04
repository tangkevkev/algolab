#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h> // choose input type (input coefficients must fit)
typedef int IT;        // choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET; // program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int testcase()
{
    int n, m;
    std::cin >> n >> m;
    if (n + m == 0)
        return 0;

    //Store the required nutritions boundaries (min, max of each nutrition)
    std::vector<std::vector<int>> nutr_bounds(n, std::vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        std::cin >> nutr_bounds[i][0] >> nutr_bounds[i][1];
    }

    //Price of each food
    std::vector<int> prices(m);
    //Per food, store the kilocalories for each "vitamin"
    std::vector<std::vector<int>> food_nutr(m, std::vector<int>(n));
    for (int i = 0; i < m; i++)
    {
        std::cin >> prices[i];
        for (int j = 0; j < n; j++)
        {
            std::cin >> food_nutr[i][j];
        }
    }

    //Set objective function to minimize
    //Sum of all r_i * p_i must be minimal, whereby r_i describes the amount of food i, p_i is the price
    //Set that all variables need to be positive >= 0, should not be possible to have negative amount of food
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    //Set objective function (coefficient will be from 0 to m-1). We want the sum to be minimal
    for (int i = 0; i < m; i++)
    {
        lp.set_c(i, prices[i]);
    }

    //Set the constraints, the sum of nutrients from the combination of food must always be situated in the nutrients boundaries
    for (int i = 0; i < n; i++)
    {
        //We establish the following inequality
        //The sum of (each food that contains this nutrient, times the number of its count)
        //Must be in the boundary

        for (int j = 0; j < m; j++)
        {
            //For the upper bound
            lp.set_a(j, i, food_nutr[j][i]);
            //for the lower bound
            lp.set_a(j, i + n, -food_nutr[j][i]);
        }

        lp.set_b(i, nutr_bounds[i][1]);
        lp.set_b(i + n, -nutr_bounds[i][0]);
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_optimal())
    {
        auto nenner = s.objective_value_numerator();
        auto zaehler = s.objective_value_denominator();

        auto result = nenner/zaehler;

        std::cout << result << std::endl;
    }

    if (s.is_infeasible())
    {
        std::cout << "No such diet." << std::endl;
    }

    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while (testcase())
        ;
    return 0;
}