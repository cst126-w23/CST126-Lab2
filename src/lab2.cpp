#include <iostream>
#include <fstream>

char* strdup(const char* s) {

    //initializes length of the new string (s2) to the length of the original string (s) by adding 1 to the value returned by the strlen function, to make room for null terminator
    char* s2 = new char[strlen(s) + 1]{};

    //uses built-in copy function to copy contents of the first string (s2) to the new string (s)
    strcpy(s2, s);

    return s2;
}

void stringReverse(char*& item) {

    int n = strlen(item);    //intializes "n" to the length of the item c-string

    for (size_t i{}; i < n / 2; i++) {   //swaps the first letter of string to last letter, second letter to second last letter, etc

        char temp_item = item[i];

        item[i] = item[n - i - 1];

        item[n - i - 1] = temp_item;
    }
}

void append(char**& items, size_t& len, char* item) {  //passes items and len in by reference

    len++; //variable increments by one, thus accurately keeping track of the amount of c-strings in the array

    //dynamically allocates memory for a temporary 2-D array to store the item c-string
    char** temp_items = new char* [len];

    //assigns each element of the items array to each element of the temp array, thus creating a copy of the items array.
    for (size_t i{}; i < len; i++) {
        temp_items[i] = items[i];
    }

    temp_items[len] = item;   //adds the word copied by the buffer to the temporary array

    delete[] items;  //frees allocated memory

    items = temp_items;    //replaces contents of the items array with the temp array that contains the new word that is copied by the buffer
}

int main(int argc, char* argv[]) {

    //checks if user passed any command line arguments
    if (argc < 2) {
        std::cerr << "Please provide a filename.\n";
        return 1; // exit the program with an error return code
    }

    //const ensures pointer value cant be changed, filename initialized to argv[1] so that program can use filename argument provided by user to read and access a file
    const char* filename{ argv[1] };

    char** items{}; //initializes pointer to pointer, which can create array of strings, currently doesnt point to anything

    size_t len{}; //blank brackets {} initiazlies variable to zero, variable len is used to keep track of number of items in "items" array

    char buffer[256]{}; //allocate a buffer on the stack so we have somewhere to put things

    std::ifstream f{ filename };

    //loop that reads file line by line by using getline function, which stores each line in buffer until 255 characters are stored or there is a newline terminator 
    while (f.getline(buffer, 255)) {

        char* item = strdup(buffer); //creates a duplicate of the buffer and assigns it to to item, a temporary char pointer variable called item

        append(items, len, item);   //appends the word duplicated from the buffer to the items array

        stringReverse(item);

        std::cout << item << '\n';
    }

    for (int i = 0; i < len; i++) { //loops through each c-string and deallocates their memory

        delete[] items[i];
    }

    delete[] items; //deallocates memory for each pointer associated with "items"



}
