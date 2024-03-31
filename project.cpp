#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <algorithm>
#include <initializer_list>
#include <tuple>

int f(int n, int m, std::size_t z, const std::vector<int> &s, const std::vector<std::vector<int> > &matrix, std::vector<std::vector<std::vector<int> > > &dp) {
    if (z >= s.size())
        return 0; // Base case
    else if (n >= static_cast<int>(matrix.size()) || m >= static_cast<int>(matrix.front().size()) || n < 0 || m < 0)
        return INT_MAX; // Base case
    else if (dp.at(n).at(m).at(z) != -1)
        return dp.at(n).at(m).at(z); // Return the value if it has been calculated
    else {
        dp.at(n).at(m).at(z) = std::abs(matrix.at(n).at(m) - s.at(z)) + std::min({ // Calculate the minimum value:
            f(n - 1, m, z + 1, s, matrix, dp), // go down
            f(n + 1, m, z + 1, s, matrix, dp), // go up
            f(n, m - 1, z + 1, s, matrix, dp), // go left
            f(n, m + 1, z + 1, s, matrix, dp), // go right
        });
        return dp.at(n).at(m).at(z);
    }
}

int f(int n, int m, std::size_t z, const std::vector<int> &s, const std::vector<std::vector<int> > &matrix) {
    if (z >= s.size())
        return 0; // Base case
    else if (n >= static_cast<int>(matrix.size()) || m >= static_cast<int>(matrix.front().size()) || n < 0 || m < 0)
        return INT_MAX; // Base case
    else { // Recursive case
        return std::abs(matrix.at(n).at(m) - s.at(z)) + std::min({ // Calculate the minimum value:
            f(n - 1, m, z + 1, s, matrix), // go down
            f(n + 1, m, z + 1, s, matrix), // go up
            f(n, m - 1, z + 1, s, matrix), // go left
            f(n, m + 1, z + 1, s, matrix), // go right
        });
    }
}

// Memoization Wrapper:
int memoization(const std::vector<int> &s, const std::vector<std::vector<int> > &matrix) {
    std::vector<std::vector<std::vector<int> > > dp(matrix.size(), std::vector<std::vector<int> >(matrix.front().size(), std::vector<int>(s.size(), -1)));
    int min = INT_MAX; // Find the minimum value:
    for (int i = 0; i < static_cast<int>(matrix.size()); ++i)
            for (int j = 0; j < static_cast<int>(matrix.front().size()); ++j)
                min = std::min(f(i, j, 0, s, matrix, dp), min); // Calculate the minimum value for each starting point
    return min;
}

// Recursive Wrapper:
int recursive(const std::vector<int> &s, const std::vector<std::vector<int> > &matrix) {
    int min = INT_MAX; // Find the minimum value:
    for (int i = 0; i < static_cast<int>(matrix.size()); ++i)
            for (int j = 0; j < static_cast<int>(matrix.front().size()); ++j)
                min = std::min(f(i, j, 0, s, matrix), min); // Calculate the minimum value for each starting point
    return min;
}

// Iterative
int iterative(const std::vector<int> &s, const std::vector<std::vector<int> > &matrix) {
    std::vector<std::vector<std::vector<int> > > dp(s.size() + 1, std::vector<std::vector<int> >(matrix.size(), std::vector<int>(matrix.front().size(), 0)));
    for (std::size_t i = 1; i < dp.size(); ++i) // Iterate through the matrix:
            for (std::size_t j = 0; j < dp.front().size(); ++j) // Iterate through the rows
                for (std::size_t l = 0; l < dp.front().front().size(); ++l) // Iterate through the columns
                    dp.at(i).at(j).at(l) = std::abs(matrix.at(j).at(l) - s.at(s.size() - i)) + std::min({
                        (j + 1 < dp.front().size() ? dp.at(i - 1).at(j + 1).at(l) : INT_MAX), // Go down
                        (j > 0 ? dp.at(i - 1).at(j - 1).at(l) : INT_MAX), // Go up
                        (l + 1 < dp.front().front().size() ? dp.at(i - 1).at(j).at(l + 1) : INT_MAX), // Go right
                        (l > 0 ? dp.at(i - 1).at(j).at(l - 1) : INT_MAX) // Go left
                    });
    int min = INT_MAX; // Find the minimum value:
    for (std::size_t i = 0; i < dp.back().size(); ++i)
        for (std::size_t j = 0; j < dp.back().front().size(); ++j)
            min = std::min(min, dp.back().at(i).at(j));
    return min;
}
            

