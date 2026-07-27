#include "item.hh"

#include <stdexcept>

namespace oci
{
    Item::Item(std::uint16_t t, std::uint8_t s, const std::string& n)
        : type(t)
        , type_short(s)
        , name(n)
    {}

    const Item& Item::searchItemType(std::uint16_t t)
    {
        for (const Item& item : all_items)
        {
            if (item.type == t)
            {
                return item;
            }
        }
        
        throw std::invalid_argument("Invalid Item Type");
    }

    // const Item& Item::searchItemTypeShort(std::uint8_t s)
    // {}

    // const Item& Item::searchItemName(const std::string& n)
    // {}

    Item       weak_flashlight(0x00C9, 0x66, "WEAK_FLASHLIGHT");
    Item                   bat(0x00CA, 0x69, "BAT");
    Item            old_pistol(0x00CB, 0x6C, "OLD_PISTOL");
    Item                 laser(0x00CC, 0x70, "LASER");
    Item               shotgun(0x00CE, 0x71, "SHOTGUN");
    Item             metal_bar(0x00D1, 0x6A, "METAL_BAR");
    Item         light_grenade(0x00D2, 0x73, "LIGHT_GRENADE");
    Item   gun_with_flashlight(0x00D3, 0x74, "GUN_WITH_FLASHLIGHT");
    Item     yellow_flashlight(0x00D5, 0x67, "YELLOW_FLASHLIGHT");
    Item   powerful_flashlight(0x00D6, 0x68, "POWERFUL_FLASHLIGHT");
    Item      automatic_pistol(0x00D7, 0x6D, "AUTOMATIC_PISTOL");
    Item              revolver(0x00D8, 0x6E, "REVOLVER");
    Item double_barrel_shotgun(0x00D9, 0x72, "DOUBLE_BARREL_SHOTGUN");
    Item         aluminium_bat(0x00DA, 0x6B, "ALUMINIUM_BAT");
    Item             laser_gun(0x00DC, 0x6F, "LASER_GUN");
    Item          shotgun_ammo(0x0130, 0x7A, "SHOTGUN_AMMO");
    Item          handgun_ammo(0x0132, 0x7B, "HANDGUN_AMMO");
    Item             statuette(0x0191, 0x83, "STATUETTE");
    Item                  safe(0x0192, 0x84, "SAFE");
    Item                  hook(0x0194, 0x85, "HOOK");
    Item                 fuses(0x0195, 0x86, "FUSES");
    Item            wood_plank(0x0197, 0x87, "WOOD_PLANK");
    Item                needle(0x0199, 0x89, "NEEDLE");
    Item           screwdriver(0x019A, 0x8A, "SCREWDRIVER");
    Item        piece_of_paper(0x019B, 0x8B, "PIECE_OF_PAPER");
    Item                 lever(0x019C, 0x8C, "LEVER");
    Item                  film(0x01F5, 0x97, "FILM");
    Item                 photo(0x01F6, 0x98, "PHOTO");
    Item              document(0x01F7, 0x99, "DOCUMENT");
    Item                   map(0x01F8, 0x9A, "MAP");
    Item         basement_plan(0x01F9, 0x9B, "BASEMENT_PLAN");
    Item                   key(0x0259, 0xA1, "KEY");
    Item                  disc(0x025A, 0xA2, "DISC");
    Item                  tape(0x025B, 0xA3, "TAPE");
    Item                pliers(0x025C, 0xA4, "PLIERS");
    Item                 wheel(0x025E, 0xA5, "WHEEL");
    Item                medkit(0x025F, 0xA6, "MEDKIT");
    Item             cellphone(0x0260, 0xA7, "CELLPHONE");
    Item            video_tape(0x0261, 0xA8, "VIDEO_TAPE");
    Item          reel_of_wire(0x0263, 0xAA, "REEL_OF_WIRE");
    Item          energy_drink(0x0264, 0xAB, "ENERGY_DRINK");

    std::vector<Item> all_items;
    std::vector<ItemUid> all_item_uids;

