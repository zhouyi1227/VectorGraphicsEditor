---
layout: two-cols
transition: slide-left
---

# 依赖注入与创建上下文

<style>
.slidev-layout.two-cols { gap: 4rem !important; column-gap: 4rem !important; padding: 1rem 2rem !important; }
.slidev-layout.two-cols > .col-left { padding-right: 0 !important; }
.slidev-layout.two-cols > .col-right { padding-left: 1rem !important; }
.slidev-layout.two-cols pre.shiki { font-size: 0.7rem !important; padding: 0.55rem 0.75rem !important; line-height: 1.45; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.rail-list { gap: 0.5rem; }
.rail-item { padding-left: 0.7rem; }
.diagram-caption { font-size: 0.78rem; margin-top: 0.5rem; line-height: 1.4; }
</style>

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
    <div class="rail-index">为什么</div>
    <div class="rail-title">不让策略直接依赖 <code>CanvasView</code></div>
    <div class="rail-copy">那样会让策略反向耦合整个视图类，测试和复用都会被窗口内部状态牵制。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">注入什么</div>
    <div class="rail-title">能力，不是容器</div>
    <div class="rail-copy">策略拿到的是生成 ID、读取当前样式、分配 z 值、把图形加入场景这一组最小必要能力。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">效果</div>
    <div class="rail-title">preview 和落盘共用一套逻辑</div>
    <div class="rail-copy">同一套策略既能驱动 preview item，也能在 <code>mouseReleaseEvent</code> 时生成真实图形对象。</div>
  </div>
</div>

<!--
各位老师，这一页我讲依赖注入具体落在哪里。CreationContext 这个 struct 是关键——它的作用是把策略运行需要的 5 个能力抽成 5 个 std::function：nextZValue 分配层级、currentStyleFor 取当前工具的样式、addShape 把图形加入场景、generateId 生成唯一标识、currentShapeType 读当前选中的工具类型。CanvasView 在构造函数里把这 5 个能力注入到三个策略对象里。这种写法的直接好处是 preview 和落盘共用同一套策略：拖拽过程中驱动 m_previewItem 显示预览，松手时同一份 finish 调用通过 addShape 落到正式场景里。如果让策略直接持有 CanvasView，preview 和落盘就会变成两份逻辑要维护。
-->
