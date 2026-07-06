---
layout: default
transition: slide-left
---

# 多态分发 · 鼠标事件

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">QGraphicsView 虚函数 → CanvasView override → 策略路由</div>

<div class="grid" style="display:grid;grid-template-columns:1fr 1fr;gap:1.5rem;">

<div style="overflow:hidden;">

```cpp
void CanvasView::
mousePressEvent(QMouseEvent* e) {
    auto pt = mapToScene(
        e->position().toPoint());

    if (m_tool == Tool::Select) {
        handleSelectPress(pt);
        return;
    }

    auto* strategy =
        currentCreationStrategy();
    if (strategy)
        strategy->begin(pt);
    // → DragCreationStrategy::begin
    //   或 PathCreationStrategy::begin
}
```

</div>

<div>

<v-click>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:1rem;">

<div style="font-weight:600;font-size:0.85rem;margin-bottom:0.5rem;">currentCreationStrategy()</div>

```cpp
ICreationStrategy*
CanvasView::
currentCreationStrategy() {
    switch (m_tool) {
    case Point: case Line:
    case Circle: case Ellipse:
    case Rectangle:
        return m_dragStrategy.get();
    case Polyline:
        return m_polylineStrategy.get();
    case Polygon:
        return m_polygonStrategy.get();
    default: return nullptr;
    }
}
```

</div>

</v-click>

<v-click>

<div style="margin-top:0.75rem;padding:0.5rem 0.8rem;background:#fafafa;border:1px solid #eee;border-radius:4px;font-size:0.8rem;">

<strong>双层多态</strong> — Qt 框架层: QGraphicsView → CanvasView 的虚函数覆盖 · 应用层: ICreationStrategy* → 具体策略的虚函数调用

</div>

</v-click>

</div>

</div>

<!--
鼠标事件的分发分两层。第一层是Qt框架层面的多态——QGraphicsView定义了mousePressEvent等虚函数，CanvasView使用override覆盖，Qt事件系统通过基类指针调用时实际执行CanvasView版本。第二层是应用层面的策略分发——根据m_tool的值，currentCreationStrategy返回对应的策略对象，然后通过基类指针ICreationStrategy调用begin/update/finish。7个Tool枚举值映射为3种工具模式：选择、拖拽创建、路径创建。
-->
