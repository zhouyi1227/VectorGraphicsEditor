---
layout: two-cols-header
transition: slide-left
---

# 图形绘制与命中测试

<div class="deck-rule"></div>
<div class="deck-lead">
  图形编辑器不能只把内容“画出来”，还必须保证图形“选得到、点得准、复制得对”。因此绘制路径和命中路径被刻意分开设计。
</div>

::left::

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">DRAW 01</div>
    <div class="rail-title"><code>ShapeItem::paint</code></div>
    <div class="rail-copy">根据 <code>ShapeType</code> 选择绘制分支，并统一应用描边、填充与 preview 样式。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">DRAW 02</div>
    <div class="rail-title"><code>buildPath / buildBasePath</code></div>
    <div class="rail-copy">把同一份 <code>ShapeData</code> 几何信息翻译成 <code>QPainterPath</code>，支撑矩形、圆、折线、多边形等图元。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">DRAW 03</div>
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
      <div class="rail-title">细图形需要额外扩展</div>
      <div class="rail-copy">对点和线段这类细图元，如果不扩展交互区域，就会出现“看得见但点不中”的体验问题。</div>
    </div>
  </div>
</div>

<!--
这里可以顺着老师的问题讲：为什么不是只实现一个 paint 就结束。因为图形编辑器不仅要“画出来”，还要“选得到、点得准、复制得对”。所以绘制路径和命中路径是两个不同层面的需求。
-->
