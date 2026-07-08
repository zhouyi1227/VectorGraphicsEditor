---
layout: two-cols-header
transition: slide-left
---

# 图形绘制与命中测试

<div class="deck-rule"></div>
<div class="deck-lead">
  图形编辑器要保证「画得出、选得中、复制对」。绘制路径和命中路径被刻意分开设计。
</div>

::left::

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">绘制 1</div>
    <div class="rail-title"><code>ShapeItem::paint</code></div>
    <div class="rail-copy">根据 <code>ShapeType</code> 选择绘制分支，统一应用描边、填充与 preview 样式。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">绘制 2</div>
    <div class="rail-title"><code>buildPath / buildBasePath</code></div>
    <div class="rail-copy">把 <code>ShapeData</code> 几何翻译成 <code>QPainterPath</code>，支撑所有图元。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">绘制 3</div>
    <div class="rail-title"><code>ShapeFactory</code></div>
    <div class="rail-copy">集中负责创建、归一化和复制偏移，避免散落在 UI 或事件代码里。</div>
  </div>
</div>

::right::

<div class="deck-stage">
  <div class="eyebrow">命中测试</div>
  <div class="thin-divider"></div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-title"><code>boundingRect()</code></div>
      <div class="rail-copy">给 Qt 做重绘裁剪和粗粒度包围盒判断。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-title"><code>shape()</code></div>
      <div class="rail-copy">给鼠标命中、选择和碰撞判断提供精确路径区域。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-title">细图元扩交互区</div>
      <div class="rail-copy">点和线段这类细图元扩展交互区，避免「看得见但点不中」。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页讲绘制和命中测试为什么要分开。ShapeItem::paint 负责渲染，buildPath 翻译几何。命中测试侧：boundingRect 给 Qt 做裁剪，shape() 给鼠标命中提供精确路径。细图元如果不扩展交互区会点不中。
-->
