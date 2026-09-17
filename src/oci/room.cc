#include "room.hh"

namespace oci
{
    Room::Room(std::string i, std::uint8_t is)
        : id(i)
        , id_short(is)
    {}

    fs::path getRoomFilePath(fs::path data_folder_path,
        const std::string& room_id, RoomFileType file_type)
    {
        fs::path result = data_folder_path;
        result.append("_levels");
        result.append(room_id.substr(0, 1));
        result.append(room_id);

        std::string filename = room_id;
        switch (file_type)
        {
        case RoomFileType::HOE:
            filename = filename + ".hoe";
            break;
        default:
            throw std::invalid_argument("Invalid RoomFileType");
            break;
        }

        result.append(filename);
        return result;
    }

    Room a000("a000", 0x01);
    Room a001("a001", 0x02);
    Room a002("a002", 0x03);
    Room a003("a003", 0x04);
    Room a004("a004", 0x05);
    Room b000("b000", 0x11);
    Room b002("b002", 0x13);
    Room b004("b004", 0x15);
    Room b005("b005", 0x16);
    Room b006("b006", 0x17);
    Room b007("b007", 0x18);
    Room b008("b008", 0x19);
    Room b009("b009", 0x1A);
    Room b010("b010", 0x20);
    Room b100("b100", 0x1B);
    Room b102("b102", 0x1C);
    Room b103("b103", 0x1D);
    Room b104("b104", 0x1E);
    Room b106("b106", 0x1F);
    Room c000("c000", 0x31);
    Room c003("c003", 0x32);
    Room c004("c004", 0x33);
    Room c006("c006", 0x34);
    Room c009("c009", 0x35);
    Room c010("c010", 0x36);
    Room c011("c011", 0x37);
    Room c100("c100", 0x38);
    Room c101("c101", 0x39);
    Room c104("c104", 0x3A);
    Room c105("c105", 0x3B);
    Room c109("c109", 0x3C);
    Room d000("d000", 0x41);
    Room d001("d001", 0x40);
    Room d002("d002", 0x42);
    Room d003("d003", 0x43);
    Room d004("d004", 0x44);
    Room d005("d005", 0x45);
    Room d006("d006", 0x46);
    Room d009("d009", 0x47);
    Room d010("d010", 0x4F);
    Room d100("d100", 0x48);
    Room d101("d101", 0x49);
    Room d102("d102", 0x4A);
    Room d103("d103", 0x4B);
    Room d104("d104", 0x4C);
    Room d105("d105", 0x4D);
    Room d106("d106", 0x4E);
    Room e000("e000", 0x51);
    Room e001("e001", 0x52);
    Room e002("e002", 0x53);
    Room e003("e003", 0x54);
    Room e100("e100", 0x55);
    Room e101("e101", 0x56);
    Room e102("e102", 0x57);
    Room e103("e103", 0x58);
    Room f000("f000", 0x61);
    Room f001("f001", 0x62);
    Room f002("f002", 0x63);
    Room f003("f003", 0x64);
    Room f101("f101", 0x65);
    Room f102("f102", 0x66);
    Room g000("g000", 0x71);
    Room g001("g001", 0x72);
    Room g002("g002", 0x73);
    Room g003("g003", 0x74);
    Room g004("g004", 0x75);
    Room g005("g005", 0x76);
    Room g006("g006", 0x77);
    Room g007("g007", 0x78);
    Room g008("g008", 0x79);
    Room g009("g009", 0x7A);
    Room g010("g010", 0x7B);
    Room g012("g012", 0x7C);
    Room g013("g013", 0x7D);
    Room g014("g014", 0x85);
    Room g015("g015", 0x86);
    Room g016("g016", 0x87);
    Room g100("g100", 0x7E);
    Room g103("g103", 0x80);
    Room g104("g104", 0x81);
    Room g105("g105", 0x82);
    Room g106("g106", 0x83);
    Room g107("g107", 0x84);
    Room i000("i000", 0xA1);
    Room i001("i001", 0xA2);
    Room i002("i002", 0xA3);
    Room i004("i004", 0xA4);
    Room i007("i007", 0xA5);
    Room i100("i100", 0xA7);
    Room i101("i101", 0xA8);
    Room i102("i102", 0xA9);
    Room i103("i103", 0xAA);
    Room i107("i107", 0xAB);
    Room j000("j000", 0xB1);
    Room j001("j001", 0xB2);
    Room m000("m000", 0xC1);
    Room m001("m001", 0xC2);
    Room m002("m002", 0xC3);
    Room m003("m003", 0xC4);
    Room m100("m100", 0xC5);

