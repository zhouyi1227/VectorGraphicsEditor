---
layout: default
transition: slide-left
---

# 核心数据模型 · ShapeData

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">core/ShapeData.h · 153 行 · struct 而非 class</div>

<div class="grid" style="display:grid;grid-template-columns:1fr 1fr;gap:1.5rem;">

<div>

```cpp
struct ShapeData {
    QString id;
    ShapeType type;
    QVector<QPointF> points;
    QRectF rect;
    ShapeStyle style;
    QTransform transform;
    qreal zValue = 0.0;
};

struct ShapeStyle {
    bool strokeEnabled = true;
    QColor strokeColor = Qt::black;
    qreal strokeWidth = 2.0;
    QColor fillColor = "#80c8ff";
    bool fillEnabled = false;
};
```

</div>

<div>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">

<div style="font-weight:600;font-size:0.9rem;margin-bottom:0.5rem;">ShapeType · 7 种图形</div>

| 类型 | 字段 | 说明 |
|------|------|------|
| Point | points[0] | 直径 6px |
| Line | points[0..1] | 线段 |
| Polyline | points[0..n] | ≥2 顶点 |
| Polygon | points[0..n] | 自动闭合 |
| Circle | rect | 强制正方形框 |
| Ellipse | rect | 外接矩形 |
| Rectangle | rect | 任意方向 |

</div>

<v-click>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;margin-top:0.75rem;">

<div style="font-weight:600;font-size:0.9rem;margin-bottom:0.3rem;">归一化保证</div>

<div style="font-size:0.85rem;color:#555;">

`normalizedShapeData()` 在构造时执行:

- 负宽高 rect → 规范化为左上角 + 正值
- Circle → 宽高取 max，强制正方形
- 不支持填充的类型 → fillEnabled = false

</div>

</div>

</v-click>

</div>

</div>

<!--
ShapeData是整个系统的数据模型基座，采用struct而非class，因为它是纯数据容器，所有字段需要被外部读写，没有需要隐藏的内部实现细节。7种图形类型分为两类：基于点的和基于矩形框的。这种二分法决定了交互创建方式的不同——前者需要多次点击，后者一次拖拽完成。归一化函数在构造和加载时都会调用，保证内部始终是规范的几何数据。
-->
