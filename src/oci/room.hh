#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace oci
{
    struct Room
    {
        Room(std::string i, std::uint8_t is);
        std::string id;
        std::uint8_t id_short;
    };

    enum class RoomFileType
    {
        HOE,
    };

    extern std::vector<Room> all_rooms;
    void initializeAllRooms();

    fs::path getRoomFilePath(fs::path data_folder_path,
        const std::string& room_id, RoomFileType file_type);
} // namespace oci