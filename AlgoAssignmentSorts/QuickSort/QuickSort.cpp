#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

void populate_vector(std::vector<int>& v, int size)
{
    for (int i = 0; i < size; i++)
    {
        v.push_back(rand() % 10001);
    }
}

void print_vector(std::vector<int>& v)
{
    for (int i : v)
    {
        std::cout << i << " ";
    }
}

int partition(std::vector<int>& v, int const& low, int const& high)
{
    const int pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (v[j] <= pivot)
        {
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[high]);
    return i + 1;
}

void quick_sort(std::vector<int>& v, int const& low, int const& high)
{
    if (low > high || low < 0 || high < 0)
        return;

    const int pi = partition(v, low, high);

    quick_sort(v, low, pi - 1);
    quick_sort(v, pi + 1, high);
}

void write_results_to_file(std::ofstream& out_put_file, int size)
{
    out_put_file << "\n" << size << " elements:";

    for (int i = 0; i < 10; i++)
    {
        std::vector<int> v;
        populate_vector(v, size);
        const auto start = std::chrono::high_resolution_clock::now();
        quick_sort(v, 0, size - 1);
        const auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        const auto microseconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
        out_put_file << std::fixed << std::setprecision(9) << "\nDuration: " << microseconds << " microseconds" <<
            std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::ofstream out_put_file;
    out_put_file.open("quick_sort.txt");

    if (!out_put_file)
    {
        out_put_file << "Error opening file." << std::endl;
        return 1;
    }
    
    write_results_to_file(out_put_file, 10);
    write_results_to_file(out_put_file, 50);
    write_results_to_file(out_put_file, 100);
    write_results_to_file(out_put_file, 500);
    write_results_to_file(out_put_file, 1000);
    write_results_to_file(out_put_file, 5000);
}