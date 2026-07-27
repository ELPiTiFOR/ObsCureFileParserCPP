#pragma once

#include <cstdint>
#include <string>
#include <vector>

#define NB_ITEM_UIDS 249

namespace oci
{
    struct Item
    {
        Item(std::uint16_t t, std::uint8_t s, const std::string& n);
        std::uint16_t type;
        std::uint8_t type_short;
        std::string name;
        static const Item& searchItemType(std::uint16_t t);
        // static const Item& searchItemTypeShort(std::uint8_t s);
        // static const Item& searchItemName(const std::string& n);
    };

    extern std::vector<Item> all_items;
    void initializeAllItems();

    enum class ItemUid
    {
        A000_DOUBLE_BARREL_SHOTGUN          = 0x00010001,
        A000_SHOTGUN_AMMO                   = 0x00010002,
        A000_HANDGUN_AMMO                   = 0x00010003,
        A001_HANDGUN_AMMO1                  = 0x00010081,
        A001_MEDKIT                         = 0x00010082,
        A001_HANDGUN_AMMO3                  = 0x00010083,
        A002_STATUETTE                      = 0x00010101,
        A002_DISC                           = 0x00010102,
        A002_MEDKIT                         = 0x00010103,
        A003_MEDKIT                         = 0x00010181,
        A003_ENERGY_DRINK2                  = 0x00010182,
        A003_ENERGY_DRINK3                  = 0x00010183,
        A003_SHOTGUN_AMMO                   = 0x00010184,
        A003_LEVER                          = 0x00010185,
        A004_OLD_PISTOL                     = 0x00010201,       // DO NOT CHANGE
        A004_TAPE                           = 0x00010203,       // DO NOT CHANGE
        A004_WEAK_FLASHLIGHT                = 0x00010202,       // DO NOT CHANGE
        A004_HANDGUN_AMMO                   = 0x00010205,
        A004_DISC                           = 0x00010204,
        B000_MAP1                           = 0x00020001,
        B000_SHOTGUN_AMMOF                  = 0x0002000F,
        B002_TAPE                           = 0x00020132,
        B004_KEY                            = 0x00020201,
        B005_DISC                           = 0x00020281,
        B006_ENERGY_DRINK                   = 0x00020301,
        B007_ENERGY_DRINK                   = 0x00020381,
        B008_DISC                           = 0x00020401,
        B008_BAT                            = 0x00020402,       // DO NOT CHANGE
        B008_ENERGY_DRINK                   = 0x00020403,
        B009_MEDKIT                         = 0x00020481,
        B010_REEL_OF_WIRE                   = 0x00020501,       // DO NOT CHANGE
        B100_METAL_BAR                      = 0x00023201,
        B100_ENERGY_DRINK                   = 0x00023202,
        B102_SCREWDRIVER                    = 0x00023301,       // DO NOT CHANGE
        B103_DOCUMENT3                      = 0x000233B3,
        B103_DISC2                          = 0x00023382,
        B104_SHOTGUN_AMMO2                  = 0x00023402,
        B104_DISC3                          = 0x00023403,
        B104_HANDGUN_AMMO4                  = 0x00023404,
        B104_PHOTO5                         = 0x00023405,
        B104_FILM2                          = 0x00063302,
        B106_KEY2                           = 0x00023502,       // DO NOT CHANGE (amphi)
        B106_KEY1                           = 0x00023501,       // DO NOT CHANGE
        B106_DISC3                          = 0x00023503,
        C000_ALUMINIUM_BAT2                 = 0x00030002,
        C000_MAP1                           = 0x00030001,
        C000_ENERGY_DRINK3                  = 0x00030003,
        C000_ENERGY_DRINK4                  = 0x00030004,
        C003_MEDKIT1                        = 0x00030181,
        C004_WEAK_FLASHLIGHT                = 0x00030202,
        C004_OLD_PISTOL                     = 0x00030203,
        C004_HANDGUN_AMMO                   = 0x00030204,
        C006_DISC1                          = 0x00030301,
        C006_DOCUMENT2                      = 0x00030302,
        C009_NEEDLE                         = 0x00030482,       // DO NOT CHANGE
        C010_DOCUMENT2                      = 0x00030502,
        C010_DISC3                          = 0x00030503,
        C011_TAPE1                          = 0x00030581,
        C100_WEAK_FLASHLIGHT1               = 0x00033201,
        C100_DISC2                          = 0x00033202,
        C100_ENERGY_DRINK3                  = 0x00033203,
        C100_OLD_PISTOL5                    = 0x00033205,
        C101_HANDGUN_AMMO1                  = 0x00033281,
        C104_HANDGUN_AMMO3                  = 0x00033433,
        C104_ENERGY_DRINK1                  = 0x00033401,
        C104_HANDGUN_AMMO2                  = 0x00033432,
        C105_DISC1                          = 0x00033481,
        C105_ENERGY_DRINK2                  = 0x00033482,
        C105_TAPE3                          = 0x00033483,
        C105_HANDGUN_AMMO4                  = 0x00033484,
        C109_KEY5                           = 0x00033685,
        C109_HANDGUN_AMMO2                  = 0x00033682,
        C109_PHOTO4                         = 0x00033684,
        C109_GUN_WITH_FLASHLIGHT1           = 0x00033681,
        C109_VIDEO_TAPE6                    = 0x00033686,
        C109_DOCUMENTA                      = 0x0003368A,
        C109_NEEDLE                         = 0x0003368C,       // DO NOT CHANGE
        C109_DISC3                          = 0x00033693,
        C109_LASER_GUN4                     = 0x00033694,
        C109_DOCUMENT8_D                    = 0x00033688,
        C109_DOCUMENT7_D                    = 0x00033687,
        D000_MAP1                           = 0x00040001,
        D000_DISC2                          = 0x00040002,
        D001_TAPE1                          = 0x00040081,
        D002_FILM2                          = 0x00040102,
        D002_POWERFUL_FLASHLIGHT3           = 0x00040103,
        D002_STATUETTE1                     = 0x00040101,
        D002_KEY4                           = 0x00040104,
        D003_DOCUMENT1                      = 0x00040181,
        D003_DOCUMENTA                      = 0x0004018A,
        D003_DISCB                          = 0x0004018B,
        D003_STATUETTE1                     = 0x00043501,
        D004_DISC1                          = 0x00040201,
        D005_HANDGUN_AMMO2                  = 0x00040282,
        D005_ENERGY_DRINK3                  = 0x00040283,
        D006_ENERGY_DRINK1                  = 0x00040301,
        D009_YELLOW_FLASHLIGHT2             = 0x00040482,
        D010_KEY1                           = 0x00040501,
        D010_PIECE_OF_PAPER3                = 0x00020183,
        D010_DOCUMENT2                      = 0x00040502,
        D100_DISC1                          = 0x00043201,
        D101_ENERGY_DRINK1                  = 0x00043281,
        D101_ENERGY_DRINK2                  = 0x00043282,
        D101_ENERGY_DRINK3                  = 0x00043283,
        D101_DISC4                          = 0x00043284,
        D102_REVOLVER1                      = 0x00043301,
        D102_SHOTGUN_AMMO2                  = 0x00043302,
        D102_SHOTGUN_AMMO3                  = 0x00043303,
        D103_TAPE1                          = 0x00043381,
        D103_LIGHT_GRENADE2                 = 0x00043382,
        D103_MEDKIT3                        = 0x00043383,
        D104_TAPE1                          = 0x00043401,
        D104_HANDGUN_AMMO2                  = 0x00043402,
        D104_HANDGUN_AMMO3                  = 0x00043403,
        D105_MEDKIT1                        = 0x00043481,
        D106_STATUETTE1                     = 0x00043501,
        D106_MEDKIT2                        = 0x00043502,
        E000_MAP2                           = 0x00050002,
        E000_HANDGUN_AMMO1                  = 0x00050001,
        E000_AUTOMATIC_PISTOL3              = 0x00050003,
        E001_HANDGUN_AMMO5                  = 0x00050085,
        E001_YELLOW_FLASHLIGHT3             = 0x00050083,
        E001_SHOTGUN1                       = 0x00050081,
        E001_SHOTGUN_AMMO4                  = 0x00050084,
        E001_HANDGUN_AMMO6                  = 0x00050086,
        E002_ENERGY_DRINK1                  = 0x00050101,
        E002_DISC2                          = 0x00050102,
        E003_VIDEO_TAPE1                    = 0x00050181,
        E003_KEY6                           = 0x00050186,
        E100_SHOTGUN_AMMO1                  = 0x00053201,
        E100_ENERGY_DRINK2                  = 0x00053202,
        E100_ENERGY_DRINK3                  = 0x00053203,
        E100_MEDKIT4                        = 0x00053204,
        E101_DISC2                          = 0x00053282,
        E101_MEDKIT1                        = 0x00053281,
        E101_ENERGY_DRINK3                  = 0x00053283,
        E101_AUTOMATIC_PISTOL4              = 0x00053284,
        E102_FUSES1                         = 0x00053301,
        E102_SHOTGUN_AMMO2                  = 0x00053302,
        E103_WHEEL1                         = 0x00053381,
        E103_DOCUMENT2                      = 0x00053382,
        E103_MEDKIT4                        = 0x00053384,
        E103_MEDKIT5                        = 0x00053385,
        E103_DISC3                          = 0x00053383,
        E103_MEDKIT6                        = 0x00053386,
        F000_MAP1                           = 0x00060001,
        F000_DISC2                          = 0x00060002,
        F000_TAPE3                          = 0x00060003,
        F001_SHOTGUN_AMMO1                  = 0x00060081,
        F001_DISC2                          = 0x00060082,
        F002_HANDGUN_AMMO1                  = 0x00060101,
        F002_MEDKIT2                        = 0x00060102,
        F003_WOOD_PLANK1                    = 0x00060181,
        F003_TAPE3                          = 0x00060183,
        F003_MEDKIT4                        = 0x00060184,
        F101_ENERGY_DRINK1                  = 0x00063281,
        F101_MEDKIT2                        = 0x00063282,
        F102_SHOTGUN_AMMO3                  = 0x00063303,
        F102_SHOTGUN_AMMO4                  = 0x00063304,
        G000_ENERGY_DRINK1                  = 0x00070001,
        G001_DOCUMENT1                      = 0x00070081,
        G001_MEDKIT3                        = 0x00070083,
        G001_DISC4                          = 0x00070084,
        G002_SHOTGUN1                       = 0x00070101,
        G002_LIGHT_GRENADE2                 = 0x00070102,
        G002_LEVER3                         = 0x00070103,
        G002_DOCUMENT4                      = 0x00070104,
        G003_LASER1                         = 0x00070181,
        G003_MEDKIT2                        = 0x00070182,
        G003_PHOTO3                         = 0x00070183,
        G004_PLIERS                         = 0x00070201,
        G004_HOOK                           = 0x00070202,       // DO NOT CHANGE
        G005_DISC1                          = 0x00070281,
        G005_ENERGY_DRINK2                  = 0x00070282,
        G005_TAPE3                          = 0x00070283,
        G006_SHOTGUN_AMMO1                  = 0x00070301,
        G006_SHOTGUN_AMMO2                  = 0x00070302,
        G007_MEDKIT1                        = 0x00070381,
        G007_ENERGY_DRINK2                  = 0x00070382,
        G008_MEDKIT2                        = 0x00070402,
        G008_SHOTGUN_AMMO7                  = 0x00070407,
        G008_MEDKIT3                        = 0x00070403,
        G008_DISC1                          = 0x00070401,
        G008_HANDGUN_AMMO6                  = 0x00070406,
        G008_HANDGUN_AMMO5                  = 0x00070405,
        G008_SHOTGUN_AMMO4                  = 0x00070404,
        G010_DISC3                          = 0x00070503,
        G010_HANDGUN_AMMO4                  = 0x00070504,
        G010_MEDKIT1                        = 0x00070501,
        G010_YELLOW_FLASHLIGHT2             = 0x00070502,
        G010_POWERFUL_FLASHLIGHT5           = 0x00070505,
        G010_HANDGUN_AMMO6                  = 0x00070506,
        G012_SHOTGUN_AMMO1                  = 0x00070601,
        G013_SHOTGUN_AMMO1                  = 0x00070681,
        G013_MEDKIT2                        = 0x00070682,
        G014_ENERGY_DRINK1                  = 0x00070701,
        G014_MEDKIT2                        = 0x00070702,
        G015_SHOTGUN_AMMO1                  = 0x00070781,
        G016_OLD_PISTOL                     = 0x00070801,       // DO NOT CHANGE
        G100_SHOTGUN_AMMO1                  = 0x00073201,
        G100_LIGHT_GRENADE2                 = 0x00073202,
        G100_SHOTGUN_AMMO3                  = 0x00073203,
        G103_MEDKIT1                        = 0x00073381,
        G103_LEVER2                         = 0x00073382,
        G104_DISC1                          = 0x00073401,
        G104_SHOTGUN_AMMO2                  = 0x00073402,
        G104_HANDGUN_AMMO3                  = 0x00073403,
        G105_MEDKIT1                        = 0x00073481,
        G105_SHOTGUN_AMMO2                  = 0x00073482,
        G106_HANDGUN_AMMO1                  = 0x00073501,
        G107_DISC1                          = 0x00073581,
        G107_SHOTGUN_AMMO2                  = 0x00073582,
        I000_MAP1                           = 0x00090001,
        I000_ENERGY_DRINK2                  = 0x00090002,
        I000_STATUETTE3                     = 0x00090003,
        I000_HANDGUN_AMMO4                  = 0x00090004,
        I000_SHOTGUN_AMMO5                  = 0x00090005,
        I001_KEY1                           = 0x00090081,
        I001_BASEMENT_PLAN2                 = 0x00090082,
        I001_DOCUMENT3                      = 0x00090083,
        I001_SHOTGUN_AMMO4                  = 0x00090084,
        I001_MEDKIT5                        = 0x00090085,
        I001_SHOTGUN_AMMO7                  = 0x00090087,
        I001_SHOTGUN_AMMO8                  = 0x00090088,
        I002_DISC1                          = 0x00090101,
        I002_DOCUMENT2                      = 0x00090102,
        I002_HANDGUN_AMMO3                  = 0x00090103,
        I004_MEDKIT1                        = 0x00090201,
        I004_ENERGY_DRINK2                  = 0x00090202,
        I007_HANDGUN_AMMO1                  = 0x00090381,
        I007_LIGHT_GRENADE2                 = 0x00090382,
        I100_SAFE1                          = 0x00093201,
        I100_DISC2                          = 0x00093202,
        I100_SHOTGUN_AMMO3                  = 0x00093203,
        I101_HANDGUN_AMMO2                  = 0x00093282,
        I101_ENERGY_DRINK4                  = 0x00093284,
        I101_ENERGY_DRINK3                  = 0x00093283,
        I102_DISC1                          = 0x00093301,
        I102_HANDGUN_AMMO2                  = 0x00093302,
        I103_SAFE1                          = 0x00093381,
        I103_DOCUMENT1                      = 0x00093281,
        I107_SHOTGUN_AMMO2                  = 0x00093582,
        I107_MEDKIT3                        = 0x00093583,
        J001_CELLPHONE                      = 0x000A0081,       // DO NOT CHANGE
        M000_DISC1                          = 0x000D0001,
        M001_MEDKIT1                        = 0x000D0081,
        M002_DISC1                          = 0x000D0101,
        M002_MEDKIT2                        = 0x000D0102,
        M100_DISC1                          = 0x000D3201,
    };

