---
layout: two-cols-header
transition: slide-left
---

# 核心数据模型

<div class="deck-rule"></div>
<div class="deck-lead">
  <code>ShapeData</code> 是整个项目最重要的边界对象。
  它不持有界面行为，只负责把图形的身份、几何、样式、变换和层级稳定地传给图形层、文件层和界面层。
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

<div class="diagram-caption">真实定义位于 <code>core/ShapeData.h</code>，它是跨 <code>core / graphics / canvas / ui</code> 的统一边界对象。</div>

::right::

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">BOUNDARY</div>
    <div class="rail-title">单一边界模型</div>
    <div class="rail-copy">界面、图形和文件 I/O 都通过 <code>ShapeData</code> 交换信息，避免让视图对象泄漏到核心层。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">GEOMETRY</div>
    <div class="rail-title">同一结构承载七种图形</div>
    <div class="rail-copy"><code>Point / Line / Polyline / Polygon</code> 主要使用 <code>points</code>，<code>Circle / Ellipse / Rectangle</code> 主要使用 <code>rect</code>。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">CONTRACT</div>
    <div class="rail-title">规则放在自由函数里</div>
    <div class="rail-copy"><code>normalizedShapeData()</code> 处理负宽高与圆形正方形化；序列化函数则负责稳定的 JSON 字段契约。</div>
  </div>
</div>

<!--
如果老师问为什么这里用 struct：因为它是纯数据容器，字段需要在多个层之间直接读写，没有额外封装不变式。真正的行为，比如归一化、平移、序列化，都放在自由函数里。
-->