    void initializeAllItems()
    {
        all_items.push_back(weak_flashlight);
        all_items.push_back(bat);
        all_items.push_back(old_pistol);
        all_items.push_back(laser);
        all_items.push_back(shotgun);
        all_items.push_back(metal_bar);
        all_items.push_back(light_grenade);
        all_items.push_back(gun_with_flashlight);
        all_items.push_back(yellow_flashlight);
        all_items.push_back(powerful_flashlight);
        all_items.push_back(automatic_pistol);
        all_items.push_back(revolver);
        all_items.push_back(double_barrel_shotgun);
        all_items.push_back(aluminium_bat);
        all_items.push_back(laser_gun);
        all_items.push_back(shotgun_ammo);
        all_items.push_back(handgun_ammo);
        all_items.push_back(statuette);
        all_items.push_back(safe);
        all_items.push_back(hook);
        all_items.push_back(fuses);
        all_items.push_back(wood_plank);
        all_items.push_back(needle);
        all_items.push_back(screwdriver);
        all_items.push_back(piece_of_paper);
        all_items.push_back(lever);
        all_items.push_back(film);
        all_items.push_back(photo);
        all_items.push_back(document);
        all_items.push_back(map);
        all_items.push_back(basement_plan);
        all_items.push_back(key);
        all_items.push_back(disc);
        all_items.push_back(tape);
        all_items.push_back(pliers);
        all_items.push_back(wheel);
        all_items.push_back(medkit);
        all_items.push_back(cellphone);
        all_items.push_back(video_tape);
        all_items.push_back(reel_of_wire);
        all_items.push_back(energy_drink);
    }

