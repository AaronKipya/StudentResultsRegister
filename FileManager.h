
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "Student.h"
#include "DynamicArray.h"

class FileManager {
public:

    static bool loadStudents(
        const std::string& filename,
        DynamicArray<Student>& students
    ) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Cannot open " << filename << "\n";
            return false;
        }

        DynamicArray<Student> loaded;
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string idText, name, scoreText;

            if (!std::getline(ss, idText, '|') ||
                !std::getline(ss, name, '|') ||
                !std::getline(ss, scoreText)) {
                std::cerr << "Invalid record: " << line << "\n";
                return false;
            }

            try {
                std::size_t idPos = 0, scorePos = 0;
                int id = std::stoi(idText, &idPos);
                double score = std::stod(scoreText, &scorePos);

                if (idPos != idText.size() ||
                    scorePos != scoreText.size() ||
                    id <= 0 || name.empty() ||
                    score < 0 || score > 100) {
                    return false;
                }

                loaded.add({id, name, score});
            }
            catch (const std::exception&) {
                std::cerr << "Invalid record: " << line << "\n";
                return false;
            }
        }

        if (file.bad()) {
            std::cerr << "Error reading file.\n";
            return false;
        }

        students = loaded;
        return true;
    }

    static bool saveStudents(
        const std::string& filename,
        const DynamicArray<Student>& students
    ) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Cannot write to " << filename << "\n";
            return false;
        }

        file << std::fixed << std::setprecision(1);

        for (std::size_t i = 0; i < students.getSize(); ++i) {
            const Student& s = students.get(i);

            file << s.studentID << "|"
                 << s.name << "|"
                 << s.score << "\n";
        }

        file.close();
        return file.good();
    }
};

#endif
