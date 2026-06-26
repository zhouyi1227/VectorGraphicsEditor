#include <QtTest>

#include <QTemporaryDir>

#include "FileManager.h"

class FileManagerTests : public QObject {
    Q_OBJECT

  private slots:
    void saveAndLoadDocument();
};

void FileManagerTests::saveAndLoadDocument() {
    QTemporaryDir tempDir;
    QVERIFY(tempDir.isValid());

    DocumentData document;
    document.canvasSize = QSizeF(800.0, 600.0);

    ShapeData rectangle;
    rectangle.id = "rect-1";
    rectangle.type = ShapeType::Rectangle;
    rectangle.rect = QRectF(10.0, 20.0, 100.0, 60.0);
    rectangle.style.fillEnabled = true;
    rectangle.style.fillColor = QColor("#ff0099cc");
    rectangle.zValue = 3.0;
    document.shapes.append(rectangle);

    const QString filePath = tempDir.filePath("sample.vgjson");
    QString saveError;
    QVERIFY(FileManager::saveToFile(filePath, document, &saveError));
    QVERIFY2(saveError.isEmpty(), qPrintable(saveError));

    QString loadError;
    const std::optional<DocumentData> loaded = FileManager::loadFromFile(filePath, &loadError);
    QVERIFY(loaded.has_value());
    QVERIFY2(loadError.isEmpty(), qPrintable(loadError));
    const DocumentData& loadedDocument = loaded.value();
    QCOMPARE(loadedDocument.canvasSize.width(), document.canvasSize.width());
    QCOMPARE(loadedDocument.canvasSize.height(), document.canvasSize.height());
    QCOMPARE(loadedDocument.shapes.size(), 1);
    QCOMPARE(loadedDocument.shapes.first().type, ShapeType::Rectangle);
    QCOMPARE(loadedDocument.shapes.first().rect, rectangle.rect);
    QCOMPARE(loadedDocument.shapes.first().style.fillEnabled, rectangle.style.fillEnabled);
    QCOMPARE(loadedDocument.shapes.first().zValue, rectangle.zValue);
}

QTEST_APPLESS_MAIN(FileManagerTests)

#include "FileManagerTests.moc"