    std::vector<Room> all_rooms;

    void initializeAllRooms()
    {
        all_rooms.push_back(a000);
        all_rooms.push_back(a001);
        all_rooms.push_back(a002);
        all_rooms.push_back(a003);
        all_rooms.push_back(a004);
        all_rooms.push_back(b000);
        all_rooms.push_back(b002);
        all_rooms.push_back(b004);
        all_rooms.push_back(b005);
        all_rooms.push_back(b006);
        all_rooms.push_back(b007);
        all_rooms.push_back(b008);
        all_rooms.push_back(b009);
        all_rooms.push_back(b010);
        all_rooms.push_back(b100);
        all_rooms.push_back(b102);
        all_rooms.push_back(b103);
        all_rooms.push_back(b104);
        all_rooms.push_back(b106);
        all_rooms.push_back(c000);
        all_rooms.push_back(c003);
        all_rooms.push_back(c004);
        all_rooms.push_back(c006);
        all_rooms.push_back(c009);
        all_rooms.push_back(c010);
        all_rooms.push_back(c011);
        all_rooms.push_back(c100);
        all_rooms.push_back(c101);
        all_rooms.push_back(c104);
        all_rooms.push_back(c105);
        all_rooms.push_back(c109);
        all_rooms.push_back(d000);
        all_rooms.push_back(d001);
        all_rooms.push_back(d002);
        all_rooms.push_back(d003);
        all_rooms.push_back(d004);
        all_rooms.push_back(d005);
        all_rooms.push_back(d006);
        all_rooms.push_back(d009);
        all_rooms.push_back(d010);
        all_rooms.push_back(d100);
        all_rooms.push_back(d101);
        all_rooms.push_back(d102);
        all_rooms.push_back(d103);
        all_rooms.push_back(d104);
        all_rooms.push_back(d105);
        all_rooms.push_back(d106);
        all_rooms.push_back(e000);
        all_rooms.push_back(e001);
        all_rooms.push_back(e002);
        all_rooms.push_back(e003);
        all_rooms.push_back(e100);
        all_rooms.push_back(e101);
        all_rooms.push_back(e102);
        all_rooms.push_back(e103);
        all_rooms.push_back(f000);
        all_rooms.push_back(f001);
        all_rooms.push_back(f002);
        all_rooms.push_back(f003);
        all_rooms.push_back(f101);
        all_rooms.push_back(f102);
        all_rooms.push_back(g000);
        all_rooms.push_back(g001);
        all_rooms.push_back(g002);
        all_rooms.push_back(g003);
        all_rooms.push_back(g004);
        all_rooms.push_back(g005);
        all_rooms.push_back(g006);
        all_rooms.push_back(g007);
        all_rooms.push_back(g008);
        all_rooms.push_back(g009);
        all_rooms.push_back(g010);
        all_rooms.push_back(g012);
        all_rooms.push_back(g013);
        all_rooms.push_back(g014);
        all_rooms.push_back(g015);
        all_rooms.push_back(g016);
        all_rooms.push_back(g100);
        all_rooms.push_back(g103);
        all_rooms.push_back(g104);
        all_rooms.push_back(g105);
        all_rooms.push_back(g106);
        all_rooms.push_back(g107);
        all_rooms.push_back(i000);
        all_rooms.push_back(i001);
        all_rooms.push_back(i002);
        all_rooms.push_back(i004);
        all_rooms.push_back(i007);
        all_rooms.push_back(i100);
        all_rooms.push_back(i101);
        all_rooms.push_back(i102);
        all_rooms.push_back(i103);
        all_rooms.push_back(i107);
        all_rooms.push_back(j000);
        all_rooms.push_back(j001);
        all_rooms.push_back(m000);
        all_rooms.push_back(m001);
        all_rooms.push_back(m002);
        all_rooms.push_back(m003);
        all_rooms.push_back(m100);
    }
} // namespace oci