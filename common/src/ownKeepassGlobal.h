/***************************************************************************
**
** Copyright (C) 2015 Marko Koschak (marko.koschak@tisno.de)
** All rights reserved.
**
** This file is part of ownKeepass.
**
** ownKeepass is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** ownKeepass is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with ownKeepass. If not, see <http://www.gnu.org/licenses/>.
**
***************************************************************************/

#ifndef OWNKEEPASSGLOBAL_H
#define OWNKEEPASSGLOBAL_H

#include <QObject>

namespace ownKeepassPublic {

class DatabaseAccessResult : public QObject
{
    Q_OBJECT

public:
    Q_ENUMS(eDatabaseAccessResult)

    enum eDatabaseAccessResult {
        RE_OK = 0,                                  // no error
        RE_DB_LOAD_ERROR,                           // error loading data from database
        RE_DB_SAVE_ERROR,                           // error saving data into database
        RE_DB_NOT_OPENED,                           // database is not opened
        RE_DB_OPEN,                                 // other database is currently open, close it first
        RE_DB_ALREADY_CLOSED,                       // database already closed, no harm
        RE_DB_CLOSE_FAILED,                         // database closing failed
        RE_DB_FILE_ERROR,                           // file path error for new database
        RE_DB_SETKEY_ERROR,                         // error setting key (consisting of password and/or keyfile
        RE_DB_SETPW_ERROR,                          // error setting password for database
        RE_DB_SETKEYFILE_ERROR,                     // error setting key file for database
        RE_DB_CREATE_BACKUPGROUP_ERROR,             // error creating backup group
        RE_PRECHECK_DB_PATH_ERROR,                  // database file does not exists on precheck
        RE_PRECHECK_KEY_FILE_PATH_ERROR,            // key file does not exists on precheck
        RE_PRECHECK_DB_PATH_CREATION_ERROR,         // path to database file could not be created

        RE_DB_READ_ONLY,                            // database file is read-only

        // Keepass 1 specific
        RE_ERR_QSTRING_TO_INT,                      // conversion of QString to int failed

        // Keepass 2 specific
        RE_ERR_QString_TO_UUID,                     // conversion of uuid to QString failed (for passing a reference to QML)

        RE_LAST
    };
};

class DatabaseItemType : public QObject
{
    Q_OBJECT

public:
    Q_ENUMS(eDatabaseItemType)

    enum eDatabaseItemType {
        UNKNOWN = 0,
        GROUP,
        ENTRY,
    };
};

class DatabaseType : public QObject
{
    Q_OBJECT

public:
    Q_ENUMS(eDatabaseType)

    // to be used as type in initDatabaseInterface()
    enum eDatabaseType {
        DB_TYPE_UNKNOWN = -1,
        DB_TYPE_KEEPASS_1 = 0,
        DB_TYPE_KEEPASS_2 = 1,
    };
};

class Language : public QObject
{
    Q_OBJECT

public:
    Q_ENUMS(eLanguage)

    enum eLanguage {
        SYSTEM_DEFAULT = 0,
        EN,    // English
        SV_SE, // Swedish
        FI_FI, // Finnish
        DE_DE, // German
        CS_CZ, // Czech
        CA,    // Catalan
        NL_NL, // Dutch
        ES,    // Spanish
        FR_FR, // French
        IT,    // Italian
        RU,    // Russian
        DA,    // Danish
        PL_PL, // Polish - not yet started
        ZH_CN, // Chinese
        UK_UA, // Ukrainian - not yet started
        NB_NO, // Norwegian Bogmål
        INVALID
    };
};

}
#endif // OWNKEEPASSGLOBAL_H
