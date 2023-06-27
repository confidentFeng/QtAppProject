#pragma once

#include <QtCore/qstring.h>
#include <QtCore/qobject.h>
#include <QtCore/qfile.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qvector.h>
#include <QtCore/qthread.h>

class FileCopyer : public QObject {
    Q_OBJECT
        Q_PROPERTY(qint64 chunksize READ chunkSize WRITE setChunkSize)
        Q_PROPERTY(QVector<QString> sourcePaths READ sourcePaths WRITE setSourcePaths)
        Q_PROPERTY(QVector<QString> destinationPaths READ destinationPaths WRITE setDestinationPaths)

public:
    static const int DEFAULT_CHUNK_SIZE = 1024 * 1024 * 1;

    FileCopyer(QThread*);
    ~FileCopyer();

    qint64 chunkSize() const {
        return _chunk;
    }
    void setChunkSize(qint64 ch) {
        _chunk = ch;
    }

    QVector<QString> sourcePaths() const {
        return src;
    }
    void setSourcePaths(const QVector<QString>& _src) {
        src = _src;
    }

    QVector<QString> destinationPaths() const {
        return dst;
    }
    void setDestinationPaths(const QVector<QString>& _dst) {
        dst = _dst;
    }

    void interrupt()
    {
        _interrupt = true;
    }

    protected slots:
    void copy();



private:
    QVector<QString> src, dst;
    qint64 _chunk;
    bool _interrupt;

signals:
    void copyProgress(qint64 bytesCopied, qint64 bytesTotal);
    void finished(bool success);
    void oneBegin(QString srcFileName);
    void oneFinished(QString dstPath, bool result);
};
