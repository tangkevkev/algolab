#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef double IT;     // choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET; // program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase()
{
    //Number of healthy cells (h) and tumor cells (t)
    int h, t;
    std::cin >> h >> t;

    int total = h + t;

    //Coordinates of healty cell (coord_h) and tumor cells (coord_t)
    std::vector<std::vector<int>> coord_h(h, std::vector<int>(3));
    std::vector<std::vector<int>> coord_t(t, std::vector<int>(3));

    for (int i = 0; i < h; i++)
    {
        std::cin >> coord_h[i][0] >> coord_h[i][1] >> coord_h[i][2];
        //   std::cout << coord_h[i][0] << coord_h[i][1] << coord_h[i][2]<<std::endl;
    }

    for (int i = 0; i < t; i++)
    {
        std::cin >> coord_t[i][0] >> coord_t[i][1] >> coord_t[i][2];
    }

    //We are testing each polynomial degree, until degree <= 30. We start from degree 0. If it works for one degree, break loop
    for (int degree = 0; degree <= 30; degree++)
    {
        //No upper or lower bound for the variables
        Program lp(CGAL::SMALLER, false, 0, false, 0);

        int equation_number = 0;
        //set constraints for the healty cells
        for (auto cell_h : coord_h)
        {
            //column of each variable
            int col = 0;
            for (int x_deg = 0; x_deg <= degree; x_deg++)
            {
                for (int y_deg = 0; y_deg + x_deg <= degree; y_deg++)
                {
                    for (int z_deg = 0; z_deg + y_deg + x_deg <= degree; z_deg++)
                    {
                        double value = std::pow(cell_h[0], x_deg) * std::pow(cell_h[1], y_deg) * std::pow(cell_h[2], z_deg);
                        lp.set_a(col++, equation_number, value);
                    }
                }
            }
            lp.set_b(equation_number, -1);

            equation_number++;
        }

        //Set constraints for tumor cells
        for (auto cell_t : coord_t)
        {
            //column of each variable
            int col = 0;
            for (int x_deg = 0; x_deg <= degree; x_deg++)
            {
                for (int y_deg = 0; y_deg + x_deg <= degree; y_deg++)
                {
                    for (int z_deg = 0; z_deg + y_deg + x_deg <= degree; z_deg++)
                    {

                        //Value can be up to 2⁵⁰, need to be stored in double
                        double value = std::pow(cell_t[0], x_deg) * std::pow(cell_t[1], y_deg) * std::pow(cell_t[2], z_deg);
                        //Needs to be bigger than 0
                        lp.set_a(col++, equation_number, -value);
                    }
                }
            }
            lp.set_b(equation_number, -1);

            equation_number++;
        }

        //Infinite loop without bland
        CGAL::Quadratic_program_options options;
        options.set_pricing_strategy(CGAL::QP_BLAND);
        Solution s = CGAL::solve_linear_program(lp, ET(), options);

        if (s.is_optimal())
        {
            std::cout << degree << std::endl;
            return;
        }
    }
    std::cout << "Impossible!" << std::endl;
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