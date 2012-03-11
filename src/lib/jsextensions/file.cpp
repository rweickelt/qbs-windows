/**************************************************************************
**
** This file is part of the Qt Build Suite
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (info@qt.nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file.
** Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**************************************************************************/

#include "file.h"

#include <tools/fileinfo.h>

#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtScript/QScriptEngine>

void File::init(QScriptValue &extensionObject, QScriptEngine *engine)
{
    QScriptValue fileObj = engine->newQObject(new File, QScriptEngine::ScriptOwnership);
    fileObj.setProperty("copy", engine->newFunction(File::js_copy));
    fileObj.setProperty("exists", engine->newFunction(File::js_exists));
    fileObj.setProperty("remove", engine->newFunction(File::js_remove));
    extensionObject.setProperty("File", fileObj);
}

QScriptValue File::js_copy(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(engine);
    if (context->argumentCount() < 2) {
        return context->throwError(QScriptContext::SyntaxError,
                                   tr("copy expects 2 arguments"));
    }

    const QString sourceFile = context->argument(0).toString();
    const QString targetFile = context->argument(1).toString();
    QString errorMessage;
    if (!qbs::copyFileRecursion(sourceFile, targetFile, &errorMessage))
        return context->throwError(errorMessage);
    return true;
}

QScriptValue File::js_exists(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(engine);
    if (context->argumentCount() < 1) {
        return context->throwError(QScriptContext::SyntaxError,
                                   tr("exist expects 1 argument"));
    }
    return qbs::FileInfo::exists(context->argument(0).toString());
}

QScriptValue File::js_remove(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(engine);
    if (context->argumentCount() < 1) {
        return context->throwError(QScriptContext::SyntaxError,
                                   tr("remove expects 1 argument"));
    }
    QString fileName = context->argument(0).toString();

    QString errorMessage;
    if (!qbs::removeFileRecursion(QFileInfo(fileName), &errorMessage))
        return context->throwError(errorMessage);
    return true;
}
