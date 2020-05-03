/***************************************************************************
 *   Copyright (C) 2019 by Stefan Kebekus                                  *
 *   stefan.kebekus@gmail.com                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "Library.h"

#include <QDir>
#include <QStandardPaths>
#include <QtGlobal>

Library::Library(QObject *parent) : QObject(parent)
{
}


QStringList Library::flightRoutes(const QString &filter)
{
    auto flightRouteLibraryDir = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/enroute flight navigation/flight routes");

    QStringList filterList;
    filterList << "*.geojson";

    auto fileNames = flightRouteLibraryDir.entryList(filterList);

    QStringList fileBaseNames;
    foreach(auto fileName, fileNames)
        fileBaseNames << fileName.section('.', 0, 0);

    return permissiveFilter(fileBaseNames, filter);
}


bool Library::flightRouteExists(const QString &baseName)
{
#warning duplicated info
    auto flightRouteLibraryDir = QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/enroute flight navigation/flight routes");

    return QFile::exists(flightRouteLibraryDir.path()+"/"+baseName+".geojson");
}


QStringList Library::permissiveFilter(const QStringList &inputStrings, const QString &filter)
{
    QString simplifiedFilter = simplifySpecialChars(filter);

    QStringList result;
    foreach(auto inputString, inputStrings)
        if (simplifySpecialChars(inputString).contains(simplifiedFilter, Qt::CaseInsensitive))
            result << inputString;

    return result;

}


QString Library::simplifySpecialChars(const QString &string)
{
    QString cacheString = simplifySpecialChars_cache[string];
    if (!cacheString.isEmpty())
        return cacheString;

    QString normalizedString = string.normalized(QString::NormalizationForm_KD);
    return normalizedString.remove(specialChars);
}
