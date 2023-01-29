#include <iostream>
#include <fstream> 
#include <string>
#include <stdio.h>
#include "CLI11.hpp"

using namespace std;

// Helper function that returns if a file exists
inline bool fileExists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

int main(int argc, char** argv) {
    CLI::App app{"File Manipulation Tool"};
    string ver = "1.0.0";

    // Create universal variables
    string file1;
    string file2;
    string file3;
    string text;

    // TODO: Create version option function

    // Define 'create' subcommand
    auto create = app.add_subcommand("create", "Create a new file - empty or with optional text\nUsage: cli create filename \"Optional text added to file\"");
    create->add_option("filename", file1, "File to create");
    create->add_option("optional_text", text, "Text added to new file");
    create->require_option(1,2);

    // Define 'copy' subcommand
    auto copy = app.add_subcommand("copy", "Copy a file to a new file\nUsage: cli copy copy_from_filename copy_to_filename");
    copy->add_option("copy_from_filename", file1, "File to copy from");
    copy->add_option("copy_to_filename", file2, "File to copy to");
    copy->require_option(2);

    // Define 'combine' subcommand
    auto combine = app.add_subcommand("combine", "Combine two files into a third\nUsage: cli combine first_filename second_filename filename_to_combine_into ");
    combine->add_option("first_filename", file1, "First file to combine");
    combine->add_option("second_filename", file2, "Second file to combine");
    combine->add_option("filename_to_combine_into", file3, "File to combine into");
    combine->require_option(3);

    // Define 'remove' subcommand
    auto remove = app.add_subcommand("remove", "Remove a file\nUsage: cli remove filename");
    remove->add_option("filename", file1, "File to remove");
    remove->require_option(1);

    // Define 'create' subcommand behavior
    create->callback([&]() {      
        // If file does not exist, create a new file
        // TODO: Account for writing double quotes without need to escape char
        if (!fileExists(file1)) {
            fstream stream;
            stream.open(file1, ios::out);
            stream << text;
            stream.close();

            cout << "Created new file: " << file1 << "\n";

            if(!text.empty()){
                cout << "With text: " << text << "\n";
            }
        } else { 
            cout <<"Error: " << file1 << " already exists\n";
        }
    });

    // Define 'copy' subcommand behavior
    copy->callback([&]() {
        if (fileExists(file1)) {
            if(!fileExists(file2)) {
                ifstream src(file1, ios::binary);
                ofstream dst(file2, ios::binary);
                dst << src.rdbuf();
            } else {
                cout <<"Error: " << file2 << " already exists\n";
            }
        } else { 
            cout <<"Error: " << file1 << " does not exist\n";
        }
    });

    // Define 'combine' subcommand behavior
    combine->callback([&]() {
        if (fileExists(file1) && fileExists(file2)) {
            if (!fileExists(file3)) {
                fstream stream1, stream2, stream3;
                string str1, str2, str3;

                stream1.open(file1,ios::in);
                stream2.open(file2,ios::in);
                stream3.open(file3,ios::out);

                while(getline(stream1, str1)){
                    stream3 << str1;
                    stream3 << endl;
                }

                while(getline(stream2, str2)){
                    stream3 << str2;
                    stream3 << endl;
                }

                stream1.close();
                stream2.close();
                stream3.close();
            } else {
                cout <<"Error: " << file3 << " already exists\n";          
            }
        } else { 
            cout <<"Error: One or more input files do not exist\n";
        }
    });

    // Define 'remove' subcommand behavior
    remove->callback([&]() {
        if (fileExists(file1)) {
            // Cast string to char * to pass to std::remove
            char* fileChar = const_cast<char*>(file1.c_str());

            if (std::remove(fileChar) != 0 ){
                cout <<"Error: " << file1 << " could not be deleted\n";
            } else {
                cout << "Deleted: " << file1 << "\n";
            }
        } else { 
            cout <<"Error: " << file1 << " does not exist\n";
        }
    });

    CLI11_PARSE(app, argc, argv);

    return 0;
}