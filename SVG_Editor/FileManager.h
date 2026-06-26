#pragma once

#include <QList>
#include <QSizeF>
#include <QString>

#include <optional>

#include "ShapeData.h"

struct DocumentData {
    QSizeF canvasSize;
    QList<ShapeData> shapes;
};

class FileManager {
  public:
    static bool saveToFile(const QString& filePath, const DocumentData& document, QString* errorMessage = nullptr);
    static std::optional<DocumentData> loadFromFile(const QString& filePath, QString* errorMessage = nullptr);
};