    void initializeAllItemUids()
    {
        all_item_uids.push_back(ItemUid::A000_DOUBLE_BARREL_SHOTGUN);
        all_item_uids.push_back(ItemUid::A000_SHOTGUN_AMMO);
        all_item_uids.push_back(ItemUid::A000_HANDGUN_AMMO);
        all_item_uids.push_back(ItemUid::A001_HANDGUN_AMMO1);
        all_item_uids.push_back(ItemUid::A001_MEDKIT);
        all_item_uids.push_back(ItemUid::A001_HANDGUN_AMMO3);
        all_item_uids.push_back(ItemUid::A002_STATUETTE);
        all_item_uids.push_back(ItemUid::A002_DISC);
        all_item_uids.push_back(ItemUid::A002_MEDKIT);
        all_item_uids.push_back(ItemUid::A003_MEDKIT);
        all_item_uids.push_back(ItemUid::A003_ENERGY_DRINK2);
        all_item_uids.push_back(ItemUid::A003_ENERGY_DRINK3);
        all_item_uids.push_back(ItemUid::A003_SHOTGUN_AMMO);
        all_item_uids.push_back(ItemUid::A003_LEVER);
        all_item_uids.push_back(ItemUid::A004_OLD_PISTOL);
        all_item_uids.push_back(ItemUid::A004_TAPE);
        all_item_uids.push_back(ItemUid::A004_WEAK_FLASHLIGHT);
        all_item_uids.push_back(ItemUid::A004_HANDGUN_AMMO);
        all_item_uids.push_back(ItemUid::A004_DISC);
        all_item_uids.push_back(ItemUid::B000_MAP1);
        all_item_uids.push_back(ItemUid::B000_SHOTGUN_AMMOF);
        all_item_uids.push_back(ItemUid::B002_TAPE);
        all_item_uids.push_back(ItemUid::B004_KEY);
        all_item_uids.push_back(ItemUid::B005_DISC);
        all_item_uids.push_back(ItemUid::B006_ENERGY_DRINK);
        all_item_uids.push_back(ItemUid::B007_ENERGY_DRINK);
        all_item_uids.push_back(ItemUid::B008_DISC);
        all_item_uids.push_back(ItemUid::B008_BAT);
        all_item_uids.push_back(ItemUid::B008_ENERGY_DRINK);
        all_item_uids.push_back(ItemUid::B009_MEDKIT);
        all_item_uids.push_back(ItemUid::B010_REEL_OF_WIRE);
        all_item_uids.push_back(ItemUid::B100_METAL_BAR);
        all_item_uids.push_back(ItemUid::B100_ENERGY_DRINK);
        all_item_uids.push_back(ItemUid::B102_SCREWDRIVER);
        all_item_uids.push_back(ItemUid::B103_DOCUMENT3);
        all_item_uids.push_back(ItemUid::B103_DISC2);
        all_item_uids.push_back(ItemUid::B104_SHOTGUN_AMMO2);
        all_item_uids.push_back(ItemUid::B104_DISC3);
        all_item_uids.push_back(ItemUid::B104_HANDGUN_AMMO4);
        all_item_uids.push_back(ItemUid::B104_PHOTO5);
        all_item_uids.push_back(ItemUid::B104_FILM2);
        all_item_uids.push_back(ItemUid::B106_KEY2);
        all_item_uids.push_back(ItemUid::B106_KEY1);
        all_item_uids.push_back(ItemUid::B106_DISC3);
        all_item_uids.push_back(ItemUid::C000_ALUMINIUM_BAT2);
        all_item_uids.push_back(ItemUid::C000_MAP1);
        all_item_uids.push_back(ItemUid::C000_ENERGY_DRINK3);
        all_item_uids.push_back(ItemUid::C000_ENERGY_DRINK4);
        all_item_uids.push_back(ItemUid::C003_MEDKIT1);
        all_item_uids.push_back(ItemUid::C004_WEAK_FLASHLIGHT);
        all_item_uids.push_back(ItemUid::C004_OLD_PISTOL);
        all_item_uids.push_back(ItemUid::C004_HANDGUN_AMMO);
        all_item_uids.push_back(ItemUid::C006_DISC1);
        all_item_uids.push_back(ItemUid::C006_DOCUMENT2);
        all_item_uids.push_back(ItemUid::C009_NEEDLE);
        all_item_uids.push_back(ItemUid::C010_DOCUMENT2);
        all_item_uids.push_back(ItemUid::C010_DISC3);
        all_item_uids.push_back(ItemUid::C011_TAPE1);
        all_item_uids.push_back(ItemUid::C100_WEAK_FLASHLIGHT1);
        all_item_uids.push_back(ItemUid::C100_DISC2);
        all_item_uids.push_back(ItemUid::C100_ENERGY_DRINK3);
        all_item_uids.push_back(ItemUid::C100_OLD_PISTOL5);
        all_item_uids.push_back(ItemUid::C101_HANDGUN_AMMO1);
        all_item_uids.push_back(ItemUid::C104_HANDGUN_AMMO3);
        all_item_uids.push_back(ItemUid::C104_ENERGY_DRINK1);
        all_item_uids.push_back(ItemUid::C104_HANDGUN_AMMO2);
        all_item_uids.push_back(ItemUid::C105_DISC1);
        all_item_uids.push_back(ItemUid::C105_ENERGY_DRINK2);
        all_item_uids.push_back(ItemUid::C105_TAPE3);
        all_item_uids.push_back(ItemUid::C105_HANDGUN_AMMO4);
        all_item_uids.push_back(ItemUid::C109_KEY5);
        all_item_uids.push_back(ItemUid::C109_HANDGUN_AMMO2);
        all_item_uids.push_back(ItemUid::C109_PHOTO4);
        all_item_uids.push_back(ItemUid::C109_GUN_WITH_FLASHLIGHT1);
        all_item_uids.push_back(ItemUid::C109_VIDEO_TAPE6);
        all_item_uids.push_back(ItemUid::C109_DOCUMENTA);
        all_item_uids.push_back(ItemUid::C109_NEEDLE);
        all_item_uids.push_back(ItemUid::C109_DISC3);
        all_item_uids.push_back(ItemUid::C109_LASER_GUN4);
        all_item_uids.push_back(ItemUid::C109_DOCUMENT8_D);
        all_item_uids.push_back(ItemUid::C109_DOCUMENT7_D);
        all_item_uids.push_back(ItemUid::D000_MAP1);
        all_item_uids.push_back(ItemUid::D000_DISC2);
        all_item_uids.push_back(ItemUid::D001_TAPE1);
        all_item_uids.push_back(ItemUid::D002_FILM2);
        all_item_uids.push_back(ItemUid::D002_POWERFUL_FLASHLIGHT3);
        all_item_uids.push_back(ItemUid::D002_STATUETTE1);
        all_item_uids.push_back(ItemUid::D002_KEY4);
        all_item_uids.push_back(ItemUid::D003_DOCUMENT1);
        all_item_uids.push_back(ItemUid::D003_DOCUMENTA);
        all_item_uids.push_back(ItemUid::D003_DISCB);
        all_item_uids.push_back(ItemUid::D003_STATUETTE1);
        all_item_uids.push_back(ItemUid::D004_DISC1);
        all_item_uids.push_back(ItemUid::D005_HANDGUN_AMMO2);
        all_item_uids.push_back(ItemUid::D005_ENERGY_DRINK3);
        all_item_uids.push_back(ItemUid::D006_ENERGY_DRINK1);
        all_item_uids.push_back(ItemUid::D009_YELLOW_FLASHLIGHT2);
        all_item_uids.push_back(ItemUid::D010_KEY1);
        all_item_uids.push_back(ItemUid::D010_PIECE_OF_PAPER3);
        all_item_uids.push_back(ItemUid::D010_DOCUMENT2);
        all_item_uids.push_back(ItemUid::D100_DISC1);
        all_item_uids.push_back(ItemUid::D101_ENERGY_DRINK1);
        all_item_uids.push_back(ItemUid::D101_ENERGY_DRINK2);
        all_item_uids.push_back(ItemUid::D101_ENERGY_DRINK3);
        all_item_uids.push_back(ItemUid::D101_DISC4);
        all_item_uids.push_back(ItemUid::D102_REVOLVER1);
        all_item_uids.push_back(ItemUid::D102_SHOTGUN_AMMO2);
        all_item_uids.push_back(ItemUid::D102_SHOTGUN_AMMO3);
        all_item_uids.push_back(ItemUid::D103_TAPE1);
        all_item_uids.push_back(ItemUid::D103_LIGHT_GRENADE2);
        all_item_uids.push_back(ItemUid::D103_MEDKIT3);
        all_item_uids.push_back(ItemUid::D104_TAPE1);
        all_item_uids.push_back(ItemUid::D104_HANDGUN_AMMO2);
        all_item_uids.push_back(ItemUid::D104_HANDGUN_AMMO3);
        all_item_uids.push_back(ItemUid::D105_MEDKIT1);
        all_item_uids.push_back(ItemUid::D106_STATUETTE1);
        all_item_uids.push_back(ItemUid::D106_MEDKIT2);
        all_item_uids.push_back(ItemUid::E000_MAP2);
        all_item_uids.push_back(ItemUid::E000_HANDGUN_AMMO1);
        all_item_uids.push_back(ItemUid::E000_AUTOMATIC_PISTOL3);
        all_item_uids.push_back(ItemUid::E001_HANDGUN_AMMO5);
        all_item_uids.push_back(ItemUid::E001_YELLOW_FLASHLIGHT3);
        all_item_uids.push_back(ItemUid::E001_SHOTGUN1);
        all_item_uids.push_back(ItemUid::E001_SHOTGUN_AMMO4);
        all_item_uids.push_back(ItemUid::E001_HANDGUN_AMMO6);
        all_item_uids.push_back(ItemUid::E002_ENERGY_DRINK1);
        all_item_uids.push_back(ItemUid::E002_DISC2);
        all_item_uids.push_back(ItemUid::E003_VIDEO_TAPE1);
        all_item_uids.push_back(ItemUid::E003_KEY6);
        all_item_uids.push_back(ItemUid::E100_SHOTGUN_AMMO1);
        all_item_uids.push_back(ItemUid::E100_ENERGY_DRINK2);
        all_item_uids.push_back(ItemUid::E100_ENERGY_DRINK3);
        all_item_uids.push_back(ItemUid::E100_MEDKIT4);
        all_item_uids.push_back(ItemUid::E101_DISC2);
        all_item_uids.push_back(ItemUid::E101_MEDKIT1);
        all_item_uids.push_back(ItemUid::E101_ENERGY_DRINK3);
        all_item_uids.push_back(ItemUid::E101_AUTOMATIC_PISTOL4);
        all_item_uids.push_back(ItemUid::E102_FUSES1);
        all_item_uids.push_back(ItemUid::E102_SHOTGUN_AMMO2);
        all_item_uids.push_back(ItemUid::E103_WHEEL1);
        all_item_uids.push_back(ItemUid::E103_DOCUMENT2);
        all_item_uids.push_back(ItemUid::E103_MEDKIT4);
        all_item_uids.push_back(ItemUid::E103_MEDKIT5);
        all_item_uids.push_back(ItemUid::E103_DISC3);
        all_item_uids.push_back(ItemUid::E103_MEDKIT6);
        all_item_uids.push_back(ItemUid::F000_MAP1);
        all_item_uids.push_back(ItemUid::F000_DISC2);
        all_item_uids.push_back(ItemUid::F000_TAPE3);
        all_item_uids.push_back(ItemUid::F001_SHOTGUN_AMMO1);
        all_item_uids.push_back(ItemUid::F001_DISC2);
        all_item_uids.push_back(ItemUid::F002_HANDGUN_AMMO1);
        all_item_uids.push_back(ItemUid::F002_MEDKIT2);
        all_item_uids.push_back(ItemUid::F003_WOOD_PLANK1);
        all_item_uids.push_back(ItemUid::F003_TAPE3);
        all_item_uids.push_back(ItemUid::F003_MEDKIT4);
        all_item_uids.push_back(ItemUid::F101_ENERGY_DRINK1);
        all_item_uids.push_back(ItemUid::F101_MEDKIT2);
        all_item_uids.push_back(ItemUid::F102_SHOTGUN_AMMO3);
        all_item_uids.push_back(ItemUid::F102_SHOTGUN_AMMO4);
        all_item_uids.push_back(ItemUid::G000_ENERGY_DRINK1);
        all_item_uids.push_back(ItemUid::G001_DOCUMENT1);
        all_item_uids.push_back(ItemUid::G001_MEDKIT3);
        all_item_uids.push_back(ItemUid::G001_DISC4);
        all_item_uids.push_back(ItemUid::G002_SHOTGUN1);
        all_item_uids.push_back(ItemUid::G002_LIGHT_GRENADE2);
        all_item_uids.push_back(ItemUid::G002_LEVER3);
        all_item_uids.push_back(ItemUid::G002_DOCUMENT4);
        all_item_uids.push_back(ItemUid::G003_LASER1);
        all_item_uids.push_back(ItemUid::G003_MEDKIT2);
        all_item_uids.push_back(ItemUid::G003_PHOTO3);
        all_item_uids.push_back(ItemUid::G004_PLIERS);
        all_item_uids.push_back(ItemUid::G004_HOOK);
        all_item_uids.push_back(ItemUid::G005_DISC1);
        all_item_uids.push_back(ItemUid::G005_ENERGY_DRINK2);
        all_item_uids.push_back(ItemUid::G005_TAPE3);
        all_item_uids.push_back(ItemUid::G006_SHOTGUN_AMMO1);
        all_item_uids.push_back(ItemUid::G006_SHOTGUN_AMMO2);
        all_item_uids.push_back(ItemUid::G007_MEDKIT1);
        all_item_uids.push_back(ItemUid::G007_ENERGY_DRINK2);
        all_item_uids.push_back(ItemUid::G008_MEDKIT2);
        all_item_uids.push_back(ItemUid::G008_SHOTGUN_AMMO7);
        all_item_uids.push_back(ItemUid::G008_MEDKIT3);
        all_item_uids.push_back(ItemUid::G008_DISC1);
        all_item_uids.push_back(ItemUid::G008_HANDGUN_AMMO6);
        all_item_uids.push_back(ItemUid::G008_HANDGUN_AMMO5);
        all_item_uids.push_back(ItemUid::G008_SHOTGUN_AMMO4);
        all_item_uids.push_back(ItemUid::G010_DISC3);
        all_item_uids.push_back(ItemUid::G010_HANDGUN_AMMO4);
        all_item_uids.push_back(ItemUid::G010_MEDKIT1);
        all_item_uids.push_back(ItemUid::G010_YELLOW_FLASHLIGHT2);
        all_item_uids.push_back(ItemUid::G010_POWERFUL_FLASHLIGHT5);
        all_item_uids.push_back(ItemUid::G010_HANDGUN_AMMO6);
        all_item_uids.push_back(ItemUid::G012_SHOTGUN_AMMO1);
        all_item_uids.push_back(ItemUid::G013_SHOTGUN_AMMO1);
        all_item_uids.push_back(ItemUid::G013_MEDKIT2);
        all_item_uids.push_back(ItemUid::G014_ENERGY_DRINK1);
        all_item_uids.push_back(ItemUid::G014_MEDKIT2);
        all_item_uids.push_back(ItemUid::G015_SHOTGUN_AMMO1);
        all_item_uids.push_back(ItemUid::G016_OLD_PISTOL);
        all_item_uids.push_back(ItemUid::G100_SHOTGUN_AMMO1);
        all_item_uids.push_back(ItemUid::G100_LIGHT_GRENADE2);
        all_item_uids.push_back(ItemUid::G100_SHOTGUN_AMMO3);
        all_item_uids.push_back(ItemUid::G103_MEDKIT1);
        all_item_uids.push_back(ItemUid::G103_LEVER2);
        all_item_uids.push_back(ItemUid::G104_DISC1);
        all_item_uids.push_back(ItemUid::G104_SHOTGUN_AMMO2);
        all_item_uids.push_back(ItemUid::G104_HANDGUN_AMMO3);
        all_item_uids.push_back(ItemUid::G105_MEDKIT1);
        all_item_uids.push_back(ItemUid::G105_SHOTGUN_AMMO2);
        all_item_uids.push_back(ItemUid::G106_HANDGUN_AMMO1);
        all_item_uids.push_back(ItemUid::G107_DISC1);
        all_item_uids.push_back(ItemUid::G107_SHOTGUN_AMMO2);
        all_item_uids.push_back(ItemUid::I000_MAP1);
        all_item_uids.push_back(ItemUid::I000_ENERGY_DRINK2);
        all_item_uids.push_back(ItemUid::I000_STATUETTE3);
        all_item_uids.push_back(ItemUid::I000_HANDGUN_AMMO4);
        all_item_uids.push_back(ItemUid::I000_SHOTGUN_AMMO5);
        all_item_uids.push_back(ItemUid::I001_KEY1);
        all_item_uids.push_back(ItemUid::I001_BASEMENT_PLAN2);
        all_item_uids.push_back(ItemUid::I001_DOCUMENT3);
        all_item_uids.push_back(ItemUid::I001_SHOTGUN_AMMO4);
        all_item_uids.push_back(ItemUid::I001_MEDKIT5);
        all_item_uids.push_back(ItemUid::I001_SHOTGUN_AMMO7);
        all_item_uids.push_back(ItemUid::I001_SHOTGUN_AMMO8);
        all_item_uids.push_back(ItemUid::I002_DISC1);
        all_item_uids.push_back(ItemUid::I002_DOCUMENT2);
        all_item_uids.push_back(ItemUid::I002_HANDGUN_AMMO3);
        all_item_uids.push_back(ItemUid::I004_MEDKIT1);
        all_item_uids.push_back(ItemUid::I004_ENERGY_DRINK2);
        all_item_uids.push_back(ItemUid::I007_HANDGUN_AMMO1);
        all_item_uids.push_back(ItemUid::I007_LIGHT_GRENADE2);
        all_item_uids.push_back(ItemUid::I100_SAFE1);
        all_item_uids.push_back(ItemUid::I100_DISC2);
        all_item_uids.push_back(ItemUid::I100_SHOTGUN_AMMO3);
        all_item_uids.push_back(ItemUid::I101_HANDGUN_AMMO2);
        all_item_uids.push_back(ItemUid::I101_ENERGY_DRINK4);
        all_item_uids.push_back(ItemUid::I101_ENERGY_DRINK3);
        all_item_uids.push_back(ItemUid::I102_DISC1);
        all_item_uids.push_back(ItemUid::I102_HANDGUN_AMMO2);
        all_item_uids.push_back(ItemUid::I103_SAFE1);
        all_item_uids.push_back(ItemUid::I103_DOCUMENT1);
        all_item_uids.push_back(ItemUid::I107_SHOTGUN_AMMO2);
        all_item_uids.push_back(ItemUid::I107_MEDKIT3);
        all_item_uids.push_back(ItemUid::J001_CELLPHONE);
        all_item_uids.push_back(ItemUid::M000_DISC1);
        all_item_uids.push_back(ItemUid::M001_MEDKIT1);
        all_item_uids.push_back(ItemUid::M002_DISC1);
        all_item_uids.push_back(ItemUid::M002_MEDKIT2);
        all_item_uids.push_back(ItemUid::M100_DISC1);
    }

