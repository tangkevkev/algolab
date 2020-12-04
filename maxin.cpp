//Full points

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>

typedef int IT;
typedef CGAL::Gmpz ET;


typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int testcase()
{
    int type;
    std::cin >> type;
    if (type == 0)
    {
        return 0;
    }
    
        
    const int X = 0;
    const int Y = 1;
    const int Z = 2;

    //upper bound of variable x,y,z to be lesser equal 0
    //lower bound of variables x,y to be greater equal 0
    // depending of the type
    Program lp(CGAL::SMALLER, (type == 1), 0, (type == 2), 0);

    int a, b;
    std::cin >> a >> b;
    
    if (type == 1)
    {
        //First equation
        lp.set_a(X, 0, 1);
        lp.set_a(Y, 0, 1);
        lp.set_b(0, 4); //x + y <= 4
        //second equation
        lp.set_a(X, 1, 4);
        lp.set_a(Y, 1, 2);
        lp.set_b(1, a * b); //4x + 2y <= ab
        //third equation
        lp.set_a(X, 2, -1);
        lp.set_a(Y, 2, 1);
        lp.set_b(2, 1); //-x+y <= 1

        //Set objective function
        lp.set_c(X, a);
        lp.set_c(Y, -b);
    }
    else
    {
        
        //First equation
        lp.set_a(X, 0, -1);
        lp.set_a(Y, 0, -1);
        lp.set_b(0, 4); //-x - y <= 4
        //Second equation
        lp.set_a(X, 1, -4);
        lp.set_a(Y, 1, -2);
        lp.set_a(Z, 1, -1);
        lp.set_b(1, a * b); // -4x - 2y - z <= ab
        //Third equation
        lp.set_a(X, 2, 1);
        lp.set_a(Y, 2, -1);
        lp.set_b(2, 1); // x - y <= 1

        lp.set_c(X, a);
        lp.set_c(Y, b);
        lp.set_c(Z, 1);
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if (s.is_optimal())
    {
        auto zaehler = s.objective_value_numerator();
        auto nenner =s.objective_value_denominator();
        
        auto result = zaehler/nenner;
        if(type == 1){
            result *= -1;
        }else{
            if(s.objective_value() > result && result > 0){
                result += 1;
            }
        }

        std::cout << result << std::endl;
    }
    else if (s.is_unbounded())
    {
        std::cout << "unbounded" << std::endl;
    }
    
    else if (s.is_infeasible())
    {
        std::cout << "no" << std::endl;
    }

    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while (testcase() == 1)
        ;
    return 0;
}