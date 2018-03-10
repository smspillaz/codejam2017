#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>

int scanForTrees(std::vector<std::string> const &grid, int y, int x) {
    int count = 1;
    int leftBound = x - 1;
    int rightBound = x + 1;

    int size = grid.size();
    int columns = grid[0].size();

    y++;

    printf("Left bound %i Right bound %i\n", leftBound, rightBound);
    while (y < size) {
        if (leftBound >= 0 && rightBound <= columns) {
            /* Check every cell from leftBound to rightBound to see
             * all cells are green, or if there is exactly one cell
             * that is green */
            int green_cell_count = 0;
            int last_green_cell = 0;
            for (int x_check = leftBound; x_check <= rightBound; ++x_check) {
                if (grid[y][x_check] == '#') {
                    green_cell_count++;
                    last_green_cell = x_check;
                }
            }

            printf("Found %i green cells, expected %i\n", green_cell_count, (rightBound - leftBound + 1));

            if (green_cell_count == 1) {
                count += 1;
                leftBound = last_green_cell - 1;
                rightBound = last_green_cell + 1;
            } else if (green_cell_count == (rightBound - leftBound + 1)) {
                count += green_cell_count;
                leftBound--;
                rightBound++;
            }

            printf("Left bound %i Right bound %i\n", leftBound, rightBound);
            printf("Added %i green cells, %i\n", green_cell_count, count);
            y++;
        } else {
            printf("Need to check for single cell\n");
            /* The only thing we can do in this situation is check for a
             * single green cell within the old bounds. If we don't find it
             * we have to break out */
            int green_cell_count = 0;
            int last_green_cell = 0;
            for (int x_check = (leftBound + 1); x_check <= (rightBound - 1); ++x_check) {
                if (grid[y][x_check] == '#') {
                    green_cell_count++;
                    last_green_cell = x_check;
                }
            }

            if (green_cell_count == 1) {
                count++;
                y++;
                leftBound = last_green_cell - 1;
                rightBound = last_green_cell + 1;
                printf("Added single green\n");
            } else {
                break;
            }
        }
        printf("y is %i rows is %i\n", y, size);
    }

    return count;
}

int main() {
    int cases = 0;
    std::cin >> cases;

    int caseNo = 1;

    while (caseNo <= cases) {
        int rows, columns, triangles;
        std::cin >> rows >> columns >> triangles;

        std::vector<std::string> grid;
        grid.reserve(rows);

        /* Append each to the row */
        for (int i = 0; i < rows; ++i) {
            std::string str;
            std::cin >> str;
            grid.push_back(str);
        }

        int bestSize = 0;

        /* Actually, a more naive solution is just to try every
         * cell and check if it is potentially a triangle. If so,
         * we enter a subroutine where we consistently check the
         * next row until we either run out of rows or the next
         * row does not form a part of the tree and then we return
         * the result */
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < columns; ++x) {
                if (grid[y][x] == '#') {
                    int size = scanForTrees(grid, y, x);
                    if (size > bestSize) {
                        bestSize = size;
                    }
                }
            }
        }

        std::cout << std::fixed << "Case #" << caseNo << ": " << bestSize << std::endl;
        caseNo++;
    }
}