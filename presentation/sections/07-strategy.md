---
layout: two-cols-header
transition: slide-left
---

# 核心数据模型

<div class="deck-rule"></div>
<div class="deck-lead">
  <code>ShapeData</code> 是整个项目最重要的边界对象。它不持有界面行为，只负责把图形的身份、几何、样式、变换和层级稳定地传过四层。
</div>

::left::

```cpp {1|2-7|8-9}
struct ShapeData {
    QString id;
    ShapeType type = ShapeType::Rectangle;
    QVector<QPointF> points;
    QRectF rect;
    ShapeStyle style;
    QTransform transform;
    qreal zValue = 0.0;
};
```

<div class="diagram-caption">位于 <code>core/ShapeData.h</code>，跨四层统一边界对象。</div>

::right::

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">边界</div>
    <div class="rail-title">一个 struct 跨四层</div>
    <div class="rail-copy">界面、图形、文件 I/O 都通过 <code>ShapeData</code> 交换信息，视图对象不泄漏到核心层。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">几何</div>
    <div class="rail-title">同构字段承载 7 种图形</div>
    <div class="rail-copy"><code>Point / Line / Polyline / Polygon</code> 用 <code>points</code>，<code>Circle / Ellipse / Rectangle</code> 用 <code>rect</code>。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">不变量</div>
    <div class="rail-title">规则放自由函数里</div>
    <div class="rail-copy"><code>normalizedShapeData()</code> 处理负宽高和圆形正方形化；<code>shapeDataToJson / shapeDataFromJson</code> 负责 JSON 字段契约。</div>
  </div>
</div>

<!--
各位老师，ShapeData 定义成 struct 而不是 class，因为它是纯数据容器。真正的不变量放自由函数里：normalizedShapeData 处理负宽高和圆形的正方形化。这种写法让 core 层的单元测试不依赖任何 Qt 图形对象。
-->
