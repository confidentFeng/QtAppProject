#include <QtCore/qdebug.h>
#include "FileCopyer.h"

FileCopyer::FileCopyer(QThread* _thread) :QObject(nullptr),
    _interrupt(false){
    moveToThread(_thread);
    setChunkSize(DEFAULT_CHUNK_SIZE);

    QObject::connect(_thread, &QThread::started, this, &FileCopyer::copy);
    QObject::connect(this, &FileCopyer::finished, _thread, &QThread::quit);
    //QObject::connect(this, &FileCopyer::finished, this, &FileCopyer::deleteLater);
    QObject::connect(_thread, &QThread::finished, _thread, &QThread::deleteLater);
}

FileCopyer::~FileCopyer() {

}

void FileCopyer::copy()
{
    if (src.isEmpty() || dst.isEmpty())
    {
        qWarning() << QStringLiteral("source or destination paths are empty!");
        emit finished(false);
        return;
    }

    if (src.count() != dst.count())
    {
        qWarning() << QStringLiteral("source or destination paths doesn't match!");
        emit finished(false);
        return;
    }

    qint64 total = 0, written = 0;
    for (const auto& f : src)
        total += QFileInfo(f).size();
    qInfo() << QStringLiteral("%1 bytes should be write in total").arg(total);

    int indx = 0;
    qInfo() << QStringLiteral("writing with chunk size of %1 byte").arg(chunkSize());
    while (indx < src.count())
    {
        const auto dstPath = dst.at(indx);

        QFile srcFile(src.at(indx));
        QFile dstFile(dstPath);
        if (QFile::exists(dstPath))
        {
            qInfo() << QStringLiteral("file %1 alreasy exists, overwriting...").arg(dstPath);
            QFile::remove(dstPath);
        }

        if (!srcFile.open(QFileDevice::ReadOnly))
        {
            qWarning() << QStringLiteral("failed to open %1 (error:%2)").arg(srcFile.fileName()).arg(srcFile.errorString());
            indx++;
            continue; // skip
        }

        if (!dstFile.open(QFileDevice::WriteOnly))
        {
            qWarning() << QStringLiteral("failed to open %1 (error:%2)").arg(dstFile.fileName()).arg(dstFile.errorString());
            indx++;
            continue; // skip
        }
        emit oneBegin(QFileInfo(srcFile).fileName());
        /* copy the content in portion of chunk size */
        qint64 fSize = srcFile.size();
        while (fSize) {
            if(_interrupt)
            {
                emit finished(true);
                return;
            }
            const auto data = srcFile.read(chunkSize());
            const auto _written = dstFile.write(data);
            if (data.size() == _written)
            {
                written += _written;
                fSize -= data.size();
                emit copyProgress(written, total);
            }
            else
            {
                emit oneFinished(dstPath, false);
                qWarning() << QStringLiteral("failed to write to %1 (error:%2)").arg(dstFile.fileName()).arg(dstFile.errorString());
                fSize = 0;
                break; // skip this operation
            }
        }

        srcFile.close();
        dstFile.close();
        emit oneFinished(dstPath, true);
        indx++;
        qDebug() << QThread::currentThreadId();
    }

    if (total == written)
    {
        qInfo() << QStringLiteral("progress finished, %1 bytes of %2 has been written").arg(written).arg(total);
        emit finished(true);
    }
    else
    {
        emit finished(false);
    }
}
