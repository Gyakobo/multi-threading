# Multi-Threading or Parallelism

![image](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![image](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![image](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![image](https://img.shields.io/badge/windows%20terminal-4D4D4D?style=for-the-badge&logo=windows%20terminal&logoColor=white)

author: [Andrew Gyakobo](https://github.com/Gyakobo)

This project was made to showcase a sample example of muli-threading in the C programming language. To be more exact, in this project we'll be trying to approximate the value $\pi$. 

## Introduction

Multi-threading is a programming concept where multiple threads are spawned by a process to execute tasks concurrently. Each thread runs independently but shares the process's resources like memory and file handles. Multi-threading can lead to more efficient use of resources, faster execution of tasks, and improved performance in multi-core systems.

### Key Concepts
1. Thread: A lightweight process or the smallest unit of execution within a process.
1. Concurrency vs. Parallelism: Concurrency means multiple threads make progress at the same time, while parallelism means multiple threads run simultaneously on different cores.
1. Synchronization: Mechanism to control the access of multiple threads to shared resources.
Thread Safety: Ensuring that shared data is accessed by only one thread at a time.

## Methodology

We'll be utilizing the function $\dfrac{4}{1 + x^2}$, the integral of which is a near approximation of $\pi$. Thus we'll be calculating the following formula:

$$
\int \dfrac{4}{1 + x^2} \, dx \approx \pi
$$

>[!NOTE]
>The graph below showcases the integrated function. 
<img src="./assets/function.png">

There is of course a minor issue with this calculation. In particular, as the $dx$ component gets ever smaller, the integration gets more precise. Hence it becomes a priority to make the $dx$ as small as possible. This however certainly backfires as with the decreasing $dx$ the integration becomes more complex as there are more facets in the function to compute. 

Here is a more specific example of the aforementioned computation, this isn't a representation of the previously calculated function but still comminucates the same idea: 

<img src="./assets/function_example.jpeg">

As you can witness, the integration is just a summation of all the rectangles entangled under the function. This is roughly what is being calculated:

$f(x_{i})$ - the function $4/(1 + x^2)$

$dx$ - is the select width of the individual squares that we have to compute.

$$
\displaystyle\sum\limits_{i=0}^{\infty} f(x_{i}) \Delta x \approx \pi
$$

From here we can distinctly see that the smaller the $dx$, the more rectangular areas we have have to compute and add up. This however proves to be a challenge cause the more the rectangles the more the computation, and we know that it is essential to have an enormous amount of said shapes.

Henceforth, a viable solution to generate as much rectangles as possible would be to use parallelism and multi-core processing with the C library `<omp.h>`.

## Code snippets

* From the getgo the code greets us with two include statements:

```c 
#include <omp.h>
#include <stdio.h>
```

* Furthermore, we define the `const int num_steps` *(the quantity of rectangles, the area of which shall be integrated)* and then the `double step` *(the dx or the width of each rectangle)*

* Now entering the main scope of our program we initialize the multi-threading aspect using the `#pragma omp parallel` where each so-called thread runs simeaultaneously from one another and calculates the partial area `local_area`.

```c
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
    ...
```

* After calculating the `local_area` all the threads are simeaultaneously halted in one specific scope where they all perform one command; in our case sum up all the partial areas into one `double area` given us our final result.

```c
#pragma omp critical
{
    area += local_area;
}
```

>[!IMPORTANT]
>It is important to acquiesce that before running this program you need to fathom and fully understand the limits of your PC set before making such calculations.

## The OpenMP - open Multi-processing library 

Just as a side note the **OpenMP** library comprises of the following parts. Also feel free to download, edit, commit and leave feedback to the project.

### Compiler Directives

```c
#pragma omp parallel
#pragma omp critical
#pragma omp barrier
#pragma omp master
```

### Functions

```c
include <omp.h>
int omp_get_thread_num()
int omp_get_num_threads()
```

### Compiling and Linking

```bash
gcc -fopenmp # C compiler
g++ -fopenmp # C compiler
```

### Environmental variables

```bash
export OMP_NUM_THREADS=8
export OMP_NESTED=TRUE
```

## License
MIT
