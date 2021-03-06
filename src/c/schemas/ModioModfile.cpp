#include "c/schemas/ModioModfile.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload
#include "c/schemas/ModioFilehash.h" // for modioInitFilehash ...
#include "c/schemas/ModioDownload.h" // for modioInitDownload ...

extern "C"
{
  void modioInitModfile(ModioModfile* modfile, nlohmann::json modfile_json)
  {
    modfile->id = 0;
    if(modio::hasKey(modfile_json, "id"))
      modfile->id = modfile_json["id"];

    modfile->mod_id = 0;
    if(modio::hasKey(modfile_json, "mod_id"))
      modfile->mod_id = modfile_json["mod_id"];

    modfile->virus_status = 0;
    if(modio::hasKey(modfile_json, "virus_status"))
      modfile->virus_status = modfile_json["virus_status"];

    modfile->virus_positive = 0;
    if(modio::hasKey(modfile_json, "virus_positive"))
      modfile->virus_positive = modfile_json["virus_positive"];

    modfile->date_added = 0;
    if(modio::hasKey(modfile_json, "date_added"))
      modfile->date_added = modfile_json["date_added"];

    modfile->date_scanned = 0;
    if(modio::hasKey(modfile_json, "date_scanned"))
      modfile->date_scanned = modfile_json["date_scanned"];

    modfile->filesize = 0;
    if(modio::hasKey(modfile_json, "filesize"))
      modfile->filesize = modfile_json["filesize"];

    modfile->filename = NULL;
    if(modio::hasKey(modfile_json, "filename"))
    {
      std::string filename_str = modfile_json["filename"];
      modfile->filename = new char[filename_str.size() + 1];
      strcpy(modfile->filename, filename_str.c_str());
    }

    modfile->version = NULL;
    if(modio::hasKey(modfile_json, "version"))
    {
      std::string version_str = modfile_json["version"];
      modfile->version = new char[version_str.size() + 1];
      strcpy(modfile->version, version_str.c_str());
    }

    modfile->virustotal_hash = NULL;
    if(modio::hasKey(modfile_json, "virustotal_hash"))
    {
      std::string virustotal_hash_str = modfile_json["virustotal_hash"];
      modfile->virustotal_hash = new char[virustotal_hash_str.size() + 1];
      strcpy(modfile->virustotal_hash, virustotal_hash_str.c_str());
    }

    modfile->changelog = NULL;
    if(modio::hasKey(modfile_json, "changelog"))
    {
      std::string changelog_str = modfile_json["changelog"];
      modfile->changelog = new char[changelog_str.size() + 1];
      strcpy(modfile->changelog, changelog_str.c_str());
    }

    modfile->metadata_blob = NULL;
    if(modio::hasKey(modfile_json, "metadata_blob"))
    {
      std::string metadata_blob_str = modfile_json["metadata_blob"];
      modfile->metadata_blob = new char[metadata_blob_str.size() + 1];
      strcpy(modfile->metadata_blob, metadata_blob_str.c_str());
    }

    nlohmann::json filehash_json;
    if(modio::hasKey(modfile_json, "filehash"))
      filehash_json = modfile_json["filehash"];
    modioInitFilehash(&(modfile->filehash), filehash_json);

    nlohmann::json download_json;
    if(modio::hasKey(modfile_json, "download"))
      download_json = modfile_json["download"];
    modioInitDownload(&(modfile->download), download_json);
  }

  void modioInitModfileCpp(ModioModfile* modio_modfile, modio::Modfile* modfile)
  {
    modio_modfile->id = modfile->id;
    modio_modfile->mod_id = modfile->mod_id;
    modio_modfile->virus_status = modfile->virus_status;
    modio_modfile->virus_positive = modfile->virus_positive;
    modio_modfile->date_added = modfile->date_added;
    modio_modfile->date_scanned = modfile->date_scanned;
    modio_modfile->filesize = modfile->filesize;

    modio_modfile->filename = new char[modfile->filename.size() + 1];
    strcpy(modio_modfile->filename, modfile->filename.c_str());

    modio_modfile->version = new char[modfile->version.size() + 1];
    strcpy(modio_modfile->version, modfile->version.c_str());

    modio_modfile->virustotal_hash = new char[modfile->virustotal_hash.size() + 1];
    strcpy(modio_modfile->virustotal_hash, modfile->virustotal_hash.c_str());

    modio_modfile->changelog = new char[modfile->changelog.size() + 1];
    strcpy(modio_modfile->changelog, modfile->changelog.c_str());

    modio_modfile->metadata_blob = new char[modfile->metadata_blob.size() + 1];
    strcpy(modio_modfile->metadata_blob, modfile->metadata_blob.c_str());

    modioInitFilehashCpp(&(modio_modfile->filehash), &(modfile->filehash));
    modioInitDownloadCpp(&(modio_modfile->download), &(modfile->download));
  }

  void modioFreeModfile(ModioModfile* modfile)
  {
    if(modfile)
    {
      if(modfile->filename)
        delete[] modfile->filename;
      if(modfile->version)
        delete[] modfile->version;
      if(modfile->virustotal_hash)
        delete[] modfile->virustotal_hash;
      if(modfile->changelog)
        delete[] modfile->changelog;
      if(modfile->metadata_blob)
        delete[] modfile->metadata_blob;

      modioFreeFilehash(&(modfile->filehash));
      modioFreeDownload(&(modfile->download));
    }
  }
}