// Iterative:
std::tuple<int, std::pair<std::size_t, std::size_t>, std::string> iterative_path(const std::vector<int> &s, const std::vector<std::vector<int> > &matrix) {
    std::vector<std::vector<std::vector<int> > > dp(s.size() + 1, std::vector<std::vector<int> >(matrix.size(), std::vector<int>(matrix.front().size(), 0))); // Create a 3D vector to store the values
    std::vector<std::pair<std::size_t, std::size_t> > path(s.size(), {0, 0});
    for (std::size_t i = 1; i < dp.size(); ++i) // Iterate through the matrix:
            for (std::size_t j = 0; j < dp.front().size(); ++j) // Iterate through the rows
                for (std::size_t l = 0; l < dp.front().front().size(); ++l) // Iterate through the columns
                    dp.at(i).at(j).at(l) = std::abs(matrix.at(j).at(l) - s.at(s.size() - i)) + std::min({
                        (j + 1 < dp.front().size() ? dp.at(i - 1).at(j + 1).at(l) : INT_MAX), // Go down
                        (j > 0 ? dp.at(i - 1).at(j - 1).at(l) : INT_MAX), // Go up
                        (l + 1 < dp.front().front().size() ? dp.at(i - 1).at(j).at(l + 1) : INT_MAX), // Go right
                        (l > 0 ? dp.at(i - 1).at(j).at(l - 1) : INT_MAX) // Go left
                    });
    int min = INT_MAX; // Find the minimum value:
    for (std::size_t i = 0; i < dp.front().size(); ++i)
        for (std::size_t j = 0; j < dp.front().front().size(); ++j)
            if (dp.back().at(i).at(j) < min) {
                path.front() = {i, j}; // Store the starting point
                min = dp.back().at(i).at(j); // Find the minimum for every starting point
            }
    std::string path_s; // String to store the path
    int up, down, left, right; // Find the path:
    std::vector<std::pair<int, int> > coordinate(4, {0, 0});
    for (std::size_t i = 1; i < dp.size() - 1; i++) {
        up = down = left = right = INT_MAX;
        if (path.at(i - 1).first > 0) { // Check if the path is valid
            up = dp.at(dp.size() - i - 1).at(path.at(i - 1).first - 1).at(path.at(i - 1).second);
            coordinate.at(0) = {path.at(i - 1).first - 1, path.at(i - 1).second};
        }
        if (path.at(i - 1).first + 1 < matrix.size()) { // Check if the path is valid
            down = dp.at(dp.size() - i - 1).at(path.at(i - 1).first + 1).at(path.at(i - 1).second);
            coordinate.at(1) = {path.at(i - 1).first + 1, path.at(i - 1).second};
        }
        if (path.at(i - 1).second > 0) { // Check if the path is valid
            left = dp.at(dp.size() - i - 1).at(path.at(i - 1).first).at(path.at(i - 1).second - 1);
            coordinate.at(2) = {path.at(i - 1).first, path.at(i - 1).second - 1};
        }
        if (path.at(i - 1).second + 1 < matrix.front().size()) { // Check if the path is valid
            right = dp.at(dp.size() - i - 1).at(path.at(i - 1).first).at(path.at(i - 1).second + 1);
            coordinate.at(3) = {path.at(i - 1).first, path.at(i - 1).second + 1};
        }

        int smallest = std::min({up, down, left, right}); // Find the smallest value
        if (up == smallest) {
            path_s.push_back('U');
            path.at(i) = coordinate.at(0);
        }
        else if (down == smallest) {
            path_s.push_back('D');
            path.at(i) = coordinate.at(1);
        }
        else if (left == smallest) {
            path_s.push_back('L');
            path.at(i) = coordinate.at(2);
        }
        else {
            path_s.push_back('R');
            path.at(i) = coordinate.at(3);
        }
        path_s.push_back(' ');
    }
    path_s.pop_back(); // Remove the last space
    path.front().first++; // Increment the starting point
    path.front().second++; // Increment the starting point
    std::tuple<int, std::pair<std::size_t, std::size_t>, std::string> tuple(min, path.front(), path_s); // Return the tuple
    return tuple;
}

