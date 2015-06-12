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
** along with ownKeepass.  If not, see <http://www.gnu.org/licenses/>.
**
***************************************************************************/

#ifndef KEEPASS2DATABASEINTERFACE_H
#define KEEPASS2DATABASEINTERFACE_H

#include <QObject>
#include "AbstractDatabaseInterface.h"
#include "../KdbDatabase.h"
#include "../KdbListModel.h"
#include "core/Database.h"

using namespace kpxPublic;

namespace kpxPrivate {

class Keepass2DatabaseInterface : public QObject, public AbstractDatabaseInterface
{
    Q_OBJECT
    Q_INTERFACES(AbstractDatabaseInterface)

public:
    explicit Keepass2DatabaseInterface(QObject* parent = 0);
    virtual ~Keepass2DatabaseInterface();

signals:
    // signals to all objects
    void disconnectAllClients();

    // signals to KdbDatabase object
    void databaseOpened();
    void newDatabaseCreated();
    void databaseClosed();
    void passwordChanged();
    void databaseKeyTransfRoundsChanged(int value);
    void databaseCryptAlgorithmChanged(int value);
    void errorOccured(int result,
                      QString errorMsg);

    // signals to KdbListModel object
    void appendItemToListModel(QString title,
                               QString subtitle,
                               int itemId,
                               int itemType,
                               int itemLevel,
                               int modelId);
    void addItemToListModelSorted(QString title,
                                  QString subtitle,
                                  int itemId,
                                  int itemType,
                                  int itemLevel,
                                  int modelId);
    void updateItemInListModel(QString title,
                               QString subTitle,
                               int itemId,
                               int modelId);
    void updateItemInListModelSorted(QString title,
                                     QString subTitle,
                                     int itemId,
                                     int modelId);
    void masterGroupsLoaded(int result);
    void groupsAndEntriesLoaded(int result);
    void deleteItemInListModel(int itemId);
    void searchEntriesCompleted(int result);

    // signal to KdbEntry object
    void entryLoaded(int result,
                     int entryId,
                     QString title,
                     QString url,
                     QString username,
                     QString password,
                     QString comment,
                     QString binaryDesc,
                     QString creation,
                     QString lastMod,
                     QString lastAccess,
                     QString expire,
                     quint32 binarySize,
                     QString friendlySize
                     );
    void entrySaved(int result,
                    int entryId);
    void newEntryCreated(int result,
                         int entryId);
    void entryDeleted(int result,
                      int entryId);
    void entryMoved(int result,
                    int entryId);

    // signal to KdbGroup object
    void groupLoaded(int result,
                     int groupId,
                     QString title);
    void groupSaved(int result,
                    int groupId);
    void newGroupCreated(int result,
                         int groupId);
    void groupDeleted(int result,
                      int groupId);
    void groupMoved(int result,
                    int groupId);


public slots:
    // signals from KdbDatabase object
    void slot_openDatabase(QString filePath,
                           QString password,
                           QString keyfile,
                           bool readonly);
    void slot_createNewDatabase(QString filePath,
                                QString password,
                                QString keyfile,
                                int cryptAlgorithm,
                                int keyTransfRounds);
    void slot_closeDatabase();
    void slot_changePassKey(QString password,
                            QString keyFile);
    void slot_changeKeyTransfRounds(int value);
    void slot_changeCryptAlgorithm(int value);
    void slot_setting_showUserNamePasswordsInListView(bool value) { m_setting_showUserNamePasswordsInListView = value; }
    void slot_setting_sortAlphabeticallyInListView(bool value) { m_setting_sortAlphabeticallyInListView = value; }

    // signal from KdbListModel object
    void slot_loadMasterGroups(bool registerListModel);
    void slot_loadGroupsAndEntries(int groupId);
    void slot_unregisterListModel(int modelId);
    void slot_searchEntries(QString searchString,
                            int rootGroupId);

    // signal from KdbEntry object
    void slot_loadEntry(int entryId);
    void slot_saveEntry(int entryId,
                        QString title,
                        QString url,
                        QString username,
                        QString password,
                        QString comment);
    void slot_createNewEntry(QString title,
                             QString url,
                             QString username,
                             QString password,
                             QString comment,
                             int parentGroupId);
    void slot_deleteEntry(int entryId);
    void slot_moveEntry(int entryId,
                        int newGroupId);

    // signal from KdbGroup object
    void slot_loadGroup(int groupId);
    void slot_saveGroup(int groupId,
                        QString title);
    void slot_createNewGroup(QString title,
                             quint32 iconId,
                             int parentGroupId);
    void slot_deleteGroup(int groupId);
    void slot_moveGroup(int groupId,
                        int newParentGroupId);

private:
    void initDatabase();
//    void updateGrandParentGroupInListModel(IGroupHandle* parentGroup);
//    inline QString getUserAndPassword(IEntryHandle* entry);

private:
    // Keepass database handler
    Database* m_Database;

    // settings
    bool m_setting_showUserNamePasswordsInListView;
    bool m_setting_sortAlphabeticallyInListView;

    // The following two hash tables store information about which list models are showing a dedicated entry or group in the UI
    QHash<int, int> m_entries_modelId;
    QHash<int, int> m_groups_modelId;
    int m_rootGroupId;
};

}
#endif // KEEPASS2DATABASEINTERFACE_H