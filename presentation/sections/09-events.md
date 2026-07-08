---
layout: default
transition: slide-left
---

# 多态与策略模式

<div class="deck-rule"></div>

<div class="deck-lead">
  创建流程通过 <code>ICreationStrategy</code> 统一暴露，<code>CanvasView</code> 只持有基类指针。工具切换在运行时完成，视图类不会膨胀成 if / else 链。
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

<div class="split-even mt-4">
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
      <div class="rail-copy">在 <code>mousePressEvent / mouseMoveEvent / mouseReleaseEvent</code> 里通过基类指针调用策略。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">扩展</div>
      <div class="rail-title">新增工具只补一个策略</div>
      <div class="rail-copy">加一种图形 = 补一个策略 + 接入路由，不改动输入状态机。</div>
    </div>
  </div>
</div>

<!--
各位老师，运行时多态四条件这里全满足：基类虚函数、派生类 override、基类指针调用、指向派生类对象。ICreationStrategy 的五个虚函数是契约，两种策略各自实现，CanvasView 不为每种图形写分支代码。
-->
