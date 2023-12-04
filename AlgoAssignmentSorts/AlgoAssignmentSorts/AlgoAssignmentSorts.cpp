#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

/*
void populate_vector(std::vector<int>& v, const int size)
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

void merge(std::vector<int>& v, const int left, const int mid, const int right)
{
    const auto n1 = mid - left + 1;
    const auto n2 = right - mid;

    std::vector<int> left_vector;
    std::vector<int> right_vector;
    left_vector.reserve(n1);
    for (auto i = 1; i <= n1; i++)
    {
        left_vector.push_back(v[left + i - 1]);
    }
    right_vector.reserve(n2);
    for (auto i = 1; i <= n2; i++)
    {
        right_vector.push_back(v[mid + i]);
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (left_vector[i] <= right_vector[j])
        {
            v[k] = left_vector[i];
            i++;
        }
        else
        {
            v[k] = right_vector[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        v[k] = left_vector[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        v[k] = right_vector[j];
        j++;
        k++;
    }
}

void merge_sort(std::vector<int>& v, const int left, const int right)
{
    if (left < right)
    {
        const auto mid = (left + right) / 2;

        merge_sort(v, left, mid);
        merge_sort(v, mid + 1, right);

        merge(v, left, mid, right);
    }
}

void write_results_to_file(std::ofstream& out_put_file, const int size)
{
    out_put_file << "\n" << size << " elements:";

    for (int i = 0; i < 10; i++)
    {
        std::vector<int> v;
        populate_vector(v, size);
        const auto start = std::chrono::high_resolution_clock::now();
        merge_sort(v, 0, size - 1);
        const auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        const auto microseconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
        out_put_file << std::fixed << std::setprecision(9) << "\nDuration: " << microseconds << " microseconds" <<
            std::endl;
    }
}
*/

//---------------------------------Array Implementation---------------------------------


void populate_vector(int* v, const int size)
{
    for (int i = 0; i < size; i++)
    {
        v[i] = rand() % 10001;
    }
}

void print_vector(int* v, const int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << v[i] << " ";
    }
}

void merge(int* v, const int left, const int mid, const int right)
{
    const auto n1 = mid - left + 1;
    const auto n2 = right - mid;

    const auto left_vector = new int[n1];
    const auto right_vector = new int[n2];
    for (auto i = 1; i <= n1; i++)
    {
        left_vector[i] = v[left + i - 1];
    }
    for (auto i = 1; i <= n2; i++)
    {
        right_vector[i] = v[mid + i];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (left_vector[i] <= right_vector[j])
        {
            v[k] = left_vector[i];
            i++;
        }
        else
        {
            v[k] = right_vector[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        v[k] = left_vector[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        v[k] = right_vector[j];
        j++;
        k++;
    }
}

void merge_sort(int* v, const int left, const int right)
{
    if (left < right)
    {
        const auto mid = (left + right) / 2;

        merge_sort(v, left, mid);
        merge_sort(v, mid + 1, right);

        merge(v, left, mid, right);
    }
}

void write_results_to_file(std::ofstream& out_put_file, const int size)
{
    out_put_file << "\n" << size << " elements:";

    for (int i = 0; i < 10; i++)
    {
        const auto v = new int[size];
        populate_vector(v, size);
        const auto start = std::chrono::high_resolution_clock::now();
        merge_sort(v, 0, size - 1);
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
    out_put_file.open("merge_sort.txt");

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
