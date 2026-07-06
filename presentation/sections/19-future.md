---
layout: default
transition: slide-left
---

# 现场演示

<style>
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; }
.process-row { gap: 0.5rem; }
.process-row.mt-6 { margin-top: 0.6rem !important; }
.process-step { padding-top: 0.45rem; }
.process-title { font-size: 0.88rem; }
.process-copy { font-size: 0.74rem; line-height: 1.4; }
.support-grid { gap: 0.4rem; }
.support-row { padding-bottom: 0.35rem; grid-template-columns: 6rem 1fr; gap: 0.6rem; }
.support-key { font-size: 0.74rem; }
.support-copy { font-size: 0.78rem; line-height: 1.4; }
.deck-stage.tight { padding: 0.7rem 0.95rem; }
.deck-stage.tight.mt-6 { margin-top: 0.5rem !important; }
</style>

<div class="deck-rule"></div>
<div class="deck-lead">
  接下来我进行现场操作：创建、编辑、变换、复制、持久化。各位老师会看到完整链路在画布上运行一遍。
</div>

<div class="process-row mt-6">
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
    <div class="process-copy">多选后拖四角缩放，按 <code>Shift</code> 展示等比约束。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 04</div>
    <div class="process-title">复制</div>
    <div class="process-copy"><code>Ctrl+C / Ctrl+V</code>，验证深拷贝与 16 像素偏移。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 05</div>
    <div class="process-title">持久化</div>
    <div class="process-copy">保存为 <code>.vgjson</code>，重开文档，再导出 PNG。</div>
  </div>
</div>

<div class="deck-stage tight mt-6">
  <div class="eyebrow">老师可直接观察的验证点</div>
  <div class="thin-divider"></div>
  <div class="support-grid">
    <div v-click class="support-row">
      <div class="support-key">Preview</div>
      <div class="support-copy">拖拽创建和路径创建都有连续预览，不是「松手才突然出现」。</div>
    </div>
    <div v-click class="support-row">
      <div class="support-key">Sync</div>
      <div class="support-copy">选中状态、属性面板、画布中的图形表现始终同步。</div>
    </div>
    <div v-click class="support-row">
      <div class="support-key">Constraint</div>
      <div class="support-copy">多选缩放、Shift 等比、粘贴偏移都能稳定复现。</div>
    </div>
    <div v-click class="support-row">
      <div class="support-key">Replay</div>
      <div class="support-copy">重开文档仍保留图形、样式、层级，I/O 与渲染一致。</div>
    </div>
  </div>
</div>

<!--
各位老师，接下来我现场演示五步。第一步是创建——我切换到 Rectangle 工具，按下鼠标拖出一个矩形，大家会看到 preview 实时跟随光标。第二步是编辑——选中矩形，右侧属性面板会显示当前描边、线型、填充，我现场改一下。第三步是变换——我框选两个图形，拖右下角手柄，按住 Shift 验证等比约束。第四步是复制——Ctrl+C、Ctrl+V，新图形会沿右下偏移 16 像素，避免和原图重叠。第五步是持久化——保存为 .vgjson，重开文档，再导出 PNG，验证重开之后图形、样式、层级都还在。四个可观察的验证点：Preview 是拖拽过程连续可见；Sync 是选中状态和属性面板实时同步；Constraint 是缩放和粘贴偏移可复现；Replay 是重开文档 I/O 和渲染一致。我现在切换到编辑器。
-->
