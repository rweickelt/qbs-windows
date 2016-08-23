/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qbs.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms and
** conditions see http://www.qt.io/terms-conditions. For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "generatordata.h"
#include <tools/error.h>

#include <QDir>

namespace qbs {

QString GeneratableProductData::name() const
{
    QString name;
    QMapIterator<QString, ProductData> it(data);
    while (it.hasNext()) {
        it.next();
        QString oldName = name;
        name = it.value().name();
        if (!oldName.isEmpty() && oldName != name)
            throw ErrorInfo(QLatin1String("Products with different names per-configuration "
                                          "are not compatible with this generator. Consider "
                                          "using the targetName property instead."));
    }
    return name;
}

QStringList GeneratableProductData::dependencies() const
{
    QStringList list;
    QMapIterator<QString, ProductData> it(data);
    while (it.hasNext()) {
        it.next();
        QStringList oldList = list;
        list = it.value().dependencies();
        if (!oldList.isEmpty() && oldList != list)
            throw ErrorInfo(QLatin1String("Products with different dependency lists "
                                          "per-configuration are not compatible with this "
                                          "generator."));
    }
    return list;
}

QString GeneratableProjectData::name() const
{
    QString name;
    QMapIterator<QString, ProjectData> it(data);
    while (it.hasNext()) {
        it.next();
        QString oldName = name;
        name = it.value().name();
        if (!oldName.isEmpty() && oldName != name)
            throw ErrorInfo(QLatin1String("Projects with different names per-configuration "
                                          "are not compatible with this generator."));
    }
    return name;
}

QDir GeneratableProject::baseBuildDirectory() const
{
    QSet<QString> baseBuildDirectory;
    QMapIterator<QString, ProjectData> it(data);
    while (it.hasNext()) {
        it.next();
        QDir dir(it.value().buildDirectory());
        dir.cdUp();
        baseBuildDirectory.insert(dir.absolutePath());
    }
    Q_ASSERT(baseBuildDirectory.size() == 1);
    return baseBuildDirectory.values().first();
}

QFileInfo GeneratableProject::filePath() const
{
    QSet<QString> filePath;
    QMapIterator<QString, ProjectData> it(data);
    while (it.hasNext()) {
        it.next();
        filePath.insert(it.value().location().filePath());
    }
    Q_ASSERT(filePath.size() == 1);
    return filePath.values().first();
}

bool GeneratableProject::hasMultipleConfigurations() const
{
    return projects.size() > 1;
}

QStringList GeneratableProject::commandLine() const
{
    QStringList combinedCommandLine;
    QMapIterator<QString, QStringList> it(commandLines);
    while (it.hasNext()) {
        it.next();
        combinedCommandLine << it.value();
    }
    return combinedCommandLine;
}

} // namespace qbs