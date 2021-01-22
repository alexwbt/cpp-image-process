#pragma once

template <int S>
struct Kernel
{
    const int size = S * 2 + 1;
    float grid[S * 2 + 1][S * 2 + 1];
};

template <int S>
using KernelPtr = std::shared_ptr<Kernel<S>>;

template <int S>
KernelPtr<S> edge_detect_kernel()
{
    auto kernel = std::make_shared<Kernel<S>>();
    for (int x = 0; x < kernel->size; x++)
        for (int y = 0; y < kernel->size; y++)
            kernel->grid[x][y] = (x == S + 1 && y == S + 1) ? pow(kernel->size, 2) - 1 : -1;
    return std::move(kernel);
}

template <int S>
KernelPtr<S> edge_detect_kernel_2()
{
    auto kernel = std::make_shared<Kernel<S>>();
    for (int x = 0; x < kernel->size; x++)
        for (int y = 0; y < kernel->size; y++)
            kernel->grid[x][y] = (x == S + 1 && y == S + 1) ? (S * 4) : ((x == S + 1 || y == S + 1) ? -1 : 0);
    return std::move(kernel);
}

template <int S, int a = 1>
KernelPtr<S> gaussian_blur_kernel()
{
    auto kernel = std::make_shared<Kernel<S>>();
    for (int x = 0; x < kernel->size; x++)
    {
        for (int y = 0; y < kernel->size; y++)
        {
            kernel->grid[x][y] = (1 / (2 * 3.141519f * a * a)) * exp(-(pow(x - (S + 1), 2) + pow(y - (S + 1), 2)) / (2 * a * a));
        }
    }
    return std::move(kernel);
}