    extern std::vector<ItemUid> all_item_uids;
    void initializeAllItemUids();

    struct ExtraInfo
    {
        ExtraInfo(std::uint32_t i, const std::string& n);
        std::uint32_t id;
        std::string name;
        static const ExtraInfo& searchExtraInfoId(std::uint32_t i);
    };

    extern std::vector<ExtraInfo> all_extra_infos;
    void initializeAllExtraInfos();

    extern Item       weak_flashlight;
    extern Item                   bat;
    extern Item            old_pistol;
    extern Item                 laser;
    extern Item               shotgun;
    extern Item             metal_bar;
    extern Item         light_grenade;
    extern Item   gun_with_flashlight;
    extern Item     yellow_flashlight;
    extern Item   powerful_flashlight;
    extern Item      automatic_pistol;
    extern Item              revolver;
    extern Item double_barrel_shotgun;
    extern Item         aluminium_bat;
    extern Item             laser_gun;
    extern Item          shotgun_ammo;
    extern Item          handgun_ammo;
    extern Item             statuette;
    extern Item                  safe;
    extern Item                  hook;
    extern Item                 fuses;
    extern Item            wood_plank;
    extern Item                needle;
    extern Item           screwdriver;
    extern Item        piece_of_paper;
    extern Item                 lever;
    extern Item                  film;
    extern Item                 photo;
    extern Item              document;
    extern Item                   map;
    extern Item         basement_plan;
    extern Item                   key;
    extern Item                  disc;
    extern Item                  tape;
    extern Item                pliers;
    extern Item                 wheel;
    extern Item                medkit;
    extern Item             cellphone;
    extern Item            video_tape;
    extern Item          reel_of_wire;
    extern Item          energy_drink;

