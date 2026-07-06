---
layout: default
transition: slide-left
---

# ShapeItem · 绘制与命中测试

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">QPainterPath 构建 · 7 分支 · 描边扩展命中</div>

<div class="grid" style="display:grid;grid-template-columns:1fr 1fr;gap:1.5rem;">

<div>

```cpp
QPainterPath ShapeItem::
buildBasePath() const {
    switch (m_data.type) {
    case Point:
        path.addEllipse(pt, 3, 3);
    case Line:
        path.moveTo(p[0]);
        path.lineTo(p[1]);
    case Rectangle:
        path.addRect(m_data.rect);
    case Circle:
        w = max(w, h);
        path.addEllipse(rect);
    case Polyline:
        for (auto& p : m_data.points)
            path.lineTo(p);
    case Polygon:
        for (auto& p : m_data.points)
            path.lineTo(p);
        path.closeSubpath();
    }
    return path;
}
```

</div>

<div>

<v-click>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:1rem;">

<div style="font-weight:600;font-size:0.85rem;margin-bottom:0.3rem;">命中测试 — shape()</div>

```cpp
QPainterPath ShapeItem::shape() const {
    auto path = buildBasePath();
    QPainterPathStroker stroker;
    stroker.setWidth(
        pen().widthF() +       // 描边宽度
        kHitPaddingMinPx +     // = 8.0
        kHitPaddingExtraPx);   // = 6.0
    auto stroke =
        stroker.createStroke(path);
    return fillEnabled
        ? path.united(stroke)
        : stroke;
}
```

</div>

</v-click>

<v-click>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem;margin-top:0.75rem;font-size:0.85rem;">

**boundingRect vs shape**

| | 用途 | 精确度 |
|--|------|--------|
| boundingRect | Qt 渲染裁剪 | 轴对齐矩形 + padding |
| shape | 命中测试 | 精确路径 + 描边扩展 |

</div>

</v-click>

</div>

</div>

<!--
ShapeItem的绘制通过buildBasePath构建QPainterPath，switch覆盖全部7种ShapeType。由于使用enum class且没有default分支，新增类型时编译器会警告遗漏。命中测试的关键在于shape和boundingRect的区分：boundingRect用于Qt的可见性判定和重绘区域计算，要求快速且保守；shape用于精确的鼠标点击判断。QPainterPathStroker把细线路径扩展为宽度等于描边宽度加padding的填充路径，这样细线也能被轻松选中。
-->