// Iterative with reduced space complexity:
int iterative_reduced(const std::vector<int> &s, const std::vector<std::vector<int>> &matrix) {
    std::vector<std::vector<std::vector<int> > > dp(2, std::vector<std::vector<int>>(matrix.size(), std::vector<int>(matrix.front().size(), 0)));
    std::size_t i, j, l; // Iterate through the matrix:
    for (i = 1; i < s.size() + 1; ++i) // Iterate through the matrixes
        for (j = 0; j < dp.front().size(); ++j) // Iterate through the rows
            for (l = 0; l < dp.front().front().size(); ++l) // Iterate through the columns
                dp.at((i & 1)).at(j).at(l) = std::abs(matrix.at(j).at(l) - s.at(s.size() - i)) + std::min({ // Calculate the minimum value
                    (j + 1 < dp.front().size() ? dp.at((i - 1) & 1).at(j + 1).at(l) : INT_MAX), // Go down
                    (j > 0 ? dp.at((i - 1) & 1).at(j - 1).at(l) : INT_MAX), // Go up
                    (l + 1 < dp.front().front().size() ? dp.at((i - 1) & 1).at(j).at(l + 1) : INT_MAX), // Go right
                    (l > 0 ? dp.at((i - 1) & 1).at(j).at(l - 1) : INT_MAX) // Go left
                });
    int min = INT_MAX; // Find the minimum value:
    for (std::size_t row = 0; row < dp.front().size(); ++row)
        for (std::size_t j = 0; j < dp.front().front().size(); ++j)
            min = std::min(min, dp.at(!(i & 1)).at(row).at(j)); // Find the minimum for every starting point
    return min;
}

int main() {                
    std::vector<int> s;
    std::vector<std::vector<int> > matrix;
    // Read the input:
    std::ifstream file("input.txt");
    if (file.is_open()) {
        int n, m, z;
        file >> z >> n >> m;
        matrix.resize(n, std::vector<int>(m, 0));
        s.resize(z);
        for (int i = 0; i < z; ++i)
            file >> s.at(i);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                file >> matrix.at(i).at(j);
        file.close();
    }
    else {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    // Calculate the minimum value:


    // Run the memoization:
    // int min = memoization(s, matrix); // Memoization
    // Run the recursive:
    //int min = recursive(s, matrix); // Recursive
    // Run the iterative:
    //int min = iterative(s, matrix); // Iterative
    // Run the iterative with reduced space complexity:
    //int min = iterative_reduced(s, matrix); // Iterative with reduced space complexity

    // Print the output:
    // std::cout << min << std::endl;


    /* We are calling 'iterative_path' which returns a three values: the minimal difference, the starting point, and the path. 
       The function is iterative. */
    std::tuple<int, std::pair<std::size_t, std::size_t>, std::string> tuple = iterative_path(s, matrix); // Iterative with path
    // Write the output:
    std::ofstream output("output.txt");
    if (output.is_open()) {
        output << std::get<0>(tuple) << std::endl << std::get<1>(tuple).first << " " << std::get<1>(tuple).second << std::endl << std::get<2>(tuple);
        output.close();
    }
    else {
        std::cerr << "Error writing to the file" << std::endl;
        return 1;
    }
    return 0;
}