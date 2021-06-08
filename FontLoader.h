#pragma once

//-------------------

namespace txu
{

namespace font_loader
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

#define NAMEID_COPIRYGHT_NOTICE         0
#define NAMEID_FONT_FAMILY_NAME         1
#define NAMEID_FONT_SUBFAMILY_NAME      2
#define NAMEID_UNIQUE_IDENTIFIER        3
#define NAMEID_FULL_FONT_NAME           4
#define NAMEID_VERSION                  5
#define NAMEID_POSTSCRIPT_NAME          6
#define NAMEID_TRADEMARK                7
#define NAMEID_MANUFACTURER             8
#define NAMEID_DESIGNER                 9
#define NAMEID_DESCRIPTION             10
#define NAMEID_URL_VENDOR              11
#define NAMEID_URL_DESIGNED            12
#define NAMEID_LICENSE_DESCRIPTION     13
#define NAMEID_LICENSE_INFORMATION_URL 14
#define NAMEID_RESERVED                15
#define NAMEID_PREFFERED_FAMILY        16
#define NAMEID_PREFFERED_SUBFAMILY     17
#define NAMEID_SAMPLE_TEXT             19
#define NAMEID_POSTSCRIPT_CID          20

//-------------------

#define PLATFORMID_APPLE_UNICODE 0
#define PLATFORMID_MACINTOSH     1
#define PLATFORMID_ISO           2
#define PLATFORMID_MICROSOFT     3
#define PLATFORMID_CUSTOM        4
#define PLATFORMID_ADOBE         5

//-------------------

const char* load_fucking_font_record_data_228 (const char* filename, int nameid, char* buffer, size_t nMaxCount);

sinfo_t& sswap (sinfo_t& x);
linfo_t& lswap (linfo_t& x);

//-------------------

const char* load_fucking_font_record_data_228 (const char* filename, int nameid, char* buffer, size_t nMaxCount)
{
    FILE* file = __txu_fopen (filename, "rb");
    if (!file)
        return "failed to open file";

    OffsetTable offset = {};
    freadobj (file, &offset);

    sswap (offset.tables_count );
    sswap (offset.major_version);
    sswap (offset.minor_version);

    if (offset.major_version != 1 || offset.minor_version != 0)
    {
        fclose (file);
        return "file is not a ttf";
    }

    TableDirectory  dir    = {};
    NameTableHeader header = {};

    bool found = false;
    for (size_t i = 0; i < offset.tables_count && !found; i++)
    {
        freadobj (file, &dir);

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
        return "failed to find name tag";
    }
    found = false;

    fseek (file, dir.offset, SEEK_SET);
    freadobj (file, &header);
    sswap (header.name_records_count);
    sswap (header.storage_offset    );

    if (header.name_records_count == 0)
        return "0 name records count, wtf????";

    NameRecord record = {};
    for (size_t i = 0; i < header.name_records_count && !found; i++)
    {
        freadobj (file, &record);
        sswap (record.name_id);

        if (record.name_id == nameid)
        {
            sswap (record.encoding_id  );
            sswap (record.platform_id  );
            sswap (record.language_id  );
            sswap (record.string_length);
            sswap (record.string_offset);

            if (record.string_length >= nMaxCount)
            {
                fclose (file);
                return "Buffer is too small";
            }

            fseek (file, dir.offset + header.storage_offset + record.string_offset, SEEK_SET);
            fread (buffer, 1, record.string_length, file);
            buffer[record.string_length] = '\0';

            found = true;
        }
    }

    fclose (file);
    return nullptr;
}

//-------------------

sinfo_t& sswap (sinfo_t& x)
{
    return x = __txu_byteswap_16 (x);
}

linfo_t& lswap (linfo_t& x)
{
    return x = __txu_byteswap_32 (x);
}

//-------------------

} // namespace font_loader

} // namespace txu

//-------------------
