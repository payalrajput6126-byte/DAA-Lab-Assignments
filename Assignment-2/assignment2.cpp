#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Movie {
    string title;
    int year;
    double rating;
    int watchTime;
};

const int MAX = 10000;
Movie movies[MAX];
int count = 0;

void swapMovies(int i, int j) {
    Movie temp = movies[i];
    movies[i] = movies[j];
    movies[j] = temp;
}

int partition(int low, int high, int sortBy) {
    double pivot;
    if (sortBy == 1) pivot = movies[high].rating;
    else if (sortBy == 2) pivot = movies[high].year;
    else pivot = movies[high].watchTime;

    int i = low - 1;
    for (int j = low; j < high; j++) {
        double value;
        if (sortBy == 1) value = movies[j].rating;
        else if (sortBy == 2) value = movies[j].year;
        else value = movies[j].watchTime;

        if (value >= pivot) {
            i++;
            swapMovies(i, j);
        }
    }
    swapMovies(i + 1, high);
    return i + 1;
}

void quicksort(int low, int high, int sortBy) {
    if (low < high) {
        int p = partition(low, high, sortBy);
        quicksort(low, p - 1, sortBy);
        quicksort(p + 1, high, sortBy);
    }
}

void splitLine(const string& line, string fields[], int maxFields) {
    int idx = 0;
    string field;
    bool inQuotes = false;

    for (int i = 0; i < (int)line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            if (idx < maxFields) fields[idx++] = field;
            field.clear();
        } else {
            field += c;
        }
    }
    if (idx < maxFields) fields[idx++] = field;
}

int main() {
    ifstream file("Top_10000_Movies.csv\\Top_10000_Movies.csv");
    if (!file.is_open()) {
        cout << "Could not open file. Put the CSV in the same folder.\n";
        return 0;
    }

    string line;
    getline(file, line); // header row
    cout << "Header: " << line << "\n";

    const int NUM_COLS = 13;
    int rowNum = 0;
    int printedErrors = 0;

    while (getline(file, line) && count < MAX) {
        rowNum++;
        string fields[NUM_COLS];
        splitLine(line, fields, NUM_COLS);

        try {
            string title = fields[3];
            string releaseDate = fields[5];
            string ratingStr = fields[6];
            string runtimeStr = fields[11];

            if (title.empty() || releaseDate.size() < 4) {
                if (printedErrors < 5) {
                    cout << "Row " << rowNum << " skipped (empty title/date). title=[" << title << "] date=[" << releaseDate << "]\n";
                    printedErrors++;
                }
                continue;
            }

            int year = stoi(releaseDate.substr(0, 4));
            double rating = stod(ratingStr);
            int runtime = runtimeStr.empty() ? 0 : (int)stod(runtimeStr);

            movies[count].title = title;
            movies[count].year = year;
            movies[count].rating = rating;
            movies[count].watchTime = runtime;
            count++;
        } catch (exception& e) {
            if (printedErrors < 5) {
                cout << "Row " << rowNum << " FAILED: " << e.what() << " | raw line: " << line.substr(0, 100) << "\n";
                printedErrors++;
            }
            continue;
        }
    }

    cout << "Loaded " << count << " movies.\n";

    int choice;
    cout << "Sort by: 1-Rating  2-Year  3-Watch Time\nEnter choice: ";
    cin >> choice;

    quicksort(0, count - 1, choice);

    cout << "\nTop 10 Movies:\n";
    for (int i = 0; i < 10 && i < count; i++) {
        cout << movies[i].title << " (" << movies[i].year << ") | "
             << "Rating: " << movies[i].rating << " | "
             << "Runtime: " << movies[i].watchTime << " min\n";
    }

    return 0;
}
