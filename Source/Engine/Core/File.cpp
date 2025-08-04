#include "File.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <system_error>
#include <iostream>
namespace bonzai::file {

    /// <summary>
    /// Retrieves the current working directory as a string.
    /// </summary>
    /// <returns>A string containing the current working directory, or an empty string if an error occurs.</returns>
    std::string GetCurrentDirectory() {
        std::error_code ec;
        auto path = std::filesystem::current_path();
        return ec ? std::string{} : path.string();
    }

    /// <summary>
    /// Sets the current working directory to the specified path.
    /// </summary>
    /// <param name="path">The path to set as the current working directory.</param>
    /// <returns>True if the operation was successful; otherwise, false.</returns>
    bool SetCurrentDirectory(const std::string& path) {
        std::error_code ec;
        std::filesystem::current_path(path);

        return !ec;
    }
    /// <summary>
    /// Extracts the file extension from a given file path.
    /// </summary>
    /// <param name="path">The file path from which to retrieve the extension.</param>
    /// <returns>The file extension as a string, including the leading dot if present. Returns an empty string if the path has no extension.</returns>
    std::string GetExtension(const std::string& path) {
        std::filesystem::path p(path);
        return p.extension().string();
    }
    /// <summary>
    /// Extracts the filename without extension from a given file path.
    /// </summary>
    /// <param name="path">The file path as a string.</param>
    /// <returns>The filename without its extension as a string.</returns>
    std::string GetFilename(const std::string& path) {
        std::filesystem::path p(path);
        return p.stem().string();
    }
    /// <summary>
    /// Checks whether a file or directory exists at the specified path.
    /// </summary>
    /// <param name="path">The path to the file or directory to check.</param>
    /// <returns>True if the file or directory exists and no error occurred; otherwise, false.</returns>
    bool Exists(const std::string& path) {
        std::error_code ec;
        bool result = std::filesystem::exists(path, ec);

        return !ec && result;
    }
    /// <summary>
    /// Retrieves a list of file paths for all regular files in the specified directory.
    /// </summary>
    /// <param name="path">The path to the directory to search for files.</param>
    /// <returns>A vector of strings containing the paths of regular files found in the directory. Returns an empty vector if an error occurs.</returns>
    std::vector<std::string> GetFilesInDirectory(const std::string& path) {
        std::vector<std::string> files;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return files; // return empty vector on error

        for (const auto& entry : iter) {
            if (entry.is_regular_file(ec) && !ec) {
                files.push_back(entry.path().string());
            }
        }

        return files;
    }
    /// <summary>
    /// Retrieves a list of directories within the specified path.
    /// </summary>
    /// <param name="path">The path to the directory whose subdirectories are to be listed.</param>
    /// <returns>A vector of strings containing the paths of all directories found within the specified path. Returns an empty vector if an error occurs.</returns>
    std::vector<std::string> GetDirectoriesIn(const std::string& path) {
        std::vector<std::string> directories;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return directories; // return empty vector on error

        for (const auto& entry : iter) {
            if (entry.is_directory(ec) && !ec) {
                directories.push_back(entry.path().string());
            }
        }

        return directories;
    }
    /// <summary>
    /// Reads the contents of a text file into a string.
    /// </summary>
    /// <param name="path">The path to the text file to be read.</param>
    /// <param name="content">A reference to a string where the file's contents will be stored.</param>
    /// <returns>Returns true if the file was successfully read; otherwise, returns false.</returns>
    bool ReadTextFile(const std::string& path, std::string& content) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return false;
        }
        // Open the file
        
        std::string str;
        if (file) {
            std::ostringstream ss;
            // Read entire file into stringstream
            ss << file.rdbuf();
            // Convert to string
            str = ss.str();
        }
        else {
            std::cerr << "Error: Could not open the file.\n";
            return 1;
        }
        // Store file content
		content = str;
        file.close();

            return true;
       
    }
    /// <summary>
    /// Writes the specified content to a text file at the given path.
    /// </summary>
    /// <param name="path">The path to the text file to write.</param>
    /// <param name="content">The content to write into the file.</param>
    /// <param name="append">If true, appends the content to the file; if false, overwrites the file.</param>
    /// <returns>True if the file was successfully written; false otherwise.</returns>
    bool WriteTextFile(const std::string& path, const std::string& content, bool append) {
        std::ios::openmode mode = append ? std::ios::app : std::ios::out;
        std::ofstream file(path, mode);
        if (!file.is_open()) {
            return false;
        }

        // read content string into file 
		file << content;
		file.close();
            return true;
    }


}