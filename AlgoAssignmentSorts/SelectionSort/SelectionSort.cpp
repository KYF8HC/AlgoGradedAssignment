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


void selection_sort(std::vector<int>& v)
{
    for (int i = 0; i < static_cast<int>(v.size() - 1); i++)
    {
        int lowest_value_index = i;
        for (int j = i + 1; j < static_cast<int>(v.size()); j++)
        {
            if (v[j] < v[lowest_value_index])
                lowest_value_index = j;
        }
        std::swap(v[i], v[lowest_value_index]);
    }
}

void write_results_to_file(std::ofstream& out_put_file, int size, bool print = false)
{
    out_put_file << "\n" << size << " elements:";

    for (int i = 0; i < 10; i++)
    {
        std::vector<int> v;
        populate_vector(v, size);
        const auto start = std::chrono::high_resolution_clock::now();
        selection_sort(v);
        const auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        const auto microseconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
        out_put_file << std::fixed << std::setprecision(9) << "\nDuration: " << microseconds << " microseconds" <<
            std::endl;
        if (print)
        {
            print_vector(v);
            std::cout << "\n";
        }
    }
}

int main(int argc, char* argv[])
{
    std::ofstream out_put_file;
    out_put_file.open("selection_sort.txt");

    if (!out_put_file)
    {
        out_put_file << "Error opening file." << std::endl;
        return 1;
    }

    write_results_to_file(out_put_file, 10, true);
    write_results_to_file(out_put_file, 50);
    write_results_to_file(out_put_file, 100);
    write_results_to_file(out_put_file, 500);
    write_results_to_file(out_put_file, 1000);
    write_results_to_file(out_put_file, 5000);
}
