---
layout: two-cols-header
transition: slide-left
---

# 图形绘制与命中测试

<style>
.deck-lead { margin-bottom: 0.4rem; font-size: 0.82rem; line-height: 1.4; }
.slidev-layout.two-cols-header { gap: 4rem !important; column-gap: 4rem !important; padding: 1rem 2rem !important; }
.slidev-layout.two-cols-header > .col-left { padding-right: 0 !important; }
.slidev-layout.two-cols-header > .col-right { padding-left: 1rem !important; }
.rail-copy { font-size: 0.72rem; line-height: 1.35; }
.rail-title { font-size: 0.84rem; }
.rail-list { gap: 0.35rem; }
.rail-item { padding-left: 0.65rem; }
.deck-stage { padding: 0.55rem 0.8rem; }
.eyebrow { font-size: 0.66rem; margin-bottom: 0.2rem; }
.thin-divider { margin: 0.3rem 0 0.4rem; }
.rail-index { font-size: 0.68rem; margin-bottom: 0.1rem; }
</style>

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
    <div class="rail-copy">把同一份 <code>ShapeData</code> 几何信息翻译成 <code>QPainterPath</code>，支撑矩形、圆、折线、多边形等图元。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">绘制 3</div>
    <div class="rail-title"><code>ShapeFactory</code></div>
    <div class="rail-copy">集中负责创建、归一化和复制偏移，避免这些重复动作散落在 UI 或事件代码里。</div>
  </div>
</div>

::right::

<div class="deck-stage">
  <div class="eyebrow">命中测试</div>
  <div class="thin-divider"></div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-title"><code>boundingRect()</code></div>
      <div class="rail-copy">给 Qt 做重绘裁剪和粗粒度包围盒判断，重点是效率与范围。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-title"><code>shape()</code></div>
      <div class="rail-copy">给鼠标命中测试、选择和碰撞判断提供更精确的路径区域，重点是交互准确性。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-title">细图元需要扩交互区</div>
      <div class="rail-copy">点和线段这种细图元如果不扩展交互区，会出现「看得见但点不中」的问题。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页我讲绘制和命中测试为什么要分开。ShapeItem::paint 负责把 ShapeData 画到 QPainter 上。buildPath 和 buildBasePath 是辅助函数，把同一份 ShapeData 几何信息翻译成 QPainterPath，让 paint 能统一处理矩形、圆、折线、多边形。ShapeFactory 把创建、归一化、复制偏移集中放在一个工厂里，不让这些动作散在 UI 或事件代码里。命中测试这一侧：boundingRect 给 Qt 做重绘裁剪和粗粒度判断，shape() 给鼠标命中、选择、碰撞判断提供精确路径。重点是点和线段这种细图元如果不扩展交互区域，就会出现「看得见但点不中」，我专门在 ShapeItem::shape() 里加了 hit-test 扩展。
-->