    ExtraInfo::ExtraInfo(std::uint32_t i, const std::string& n)
        : id(i)
        , name(n)
    {}

    const ExtraInfo& ExtraInfo::searchExtraInfoId(std::uint32_t i)
    {
        for (const ExtraInfo& extra_info : all_extra_infos)
        {
            if (extra_info.id == i)
            {
                return extra_info;
            }
        }

        throw std::invalid_argument("Invalid ExtraInfo ID");
    }

    ExtraInfo             no_document_id(0x00000000, "NO_EXTRA_INFO");
    ExtraInfo          statuette_praying(0x00000001, "STATUETTE_PRAYING");
    ExtraInfo           statuette_broken(0x00000002, "STATUETTE_BROKEN");
    ExtraInfo            statuette_cross(0x00000003, "STATUETTE_CROSS");
    ExtraInfo       statuette_hands_back(0x00000004, "STATUETTE_HANDS_BACK");
    ExtraInfo         piece_of_paper_doc(0x00020601, "PIECE_OF_PAPER_DOC");
    ExtraInfo         building_of_school(0x00020800, "BUILDING_OF_SCHOOL");
    ExtraInfo              leonard_state(0x00020801, "LEONARD_STATE");
    ExtraInfo  letter_from_walt_kerridan(0x00020802, "LETTER_FROM_WALT_KERRIDAN");
    ExtraInfo             the_mortifilia(0x00020803, "THE_MORTIFILIA");
    ExtraInfo                 subject_22(0x00020804, "SUBJECT_22");
    ExtraInfo shom_transformation_photos(0x00020805, "SHOM_TRANSFORMATION_PHOTOS");
    ExtraInfo         censored_newspaper(0x00020806, "CENSORED_NEWSPAPER");
    ExtraInfo            basement_photos(0x00020807, "BASEMENT_PHOTOS");
    ExtraInfo            press_clippings(0x00020808, "PRESS_CLIPPINGS");
    ExtraInfo              find_the_safe(0x00020809, "FIND_THE_SAFE");
    ExtraInfo          types_of_mutation(0x00020810, "TYPES_OF_MUTATION");
    ExtraInfo        letter_from_wickson(0x00020811, "LETTER_FROM_WICKSON");
    ExtraInfo          letter_to_wickson(0x00020812, "LETTER_TO_WICKSON");
    ExtraInfo               beauty_club_(0x00020813, "BEAUTY_CLUB_");
    ExtraInfo     basketball_programmee_(0x00020814, "BASKETBALL_PROGRAMMEE_");
    ExtraInfo                photo_twins(0x00020817, "PHOTO_TWINS");
    ExtraInfo       expedition_documents(0x00020819, "EXPEDITION_DOCUMENTS");
    ExtraInfo          expedition_plaque(0x00020820, "EXPEDITION_PLAQUE");
    ExtraInfo                  necrology(0x00020821, "NECROLOGY");
    ExtraInfo                 alan_diary(0x00020834, "ALAN_DIARY");
    ExtraInfo        expulsion_community(0x00020836, "EXPULSION_COMMUNITY");
    ExtraInfo             administration('B', "ADMINISTRATION");
    ExtraInfo                 classrooms('C', "CLASSROOMS");
    ExtraInfo                    library('D', "LIBRARY");
    ExtraInfo                  refectory('E', "REFECTORY");
    ExtraInfo               amphitheatre('F', "AMPHITHEATRE");
    ExtraInfo                  dormitory('I', "DORMITORY");

