#pragma once

//-------------------

namespace txu
{

namespace fl
{

//-------------------

typedef unsigned short sinfo_t;
typedef unsigned long  linfo_t;

//-------------------

struct OffsetTable
{
    sinfo_t major_version;
    sinfo_t minor_version;
    sinfo_t tables_count;
    sinfo_t search_range;
    sinfo_t entry_selector;
    sinfo_t range_shift;
};

//-------------------

struct TableDirectory
{
    char tag[4];
    linfo_t check_summ;
    linfo_t offset;
    linfo_t length;
};

//-------------------

struct NameTableHeader
{
    sinfo_t format_selector;
    sinfo_t name_records_count;
    sinfo_t storage_offset;
};

//-------------------

struct NameRecord
{
    sinfo_t platform_id;
    sinfo_t encoding_id;
    sinfo_t language_id;
    sinfo_t name_id;
    sinfo_t string_length;
    sinfo_t string_offset;
};

//-------------------

void sswap (sinfo_t& x);
void lswap (linfo_t& x);

template <typename Type>
void readobj (FILE* file, Type* obj);

bool get_fucking_font_name (const char* filename, char* buffer, size_t nMaxCount);

//-------------------

#define NAMEID_FONT 1

//-------------------

void sswap (sinfo_t& x)
{
    x = _byteswap_ushort (x);
}

void lswap (linfo_t& x)
{
    x = _byteswap_ulong (x);
}

//-------------------

template <typename Type>
void readobj (FILE* file, Type* obj)
{
    fread (obj, 1, sizeof (Type), file);
}

//-------------------

bool get_fucking_font_name (const char* filename, char* buffer, size_t nMaxCount)
{
    FILE* file = nullptr;
    errno_t err = fopen_s (&file, filename, "r");
    if (err || !file) return false;

    OffsetTable offset = {};
    readobj (file, &offset);

    sswap (offset.tables_count );
    sswap (offset.major_version);
    sswap (offset.minor_version);

    if (offset.major_version != 1 || offset.minor_version != 0) 
    {   
        fclose (file);
        return false;
    }

    TableDirectory  dir    = {};
    NameTableHeader header = {};
    
    bool found = false;
    for (size_t i = 0; i < offset.tables_count && !found; i++)
    {
        readobj (file, &dir);

        if (!strncmp (dir.tag, "name", 4))
        {
            lswap (dir.length);
            lswap (dir.offset);

            found = true;
        }
    }

    if (!found) 
    {
        fclose (file);
        return false;
    }
    found = false;

    fseek (file, dir.offset, SEEK_SET);
    readobj (file, &header);
    sswap (header.name_records_count);
    sswap (header.storage_offset    );

    NameRecord record = {};
    for (size_t i = 0; i < header.name_records_count && !found; i++)
    {
        readobj (file, &record);
        sswap (record.name_id);

        if (record.name_id == NAMEID_FONT)
        {
            sswap (record.string_length);
            sswap (record.string_offset);

            size_t max = std::min ((size_t) record.string_length, nMaxCount);

            fseek (file, dir.offset + header.storage_offset + record.string_offset, SEEK_SET);
            fread (buffer, 1, max, file);

            found = true;
        }
    }

    fclose (file);
    return found;
}

//-------------------

#undef NAMEID_FONT

//-------------------

}

}

//-------------------