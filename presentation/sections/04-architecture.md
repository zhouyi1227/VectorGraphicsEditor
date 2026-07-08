---
layout: default
transition: slide-left
---

# 需求与目标

<div class="deck-rule"></div>

<div class="deck-lead">
  课程题目要求把 OOP 的抽象、继承、多态、文件操作和界面交互整合成可运行系统。目标拆成功能、工程和边界三件事。
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="eyebrow">题目要求</div>
    <div class="thin-divider"></div>
    <div class="rail-list">
      <div v-click class="rail-item">
        <div class="rail-title">完整编辑链路</div>
        <div class="rail-copy">创建、选择、修改、保存、导出——五步连贯完成。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title">OOP 落到代码里</div>
        <div class="rail-copy">抽象类、继承、多态、封装能在具体类和运行时行为中指出来。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title">可解释 + 可验证</div>
        <div class="rail-copy">架构原因、文件契约、测试证据都能拿出来说清楚。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">A · 功能</div>
      <div class="rail-title">7 种图形、2 类创建流程</div>
      <div class="rail-copy">拖拽创建和路径创建两类工作流，属性编辑、复制粘贴、文件 I/O、语言与主题切换。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">B · 工程</div>
      <div class="rail-title">分层清晰 + 跨平台统一</div>
      <div class="rail-copy">四层架构、数据模型稳定、交互边界可独立测试、跨平台构建路径统一到同一套 preset。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">范围</div>
      <div class="rail-title">不做的事</div>
      <div class="rail-copy">当前不实现撤销/重做、旋转编辑、SVG 互操作。把现有闭环做完整、做稳定优先。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页先讲清楚题目的要求和我自己设的边界。题目要求是三件事：完整编辑链路、OOP 概念落到代码里、可解释可验证。我自己又拆成两个目标，最后把范围明确收一下。
-->
