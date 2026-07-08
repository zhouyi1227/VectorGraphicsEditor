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

<div class="diagram-caption"><code>CanvasView</code> 在构造函数中把能力注入到创建策略对象里。</div>

::right::

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">为什么</div>
    <div class="rail-title">不让策略直接依赖 <code>CanvasView</code></div>
    <div class="rail-copy">那样会让策略反向耦合整个视图类，测试和复用都会被窗口状态牵制。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">注入什么</div>
    <div class="rail-title">能力，不是容器</div>
    <div class="rail-copy">策略拿到最小必要能力：生成 ID、读取当前样式、分配 z 值、把图形加入场景。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">效果</div>
    <div class="rail-title">preview 和落盘共用一套逻辑</div>
    <div class="rail-copy">同一套策略既能驱动 preview item，也能在 <code>mouseReleaseEvent</code> 时生成真实图形。</div>
  </div>
</div>

<!--
各位老师，CreationContext 把策略需要的 5 个能力抽成 5 个 std::function。CanvasView 在构造函数里注入到策略对象中。这样 preview 和落盘共用同一套策略，不会变成两份逻辑。
-->
