---
layout: default
transition: slide-left
---

# 需求与目标

<style>
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; line-height: 1.4; }
.split-even { gap: 0.7rem; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.rail-list { gap: 0.45rem; }
.rail-item { padding-left: 0.7rem; }
.deck-stage { padding: 0.7rem 0.95rem; }
.eyebrow { font-size: 0.7rem; }
</style>

<div class="deck-rule"></div>

<div class="deck-lead">
  课程题目要求把 OOP 课程的抽象、继承、多态、文件操作和界面交互整合成一个可运行系统。我把目标拆成功能、知识点和可验证三件事，范围明确收敛。
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="eyebrow">题目要求</div>
    <div class="thin-divider"></div>
    <div class="rail-list">
      <div v-click class="rail-item">
        <div class="rail-title">完整编辑链路</div>
        <div class="rail-copy">创建、选择、修改、保存、导出——5 个动作必须能连贯完成，中途不出现断点。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title">OOP 概念落到代码里</div>
        <div class="rail-copy">抽象类、继承、多态、封装不能只写在汇报 PPT 上，要能在具体类、接口和运行时行为里指出来。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title">可解释 + 可验证</div>
        <div class="rail-copy">架构原因、文件契约、测试证据都要能拿出来说清楚，不是只展示界面结果。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">A · 功能</div>
      <div class="rail-title">7 种图形、2 类创建流程</div>
      <div class="rail-copy">覆盖 7 种基础图形，拖拽创建和路径创建两类工作流，属性编辑、复制粘贴、文件 I/O、语言与主题切换。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">B · 工程</div>
      <div class="rail-title">分层清晰 + 跨平台统一</div>
      <div class="rail-copy">四层架构、数据模型稳定、交互边界可独立测试、跨平台构建路径统一到同一套 preset。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">范围</div>
      <div class="rail-title">不做的事</div>
      <div class="rail-copy">当前不实现撤销/重做、旋转编辑、标准 SVG 互操作。把现有闭环做完整、做稳定优先。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页我先讲清楚题目的要求和我自己设的边界。题目要求是三件事：完整编辑链路、OOP 概念落到代码里、可解释可验证。我自己又拆成两个目标，A 是功能目标——7 种图形、两类创建流程、属性编辑、复制粘贴、文件 I/O、语言主题切换；B 是工程目标——分层清晰、跨平台构建路径统一到同一套 preset。最后我把范围明确收一下：撤销/重做、旋转编辑、SVG 互操作这三个不在这版里做，理由是把现有闭环做完整、做稳定比多塞三个半成品功能更值。这个收敛判断会在最后一页「未来工作」里再呼应。
-->
