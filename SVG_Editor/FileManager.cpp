#include "FileManager.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

bool FileManager::saveToFile(const QString& filePath, const DocumentData& document, QString* errorMessage) {
    QJsonArray shapeArray;
    for (const ShapeData& shape : document.shapes) {
        shapeArray.append(shapeDataToJson(shape));
    }

    const QJsonObject root = {
        {"version", 1},
        {"canvas",
         QJsonObject{
             {"width", document.canvasSize.width()},
             {"height", document.canvasSize.height()},
         }},
        {"shapes", shapeArray},
    };

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if (errorMessage != nullptr) {
            *errorMessage = file.errorString();
        }
        return false;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    return true;
}

std::optional<DocumentData> FileManager::loadFromFile(const QString& filePath, QString* errorMessage) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        if (errorMessage != nullptr) {
            *errorMessage = file.errorString();
        }
        return std::nullopt;
    }

    const QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    if (!document.isObject()) {
        if (errorMessage != nullptr) {
            *errorMessage = "Invalid JSON document.";
        }
        return std::nullopt;
    }

    const QJsonObject root = document.object();
    const QJsonObject canvas = root.value("canvas").toObject();

    DocumentData data;
    data.canvasSize = QSizeF(canvas.value("width").toDouble(1200.0), canvas.value("height").toDouble(800.0));

    const QJsonArray shapes = root.value("shapes").toArray();
    for (const auto& value : shapes) {
        const std::optional<ShapeData> shape = shapeDataFromJson(value.toObject());
        if (shape.has_value()) {
            data.shapes.append(*shape);
        }
    }

    return data;
}
