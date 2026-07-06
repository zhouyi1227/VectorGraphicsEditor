---
layout: two-cols
transition: slide-left
---

# 依赖注入与创建上下文

<div class="deck-rule"></div>

::left::

```cpp {1|2-7}
struct CreationContext {
    std::function<qreal()> nextZValue;
    std::function<ShapeStyle(ShapeType)> currentStyleFor;
    std::function<void(const ShapeData&, bool)> addShape;
    std::function<QString()> generateId;
    std::function<std::optional<ShapeType>()> currentShapeType;
    QGraphicsScene* scene = nullptr;
};
```

<div class="diagram-caption"><code>CanvasView</code> 在构造函数中一次性把这组能力注入到三个创建策略对象里。</div>

::right::

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">WHY</div>
    <div class="rail-title">为什么不用“策略直接依赖 CanvasView”</div>
    <div class="rail-copy">那样策略会反向耦合整个视图类，测试和复用都会受到窗口内部状态的牵制。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">INJECT</div>
    <div class="rail-title">真正注入的是能力，不是容器</div>
    <div class="rail-copy">策略只拿到生成 ID、读取当前样式、分配 z 值、把图形加入场景这些最小必要能力。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">RESULT</div>
    <div class="rail-title">预览和落盘共用一套逻辑</div>
    <div class="rail-copy">同一套策略既能驱动 preview item，也能在最终释放鼠标时生成真实图形对象。</div>
  </div>
</div>

<!--
如果老师问“依赖注入体现在哪”，这里就是最直接的例子。CreationContext 不是为了炫技巧，而是为了让策略层只依赖一小组稳定能力，不需要知道 CanvasView 的全部内部状态。
-->
