---
layout: default
transition: slide-left
---

# 选中、变换与几何约束

<style>
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; line-height: 1.4; }
.process-row { gap: 0.5rem; margin-bottom: 0.7rem !important; }
.process-step { padding-top: 0.5rem; }
.process-title { font-size: 0.88rem; }
.process-copy { font-size: 0.74rem; line-height: 1.4; }
.statement-band { font-size: 0.92rem; line-height: 1.45; padding-left: 0.85rem; }
.deck-stage.tight { padding: 0.7rem 0.95rem; }
</style>

<div class="deck-rule"></div>

<div class="deck-lead">
  选择与缩放是编辑器里最容易出错的环节：拖拽抖动、手柄翻转、圆形被拉歪。我把几何关系抽成单独的中间模型，事件代码只负责转译，不参与计算。
</div>

<div class="process-row mb-6">
  <div v-click class="process-step">
    <div class="process-no">GEOM 01</div>
    <div class="process-title"><code>SelectionFrame</code></div>
    <div class="process-copy">用 <code>topLeft + xAxis + yAxis</code> 表达朝向矩形，不只依赖轴对齐包围盒。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 02</div>
    <div class="process-title">Overlay + Handle</div>
    <div class="process-copy">覆盖层单独绘制虚线框和四角手柄，命中手柄后优先进入缩放会话。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 03</div>
    <div class="process-title"><code>CanvasGeometry</code></div>
    <div class="process-copy">frame 变换、等比缩放、防翻转钳制都做成 core 层的纯函数。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 04</div>
    <div class="process-title">交互约束</div>
    <div class="process-copy"><code>Shift</code> 保持宽高比，<code>Esc</code> 取消当前会话，多选通过快照回滚。</div>
  </div>
</div>

<div v-click class="deck-stage tight">
  <div class="statement-band">
    核心做法是把「鼠标怎么动」翻译成「框架怎么变」。
    一旦这层中间表示稳定，UI 事件代码就不再同时承担输入分发、状态维护和矩阵计算三件事。
  </div>
</div>

<!--
各位老师，这一页我讲为什么几何要单独抽出来。SelectionFrame 是关键——它用 topLeft 加 xAxis 加 yAxis 三个字段表达一个朝向矩形，不只依赖轴对齐的 bounding box，能描述旋转后的方向。Overlay 单独画虚线框和四角手柄，点击手柄会优先进入缩放会话，这是事件分发里手柄优先级高于普通选中的来源。CanvasGeometry 把 frame 变换、等比缩放、防翻转钳制都做成 core 层的纯函数，core 层的 CanvasGeometryTests 直接覆盖这些函数。Shift 保持宽高比、Esc 取消、多选用快照回滚，是交互层面的具体约束。这样做的核心好处是：UI 事件代码只负责「鼠标怎么动」到「框架怎么变」的转译，矩阵计算全部由 CanvasGeometry 这个独立单元承担，互不污染。下面进入国际化与主题。
-->
