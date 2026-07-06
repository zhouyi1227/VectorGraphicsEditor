---
layout: default
transition: slide-left
---

# 现场演示闭环

<div class="deck-rule"></div>
<div class="deck-lead">
  如果把系统价值压缩成一次现场操作，最能体现它完整性的就是这五步：创建、编辑、变换、复制和持久化。
</div>

<div class="process-row mt-6">
  <div v-click class="process-step">
    <div class="process-no">DEMO 01</div>
    <div class="process-title">创建</div>
    <div class="process-copy">拖出矩形，建立输入闭环。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 02</div>
    <div class="process-title">编辑</div>
    <div class="process-copy">修改描边、线型和填充。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 03</div>
    <div class="process-title">变换</div>
    <div class="process-copy">多选缩放，按 <code>Shift</code> 展示等比约束。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 04</div>
    <div class="process-title">复制</div>
    <div class="process-copy">验证深拷贝与 16px 偏移。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">DEMO 05</div>
    <div class="process-title">持久化</div>
    <div class="process-copy">保存、重开并导出。</div>
  </div>
</div>

<div class="deck-stage tight mt-6">
  <div class="eyebrow">观众可直接看到的验证点</div>
  <div class="thin-divider"></div>
  <div class="support-grid">
    <div v-click class="support-row">
      <div class="support-key">Preview</div>
      <div class="support-copy">拖拽创建和路径创建都有连续预览，而不是“松手才突然出现”。</div>
    </div>
    <div v-click class="support-row">
      <div class="support-key">Sync</div>
      <div class="support-copy">选中状态、属性面板和场景中的图形表现始终同步。</div>
    </div>
    <div v-click class="support-row">
      <div class="support-key">Constraint</div>
      <div class="support-copy">多选缩放、等比约束和粘贴偏移都能稳定复现。</div>
    </div>
    <div v-click class="support-row">
      <div class="support-key">Replay</div>
      <div class="support-copy">重开文档仍保留图形、样式和层级信息，证明 I/O 与渲染一致。</div>
    </div>
  </div>
</div>

<!--
高频追问建议放在备注里，不直接投给观众：为什么 ShapeData 用 struct、为什么策略接口析构要 virtual、为什么 ShapeItem 继承 QGraphicsObject、为什么属性面板不会死循环、为什么 JSON 固定 version 2、为什么 transform 不支持旋转。
-->