    extern ExtraInfo             no_document_id;
    extern ExtraInfo          statuette_praying;
    extern ExtraInfo           statuette_broken;
    extern ExtraInfo            statuette_cross;
    extern ExtraInfo       statuette_hands_back;
    extern ExtraInfo         piece_of_paper_doc;
    extern ExtraInfo         building_of_school;
    extern ExtraInfo              leonard_state;
    extern ExtraInfo  letter_from_walt_kerridan;
    extern ExtraInfo             the_mortifilia;
    extern ExtraInfo                 subject_22;
    extern ExtraInfo shom_transformation_photos;
    extern ExtraInfo         censored_newspaper;
    extern ExtraInfo            basement_photos;
    extern ExtraInfo            press_clippings;
    extern ExtraInfo              find_the_safe;
    extern ExtraInfo          types_of_mutation;
    extern ExtraInfo        letter_from_wickson;
    extern ExtraInfo          letter_to_wickson;
    extern ExtraInfo               beauty_club_;
    extern ExtraInfo     basketball_programmee_;
    extern ExtraInfo                photo_twins;
    extern ExtraInfo       expedition_documents;
    extern ExtraInfo          expedition_plaque;
    extern ExtraInfo                  necrology;
    extern ExtraInfo                 alan_diary;
    extern ExtraInfo        expulsion_community;
    extern ExtraInfo             administration;
    extern ExtraInfo                 classrooms;
    extern ExtraInfo                    library;
    extern ExtraInfo                  refectory;
    extern ExtraInfo               amphitheatre;
    extern ExtraInfo                  dormitory;

} // namespace oci