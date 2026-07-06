---
layout: default
transition: slide-left
---

# 策略模式 · 创建交互

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">ICreationStrategy — 6 个纯虚函数，同一接口两种实现</div>

<div style="display:flex;gap:0.5rem;margin-bottom:1.5rem;font-size:0.75rem;font-family:monospace;">
<span style="background:#f5f5f5;padding:0.2rem 0.6rem;border-radius:3px;">begin(pt)</span>
<span style="background:#f5f5f5;padding:0.2rem 0.6rem;border-radius:3px;">update(pt)</span>
<span style="background:#f5f5f5;padding:0.2rem 0.6rem;border-radius:3px;">finish(pt)</span>
<span style="background:#f5f5f5;padding:0.2rem 0.6rem;border-radius:3px;">cancel()</span>
<span style="background:#f5f5f5;padding:0.2rem 0.6rem;border-radius:3px;">inProgress()</span>
<span style="background:#f5f5f5;padding:0.2rem 0.6rem;border-radius:3px;">isPreviewItem()</span>
</div>

<div class="grid" style="display:grid;grid-template-columns:1fr 1fr;gap:1rem;">

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">

<div style="font-weight:600;font-size:0.9rem;margin-bottom:0.3rem;">DragCreationStrategy</div>
<div class="dim" style="font-size:0.75rem;margin-bottom:0.5rem;">Line / Circle / Ellipse / Rectangle</div>

```cpp
void begin(pt) {
    m_dragStart = pt;
    m_drawing = true;
    createPreview(pt);
}
void update(pt) {
    auto data =
      buildDragShapeData(pt);
    m_preview->setData(data);
}
void finish(pt) {
    if (size >= 1.0) finalize();
    else cancel();
}
```

</div>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">

<div style="font-weight:600;font-size:0.9rem;margin-bottom:0.3rem;">PathCreationStrategy</div>
<div class="dim" style="font-size:0.75rem;margin-bottom:0.5rem;">Polyline / Polygon</div>

```cpp
void begin(pt) {
    m_points.append(pt);
    if (m_points.size() == 1)
        createPreview(pt);
}
void finish(pt) {
    m_points.append(pt);
    // 双击或 Enter 完成
}
void cancel() {
    removePreview();
    m_points.clear();
}
```

</div>

</div>

<v-click>

<div style="margin-top:1rem;padding:0.6rem 1rem;background:#fafafa;border:1px solid #eee;border-radius:4px;font-size:0.85rem;">

CanvasView 持有 3 个 <code>std::unique_ptr&lt;ICreationStrategy&gt;</code>，通过 <code>currentCreationStrategy()</code> 按 <code>m_tool</code> 分发到对应策略。

</div>

</v-click>

<!--
策略模式是项目的核心交互机制。ICreationStrategy定义6个纯虚函数作为创建算法的统一接口，两个派生类实现完全不同的交互方式。DragCreationStrategy适用于拖拽创建：鼠标按下记录起点，移动时实时更新预览，释放时检查最小尺寸后创建正式图形。PathCreationStrategy适用于多顶点输入：每次点击新增一个顶点，双击或回车完成。最小尺寸1像素的检查防止用户创建误触级别的微小图形。
-->
