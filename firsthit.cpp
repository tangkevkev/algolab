#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <limits.h>
#include <array>

typedef CGAL::Exact_predicates_exact_constructions_kernel IK;
typedef IK::Ray_2 IK_Ray;
typedef IK::Segment_2 IK_Segment;
typedef IK::Point_2 IK_Point;

double floor_to_double(const IK::FT& x){
    double a = std::floor(CGAL::to_double(x));
    while(a > x) a-=1;
    while (a+1 <= x) a+=1;

    return a;
}

int testcase()
{
    int n;
    std::cin >> n;

    if (n == 0)
    {
        return 0;
    }

    IK::FT x, y, a, b;
    std::cin >> x >> y >> a >> b;

    IK_Ray ray(IK_Point(x, y), IK_Point(a, b));
    IK::FT min_dist = -1;
    bool found_int = false;
    IK_Point min_point(0,0);

    for (int i = 0; i < n; i++)
    {
        long s, t, u, v;
        std::cin >> s >> t >> u >> v;

        IK_Segment seg(IK_Point(s, t), IK_Point(u, v));
        if (CGAL::do_intersect(ray, seg))
        {
            found_int = true;
            auto o = CGAL::intersection(ray, seg);

            if (const IK_Point *op = boost::get<IK_Point>(&*o))
            {
                IK::FT dx = x - op->x();
                IK::FT dy = y - op->y();
                IK::FT new_dist = (dx * dx) + (dy * dy);

                if (new_dist < min_dist || min_dist == -1)
                {
                    min_dist = new_dist;
                    min_point = *op;
                }
            }
            else if (const IK_Segment *op = boost::get<IK_Segment>(&*o))
            {
                auto source = op->source();
                auto target = op->target();

                IK::FT source_dist = ((source.x() - x) * (source.x() - x)) + ((source.y() - y) * (source.y() - y));
                IK::FT target_dist = ((target.x() - x) * (target.x() - x)) + ((target.y() - y) * (target.y() - y));

                if(source_dist < min_dist || target_dist < min_dist || min_dist == -1){
                    if(source_dist < target_dist){
                        min_dist = source_dist;
                        min_point = source;
                    }else{
                        min_dist = target_dist;
                        min_point = target;
                    }
                }

            }
        }
    }

    if (found_int)
    {
        std::cout << floor_to_double(min_point.x()) << " " << floor_to_double(min_point.y()) << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
    }

    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    while (testcase())
        ;
}