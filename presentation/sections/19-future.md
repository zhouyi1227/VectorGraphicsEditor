---
layout: default
transition: slide-left
---

# 现场演示

<div class="deck-rule"></div>
<div class="deck-lead">
  接下来进行现场操作：创建、编辑、变换、复制、持久化。各位老师会看到完整链路在画布上运行一遍。
</div>

<div class="process-row mt-5 mb-5">
  <div v-click class="process-step">
    <div class="process-no">DEMO 01</div>
    <div class="process-title">创建</div>
    <div class="process-copy">拖出一个矩形，建立输入回路。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 02</div>
    <div class="process-title">编辑</div>
    <div class="process-copy">修改描边宽度、线型、填充色。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 03</div>
    <div class="process-title">变换</div>
    <div class="process-copy">多选后拖四角缩放，Shift 等比约束。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 04</div>
    <div class="process-title">复制</div>
    <div class="process-copy"><code>Ctrl+C / Ctrl+V</code>，深拷贝 + 16px 偏移。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 05</div>
    <div class="process-title">持久化</div>
    <div class="process-copy">保存 <code>.vgjson</code>，重开文档，导出 PNG。</div>
  </div>
</div>

<div class="deck-stage tight">
  <div class="support-grid">
    <div v-click class="support-row">
      <div class="support-key">Preview</div>
      <div class="support-copy">拖拽和路径创建都有连续预览，不是「松手才出现」。</div>
    </div>
    <div v-click class="support-row">
      <div class="support-key">Sync</div>
      <div class="support-copy">选中状态、属性面板、画布图形始终同步。</div>
    </div>
    <div v-click class="support-row">
      <div class="support-key">Replay</div>
      <div class="support-copy">重开文档仍保留图形、样式、层级，I/O 与渲染一致。</div>
    </div>
  </div>
</div>

<!--
各位老师，接下来现场演示五步。第一步创建，第二步编辑，第三步多选缩放，第四步复制粘贴，第五步保存重开。四个可观察的验证点：Preview 过程可见、Sync 实时同步、Constraint 可复现、Replay 一致。
-->
