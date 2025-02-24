// Copyright (C) 2025, CodingEagle2025
// SPDX-FileCopyrightText: 2025 
//
// SPDX-License-Identifier: MIT

#include <ofd/ofd_reader.h>
#include <ofd/ofd_writer.h>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create test image
    QImage testImage(800, 600, QImage::Format_RGB32);
    testImage.fill(Qt::red);
    
    // Create vector of images
    QVector<QImage> images;   
    images.append(testImage);

    // Write OFD file
    ofd::Writer writer;
    if (!writer.createFromImages("test.ofd", images,20,20)) {
        qWarning() << "Failed to create OFD file";
        return 1;
    }

    // Read OFD file
    QVector<QImage> readImages;
    ofd::Reader reader;
    if (!reader.readFile("test.ofd", readImages)) {
        qWarning() << "Failed to read OFD file";
        return 1;
    }

    qWarning() << "Successfully read" << readImages.size() << "images from OFD file";
    return 0;
} 