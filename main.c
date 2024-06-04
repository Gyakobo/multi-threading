#include <omp.h>
#include <stdio.h>

int main() {
    const int num_steps = 1000;
    double step = 1.0 / num_steps;
    double area = 0;

    #pragma omp parallel
    {
        int id =    omp_get_thread_num();
        int n =     omp_get_num_threads();
        int i;
        double local_area = 0;

        for (i = id; i<num_steps; i+=n) {
            double x = (i + 0.5) * step;
            double y = 4 / (1 + x*x);
            local_area += step * y;
        }

        #pragma omp critical
        {
            area += local_area;
        }
    }

    printf("area = %f\n", area);
    
    return 0;
}



