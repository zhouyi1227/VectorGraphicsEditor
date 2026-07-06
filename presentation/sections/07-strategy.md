---
layout: two-cols-header
transition: slide-left
---

# 核心数据模型

<style>
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; line-height: 1.4; }
.slidev-layout.two-cols-header { gap: 4rem !important; column-gap: 4rem !important; padding: 1rem 2rem !important; }
.slidev-layout.two-cols-header > .col-left { padding-right: 0 !important; }
.slidev-layout.two-cols-header > .col-right { padding-left: 1rem !important; }
pre.shiki { font-size: 0.7rem !important; padding: 0.55rem 0.75rem !important; line-height: 1.45; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.rail-list { gap: 0.5rem; }
.rail-item { padding-left: 0.7rem; }
.diagram-caption { font-size: 0.78rem; margin-top: 0.5rem; line-height: 1.4; }
</style>

<div class="deck-rule"></div>
<div class="deck-lead">
  <code>ShapeData</code> 是整个项目最重要的边界对象。它不持有界面行为，只负责把图形的身份、几何、样式、变换和层级稳定地传给图形层、文件层和界面层。
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

<div class="diagram-caption">真实定义位于 <code>core/ShapeData.h</code>，跨 <code>core / graphics / canvas / ui</code> 统一边界对象。</div>

::right::

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">边界</div>
    <div class="rail-title">一个 struct 跨四层</div>
    <div class="rail-copy">界面、图形、文件 I/O 都通过 <code>ShapeData</code> 交换信息，视图对象不会泄漏到核心层。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">几何</div>
    <div class="rail-title">同构字段承载 7 种图形</div>
    <div class="rail-copy"><code>Point / Line / Polyline / Polygon</code> 用 <code>points</code>，<code>Circle / Ellipse / Rectangle</code> 用 <code>rect</code>。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">不变量</div>
    <div class="rail-title">规则放自由函数里</div>
    <div class="rail-copy"><code>normalizedShapeData()</code> 处理负宽高和圆形正方形化；<code>shapeDataToJson</code> / <code>shapeDataFromJson</code> 负责稳定的 JSON 字段契约。</div>
  </div>
</div>

<!--
各位老师，我现在讲核心数据模型 ShapeData。我把它定义成 struct 而不是 class，因为它是纯数据容器，字段需要在多个层之间直接读写。真正的不变量放自由函数里：normalizedShapeData 处理负宽高和圆形的正方形化，shapeDataToJson 和 shapeDataFromJson 是文件 I/O 的入口。这种 struct 加自由函数的写法在课程设计里有一个具体的价值：让 core 层的单元测试不依赖任何 Qt 图形对象。后面的 ShapeDataTests 之所以能在没有 QApplication 的进程里跑，就是这个边界起的作用。下面讲继承体系。
-->
