---
layout: default
transition: slide-left
---

# 选中、变换与几何约束

<div class="deck-rule"></div>

<div class="deck-lead">
  选择与缩放是编辑器里最容易出错的环节：拖拽抖动、手柄翻转、圆形被拉歪。我把几何关系抽成单独的中间模型，事件代码只负责转译，不参与计算。
</div>

<div class="process-row mb-5">
  <div v-click class="process-step">
    <div class="process-no">GEOM 01</div>
    <div class="process-title"><code>SelectionFrame</code></div>
    <div class="process-copy">用 <code>topLeft + xAxis + yAxis</code> 表达朝向矩形。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 02</div>
    <div class="process-title">Overlay + Handle</div>
    <div class="process-copy">虚线框和四角手柄，命中手柄优先进入缩放会话。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 03</div>
    <div class="process-title"><code>CanvasGeometry</code></div>
    <div class="process-copy">frame 变换、等比缩放、防翻转钳制做成 core 层纯函数。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 04</div>
    <div class="process-title">交互约束</div>
    <div class="process-copy"><code>Shift</code> 等比，<code>Esc</code> 取消，多选快照回滚。</div>
  </div>
</div>

<div v-click class="deck-stage tight">
  <div class="statement-band">
    核心做法是把「鼠标怎么动」翻译成「框架怎么变」。UI 事件代码不再同时承担输入分发、状态维护和矩阵计算三件事。
  </div>
</div>

<!--
各位老师，几何为什么要单独抽出来。SelectionFrame 用 topLeft + xAxis + yAxis 描述朝向矩形。CanvasGeometry 把 frame 变换等做成 core 层纯函数，Core 层 CanvasGeometryTests 直接覆盖。UI 只负责翻译，矩阵计算由 CanvasGeometry 独立承担。
-->
