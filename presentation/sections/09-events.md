---
layout: default
transition: slide-left
---

# 多态与策略模式

<div class="deck-rule"></div>

<div class="deck-lead">
  创建流程通过 <code>ICreationStrategy</code> 统一暴露，<code>CanvasView</code> 只持有基类指针。
  因此工具切换发生在运行时，视图类本身不需要继续膨胀成一串巨大的 <code>if / else</code>。
</div>

```cpp {1|2-8}
class ICreationStrategy {
  public:
    virtual ~ICreationStrategy() = default;
    virtual void begin(const QPointF& scenePoint) = 0;
    virtual void update(const QPointF& scenePoint) = 0;
    virtual void finish(const QPointF& scenePoint) = 0;
    virtual void cancel() = 0;
    virtual bool inProgress() const = 0;
};
```

<div class="split-even mt-5">
  <div class="deck-stage">
    <div class="eyebrow">运行时分工</div>
    <div class="thin-divider"></div>
    <div class="rail-list">
      <div v-click class="rail-item">
        <div class="rail-title"><code>DragCreationStrategy</code></div>
        <div class="rail-copy">负责直线、圆、椭圆和矩形，适合“按下-拖拽-释放”的连续手势。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>PathCreationStrategy</code></div>
        <div class="rail-copy">负责折线和多边形，适合“逐点采样、显式结束”的离散输入。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">CANVASVIEW</div>
      <div class="rail-title">只负责路由</div>
      <div class="rail-copy">在 <code>mousePressEvent / mouseMoveEvent / mouseReleaseEvent</code> 中通过基类指针调用 <code>begin / update / finish</code>。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">PAYOFF</div>
      <div class="rail-title">扩展成本稳定</div>
      <div class="rail-copy">新增创建方式时，主要工作是补一个策略并接入工具路由，而不是改动整块输入状态机。</div>
    </div>
  </div>
</div>

<!--
这一页重点回答“多态具体体现在哪里”。四个条件是：基类虚函数、派生类 override、基类指针调用、指向派生类对象。这里四个条件全满足，所以这不是形式上的接口，而是真正的运行时多态。
-->
