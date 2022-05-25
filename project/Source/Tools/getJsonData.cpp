/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** getJsonData
*/

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

#include "FileError.hpp"

nlohmann::json getJsonData(std::string const &filepath)
{
    nlohmann::json jsonData;
    std::ifstream confStream(filepath);

    if (!confStream.is_open())
        throw Error::FileError("file " + filepath + " failed to open");
    confStream >> jsonData;
    confStream.close();
    return jsonData;
}