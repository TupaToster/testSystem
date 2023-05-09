#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <assert.h>
#include "config.h"

int main () {

    char command[200] = "";

    FILE* dataFileSearch = fopen (graphDataNameSearch, "wb");
    assert (dataFileSearch != NULL);

    FILE* dataFileInsert = fopen (graphDataNameInsert, "wb");
    assert (dataFileInsert != NULL);

    for (int testSize = 1; testSize < maxTestSize; testSize++) {

        if (GenerateTests) {

            sprintf (command, "./%s -I", testGen);
            system (command);
        }

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now ();

        sprintf (command, "./%s < %s", subjectName, testFileName);
        system (command);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now ();

        unsigned int elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count ();

        fprintf (dataFileInsert, "%d %u\n", testSize, elapsedTime);

        //=====================================================================================

        if (GenerateTests) {

            sprintf (command, "./%s -S", testGen);
            system (command);
        }

        begin = std::chrono::steady_clock::now ();

        sprintf (command, "./%s < %s", subjectName, testFileName);
        system (command);

        end = std::chrono::steady_clock::now ();

        elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count ();

        fprintf (dataFileSearch, "%d %u\n", testSize, elapsedTime);
    }

    fclose (dataFileSearch);
    fclose (dataFileInsert);
}