    std::vector<ExtraInfo> all_extra_infos;
    void initializeAllExtraInfos()
    {
        all_extra_infos.push_back(no_document_id);
        all_extra_infos.push_back(statuette_praying);
        all_extra_infos.push_back(statuette_broken);
        all_extra_infos.push_back(statuette_cross);
        all_extra_infos.push_back(statuette_hands_back);
        all_extra_infos.push_back(piece_of_paper_doc);
        all_extra_infos.push_back(building_of_school);
        all_extra_infos.push_back(leonard_state);
        all_extra_infos.push_back(letter_from_walt_kerridan);
        all_extra_infos.push_back(the_mortifilia);
        all_extra_infos.push_back(subject_22);
        all_extra_infos.push_back(shom_transformation_photos);
        all_extra_infos.push_back(censored_newspaper);
        all_extra_infos.push_back(basement_photos);
        all_extra_infos.push_back(press_clippings);
        all_extra_infos.push_back(find_the_safe);
        all_extra_infos.push_back(types_of_mutation);
        all_extra_infos.push_back(letter_from_wickson);
        all_extra_infos.push_back(letter_to_wickson);
        all_extra_infos.push_back(beauty_club_);
        all_extra_infos.push_back(basketball_programmee_);
        all_extra_infos.push_back(photo_twins);
        all_extra_infos.push_back(expedition_documents);
        all_extra_infos.push_back(expedition_plaque);
        all_extra_infos.push_back(necrology);
        all_extra_infos.push_back(alan_diary);
        all_extra_infos.push_back(expulsion_community);
        all_extra_infos.push_back(administration);
        all_extra_infos.push_back(classrooms);
        all_extra_infos.push_back(library);
        all_extra_infos.push_back(refectory);
        all_extra_infos.push_back(amphitheatre);
        all_extra_infos.push_back(dormitory);
    }
}