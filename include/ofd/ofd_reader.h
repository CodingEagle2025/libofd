// Copyright (C) 2025, CodingEagle2025
// SPDX-FileCopyrightText: 2025 
//
// SPDX-License-Identifier: MIT

#ifndef OFD_READER_H
#define OFD_READER_H

#include <QString>
#include <QVector>
#include <QImage>

namespace ofd {

class Reader
{
public:
    Reader();
    ~Reader();

    // Read OFD file and extract images
    bool readFile(const QString &path, QVector<QImage> &images);

private:
    bool uncompressFile(const QString &path, const QString &extractPath);
    bool extractImages(const QString &path, QVector<QImage> &images);
    bool removeDir(const QString &dirPath);
};

}   // namespace ofd

#endif   // OFD_READER_H
