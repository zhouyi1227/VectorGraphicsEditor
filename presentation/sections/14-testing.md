---
layout: default
transition: slide-left
---

# 选中、变换与几何约束

<div class="deck-rule"></div>

<div class="deck-lead">
  选择与缩放是整个编辑器里最容易出错的环节。为避免拖拽抖动、手柄翻转和圆形被拉歪，几何关系被单独抽象成稳定的中间模型。
</div>

<div class="process-row mb-6">
  <div v-click class="process-step">
    <div class="process-no">GEOM 01</div>
    <div class="process-title"><code>SelectionFrame</code></div>
    <div class="process-copy">用 <code>topLeft + xAxis + yAxis</code> 表达朝向矩形，而不是只依赖轴对齐包围盒。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 02</div>
    <div class="process-title">Overlay + Handle</div>
    <div class="process-copy">覆盖层单独绘制虚线框和四角手柄，点击命中后优先进入缩放会话。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 03</div>
    <div class="process-title"><code>CanvasGeometry</code></div>
    <div class="process-copy">把 frame 变换、等比缩放和防翻转钳制都做成核心层纯函数。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 04</div>
    <div class="process-title">交互约束</div>
    <div class="process-copy"><code>Shift</code> 保持宽高比，<code>Esc</code> 取消当前会话，多选通过快照回滚。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">GEOM 05</div>
    <div class="process-title">测试兜底</div>
    <div class="process-copy">用专门的几何测试覆盖正交化、等比缩放、角点映射和防翻转行为。</div>
  </div>
</div>

<div v-click class="deck-stage tight">
  <div class="statement-band">
    核心思路是把“鼠标怎么动”翻译成“框架怎么变”。
    一旦这层抽象稳定，UI 事件代码就不会再承担全部几何推导负担。
  </div>
</div>

<!--
这一页的关键词是“把复杂几何从事件代码里拿出来”。否则 mouseMoveEvent 会同时承担输入分发、状态维护和矩阵计算，既难读也难测。SelectionFrame 的意义就在于给变换一个稳定的中间表示。
-->
