/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Build Suite.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/
#ifndef QBS_ARTIFACTCLEANER_H
#define QBS_ARTIFACTCLEANER_H

#include <QList>

#include "forward_decls.h"

namespace qbs {
class BuildOptions;

namespace Internal {

class ArtifactCleaner
{
public:
    void cleanup(const QList<BuildProductPtr> &products, bool removeAll,
                 const BuildOptions &buildOptions);

private:
    void removeEmptyDirectories(const QString &rootDir, const BuildOptions &options,
                                bool *isEmpty = 0);

    bool m_hasError;
};

} // namespace Internal
} // namespace qbs

#endif // QBS_ARTIFACTCLEANER_H
