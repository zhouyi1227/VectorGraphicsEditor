---
layout: default
transition: slide-left
---

# 需求与目标

<div class="deck-rule"></div>

<div class="deck-lead">
  课程题目要求的不只是“能画图”，而是把面向对象课程里的抽象、继承、多态、文件操作和界面交互整合成一个可运行系统。
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="eyebrow">题目要求</div>
    <div class="thin-divider"></div>
    <div class="rail-list">
      <div v-click class="rail-item">
        <div class="rail-title">完成一次真实编辑流程</div>
        <div class="rail-copy">从创建、选择、修改到保存与导出，用户需要能连续完成一整条操作链路。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title">知识点必须落到代码结构里</div>
        <div class="rail-copy">课程中的 OOP 概念要体现在类设计、接口抽象和运行时行为上，而不是只写在汇报里。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title">系统要能解释、能验证</div>
        <div class="rail-copy">不仅展示界面结果，还要能说明架构原因、文件契约和测试证据。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">OBJECTIVE A</div>
      <div class="rail-title">功能目标</div>
      <div class="rail-copy">稳定覆盖 7 种图形、两类创建流程、属性编辑、复制粘贴、文件 I/O、语言与主题切换。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">OBJECTIVE B</div>
      <div class="rail-title">工程目标</div>
      <div class="rail-copy">保持分层清晰、数据模型稳定、交互边界可测试、跨平台构建路径统一。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">BOUNDARY</div>
      <div class="rail-title">范围收敛</div>
      <div class="rail-copy">当前刻意不做撤销/重做、旋转编辑和标准 SVG 互操作，优先把现有闭环做完整、做稳定。</div>
    </div>
  </div>
</div>

<!--
这页说明我是怎么“收敛范围”的：课程项目最怕什么都想做，最后每个点都只做一半。所以我把目标锁定成“围绕 7 种图形完成一个稳定闭环”，再用分层和测试把它做好。
-->
