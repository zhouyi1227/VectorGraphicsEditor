---
layout: default
transition: slide-left
---

# 测试体系

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">Qt Test + CTest · 40 个用例 · 5 个模块</div>

<div style="display:grid;grid-template-columns:repeat(5,1fr);gap:0.5rem;margin-bottom:1.5rem;">

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.5rem;text-align:center;">
<div style="font-size:1.5rem;font-weight:700;color:#2d7ff9;">13</div>
<div style="font-size:0.7rem;color:#666;">ShapeData</div>
</div>

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.5rem;text-align:center;">
<div style="font-size:1.5rem;font-weight:700;color:#2d7ff9;">5</div>
<div style="font-size:0.7rem;color:#666;">FileManager</div>
</div>

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.5rem;text-align:center;">
<div style="font-size:1.5rem;font-weight:700;color:#2d7ff9;">10</div>
<div style="font-size:0.7rem;color:#666;">CanvasGeometry</div>
</div>

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.5rem;text-align:center;">
<div style="font-size:1.5rem;font-weight:700;color:#2d7ff9;">10</div>
<div style="font-size:0.7rem;color:#666;">ShapeItem</div>
</div>

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.5rem;text-align:center;">
<div style="font-size:1.5rem;font-weight:700;color:#2d7ff9;">2</div>
<div style="font-size:0.7rem;color:#666;">MainWindow</div>
</div>

</div>

<v-click>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:1rem;background:#fafafa;margin-bottom:1rem;">

<div style="font-weight:600;font-size:0.85rem;margin-bottom:0.3rem;">测试示例 — 序列化 round-trip</div>

```cpp
void test_circle_roundtrip() {
    ShapeData original;
    original.type = ShapeType::Circle;
    original.rect = {0, 0, 100, 100};

    auto json = shapeDataToJson(original);
    auto result = shapeDataFromJson(json);

    QVERIFY(result.has_value());
    QCOMPARE(result->type, ShapeType::Circle);
    // 归一化保证宽高相等
    QCOMPARE(result->rect.width(),
             result->rect.height());
}
```

</div>

</v-click>

<v-click>

<div style="font-size:0.85rem;color:#666;display:flex;gap:0.5rem;justify-content:center;">
<span><!-- 覆盖点 -->ShapeDataTests 覆盖 7 种图形 · FileManagerTests 验证版本检测 + 格式校验 · ctest --preset test-ucrt64-debug</span>
</div>

</v-click>

<!--
测试体系使用Qt Test框架，40个测试用例分布在5个测试模块中。ShapeDataTests覆盖序列化往返一致性、7种图形类型的归一化、负宽高夹紧、圆形正方形化等边界条件。FileManagerTests验证版本号检测、重复ID拒绝、不支持的变换矩阵拒绝等错误路径。CanvasGeometryTests覆盖正圆生成、保持比例缩放、防止翻转变换等。ShapeItemTests验证每种图形类型的QPainterPath构建结果以及交互路径的padding扩展。
-->
