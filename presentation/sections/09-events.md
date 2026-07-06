---
layout: default
transition: slide-left
---

# 多态与策略模式

<style>
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; line-height: 1.4; }
pre.shiki { font-size: 0.7rem !important; padding: 0.55rem 0.75rem !important; line-height: 1.45; }
.split-even { gap: 0.7rem; margin-top: 0.6rem !important; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.rail-list { gap: 0.45rem; }
.deck-stage { padding: 0.75rem 1rem; }
.rail-item { padding-left: 0.7rem; }
</style>

<div class="deck-rule"></div>

<div class="deck-lead">
  创建流程通过 <code>ICreationStrategy</code> 统一暴露，<code>CanvasView</code> 只持有基类指针。工具切换发生在运行时，视图类不会膨胀成一串 if / else。
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
        <div class="rail-copy">直线、圆、椭圆、矩形，对应「按下—拖拽—释放」连续手势。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>PathCreationStrategy</code></div>
        <div class="rail-copy">折线、多边形，对应「逐点采样、Enter / 双击结束」。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">CanvasView</div>
      <div class="rail-title">只负责路由</div>
      <div class="rail-copy">在 <code>mousePressEvent / mouseMoveEvent / mouseReleaseEvent</code> 里通过基类指针调用 <code>begin / update / finish</code>。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">扩展</div>
      <div class="rail-title">新增工具只补一个策略</div>
      <div class="rail-copy">加一种图形 = 补一个策略 + 接入路由。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页我讲运行时多态具体落在哪里。运行时多态的四条件：基类虚函数、派生类 override、基类指针调用、指向派生类对象——这里四条件全满足，所以这不是形式上的接口，是真的运行时多态。ICreationStrategy 的 begin / update / finish / cancel / inProgress 五个虚函数是契约。DragCreationStrategy 处理按下-拖拽-释放这种连续手势，对应 Line / Circle / Ellipse / Rectangle；PathCreationStrategy 处理逐点采样，对应 Polyline / Polygon。CanvasView 在 mousePressEvent / mouseMoveEvent / mouseReleaseEvent 里通过基类指针调用策略，不为每种图形写一份分支代码。扩展成本的稳定性是策略模式的主要价值：加一种新图形，工作量就是补一个策略类加接入工具路由，不会改动输入状态机本身。
-->
