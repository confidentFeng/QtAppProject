#include "DataVM.h"
#include <QDir>
#include <QThread>
#include <QDateTime>
#include <QCryptographicHash>
#include "FileCopyer.h"


DataVM* DataVM::m_instance = nullptr;


DataVM::DataVM(QObject *parent /*= nullptr*/)
    : QObject(parent)
{


}

DataVM::~DataVM()
{

}

DataVM* DataVM::getInstance()
{
    if (m_instance == nullptr)
        m_instance = new DataVM();
	return m_instance;
}

void DataVM::copyFiles(QList<QUrl> filePaths, QString toFilePath)
{
    QVector<QString> srcFilePaths, dstFilePaths;
    for(auto &path : filePaths)
    {
        auto realPath = path.toString();
        srcFilePaths.push_back(realPath);
        QString fileName = QFileInfo(realPath).fileName();
        auto newFilePath = toFilePath + fileName;
        dstFilePaths.push_back(newFilePath);
    }
    auto local = new QThread;
    m_worker.reset(new FileCopyer(local));

    QObject::connect(m_worker.get(), &FileCopyer::finished, [&](bool s) {
        emit sigAllCopyFilesFinished();
    });

    QObject::connect(m_worker.get(), &FileCopyer::oneBegin, [&](QString fileName) {
        emit sigOneCopyFileBegin(fileName);
    });

    QObject::connect(m_worker.get(), &FileCopyer::oneFinished, [&](QString dstPath, bool result) {
        if(!result)
        {
            return;
        }
    });

    QObject::connect(m_worker.get(), &FileCopyer::copyProgress, [&](qint64 copy, qint64 total) {
        emit sigCopyFileProgress(qreal(copy) / qreal(total) );
    });

    m_worker.get()->setSourcePaths(srcFilePaths); // e.g: ~/content/example.mp4
    m_worker.get()->setDestinationPaths(dstFilePaths); // e.g /usr/local/example.mp4
    local->start();
}

void DataVM::interruptCopyFile()
{
    m_worker->interrupt();
}
